#include"StdAfx.h"
#include"TcpSrv.h"
#include<iostream>
using namespace std;
//初始化,加载库，创建端口，线程池（按功能分这部分可以分成3个函数，把他们返回值设为bool，在setout里面再return && && ;但太麻烦了~_~)
bool TcpSrv::setout()
{
	//加载socket库
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0)
	{
		cerr<<"打开socket动态链接库错误..."<<endl;
		return false;  
	}
	//初始化互斥锁和退出事件
	InitializeCriticalSection(&m_cslock);
	m_EndEvent=CreateEvent(NULL,true,false,NULL);
	//创建完成端口
	if((m_completionport=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0))=NULL)
	{
		cerr<<"创建端口失败..."<<endl;
		return false;
	}

	//创建work线程池
	SYSTEM_INFO si;
	GetSystemInfo(&si);	//获取系统信息
	//基于系统处理器核心数量创建线程
	m_nThreads=si.dwNumberOfProcessors*2+2;			//将要创建的进程数，删除时候要用
	//初始化工作者线程
	m_workthhdle=new HANDLE[m_nThreads];
	//创建工作者线程
	for(int i=0;i<m_nThreads;i++)
	{
		if((m_workthhdle[i]=CreateThread(NULL,0,WorkThread,this,0,NULL))==NULL)
		{
			cerr<<"线程池创建失败..."<<endl;
			return false;  
		}
	}
	return true;
}

//初始化listensocket
bool TcpSrv::initlistensocket()
{
	// 生成用于监听的Socket的信息
	m_socketdata=new per_socket_data;
	//创建监听socket
	if((m_socketdata->s_socket=WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED))==INVALID_SOCKET)
	{
		cerr<<"监听socket初始化失败..."<<endl;
		return false;
	}
	//将listensocket绑定到完成端口中
	if(NULL==CreateIoCompletionPort((HANDLE)m_socketdata->s_socket,m_completionport,(DWORD)m_socketdata,0))
	{
		cerr<<"绑定listensocket到完成端口失败...."<<endl;
		if(m_socketdata->s_socket!=INVALID_SOCKET)
			closesocket(m_socketdata->s_socket);
		return false;
	}
	//设置本地addr
	memset(&m_localsockaddr,0,sizeof(m_localsockaddr));
	m_localsockaddr.sin_family=AF_INET;
	m_localsockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	m_localsockaddr.sin_port=htons(SERVERPORT);
	//绑定监听socket和端口
	if(bind(m_socketdata->s_socket,(SOCKADDR*)&m_localsockaddr,sizeof(m_localsockaddr)!=0))
	{
		cerr<<"监听socket和端口绑定失败..."<<endl;
		return false;
	}
	//监听开始
	if(listen(m_socketdata->s_socket,SOMAXCONN)!=0)
	{
		cerr<<"监听启动失败..."<<endl;
		return false;
	}

	//若未获取accpetex函数就调用它消耗较大，先用WSAIoctl获取函数指针
	GUID guidAcceptEx=WSAID_ACCEPTEX;
	GUID guidGetAcceptExSockaddrs=WSAID_GETACCEPTEXSOCKADDRS;
	DWORD acByte=0;
	if(WSAIoctl(m_socketdata->s_socket,SIO_GET_EXTENSION_FUNCTION_POINTER,&guidAcceptEx,sizeof(guidAcceptEx),
		m_lpAcceptEx,sizeof(m_lpAcceptEx),&acByte,0,0)==0)
	{
		cerr<<"AcceptEx函数获取失败..."<<endl;
		return false;
	}
	//下面获取GetAcceptExSockAddrs的地址
	if(WSAIoctl(m_socketdata->s_socket,SIO_GET_EXTENSION_FUNCTION_POINTER,&guidGetAcceptExSockaddrs,sizeof(guidGetAcceptExSockaddrs),
		&m_lpGetAcceptExSockAddrs,sizeof(m_lpGetAcceptExSockAddrs),&acByte,0,0)==0)
	{
		cerr<<"AcceptEx函数获取失败..."<<endl;
		return false;
	}
	//acceptEx在完成端口上投递多个请求	
	for(int i=0;i<10;i++)
	{
		per_io_data *periodata=m_socketdata->add_new_iodata();
		periodata->s_optype=ACCEPT_TYPE;
		periodata->s_socket=m_socketdata->s_socket;
		if(postaccept(periodata)==false)
		{
			m_socketdata->dele_iodata(periodata);
			return false;
		}
	}
	cout<<"初始化服务器成功，开始投递accept请求..."<<endl;
	return true;
}
void TcpSrv::closeIocp()
{

}
DWORD WINAPI TcpSrv::WorkThread(LPVOID lpParam)
{
	TcpSrv* mythis=(TcpSrv*)lpParam;
	OVERLAPPED	*pOverapped=NULL;
	per_socket_data	*pSocketdata=NULL;
	per_io_data	*pIodata=NULL;
	DWORD	dwBytesTransfered=0;

	//循环处理请求
	while(WAIT_OBJECT_0!=WaitForSingleObject(mythis->m_EndEvent,0))
	{
		if(GetQueuedCompletionStatus(
			mythis->m_completionport,
			&dwBytesTransfered,
			(PULONG_PTR)pSocketdata,
			&pOverapped,
			INFINITE
			)==0)
		{
			cerr<<"工作线程GetQueuedCompletionStatus错误..."<<endl;
			continue;
		}//if
		pIodata=(per_io_data*)CONTAINING_RECORD(pOverapped,per_io_data,s_overlapped);
		if(dwBytesTransfered==0 && ( pIodata->s_optype==RECV_TYPE || pIodata->s_optype==SEND_TYPE))
		{
			//释放掉线客户端的资源
			mythis->endconnect(pSocketdata);
			continue;
		}//if
		switch(pIodata->s_optype)
		{
		case ACCEPT_TYPE:
			mythis->_doAccept(pSocketdata,pIodata);
			break;
		case RECV_TYPE:
			mythis->_doRecv(pSocketdata,pIodata);
			break;
		case SEND_TYPE:
			//		mythis->_doSend(pSocketdata,pIodata);
			break;
		default:
			cerr<<"workthread工作异常..."<<endl;
			break;
		}//switch
	}//while
	return 0;
}
//释放一个客户端的资源
void TcpSrv::endconnect(per_socket_data* ppsocketdata)
{
	EnterCriticalSection(&m_cslock);
	for(vector<per_socket_data*>::iterator iter=lstclntdata.begin();iter!=lstclntdata.end();iter++)
	{
		if((*iter)==ppsocketdata)
		{
			delete *iter;
			lstclntdata.erase(iter);
		}
		break;
	}
	LeaveCriticalSection(&m_cslock);
}
//投递recv请求
bool TcpSrv::postrecv(per_io_data* piodata)
{
	//WSARecv的参数准备
	DWORD dwSendBytes=0;
	DWORD dwInfo=0;
	WSABUF *databuf=&piodata->s_databuf;
	piodata->ResetBuffer();
	piodata->s_optype=RECV_TYPE;
	//投递WSARecv请求
	if(WSARecv(piodata->s_socket,databuf,1,&dwSendBytes,&dwInfo,&piodata->s_overlapped,NULL)==SOCKET_ERROR)
	{
		cerr<<"投递recv请求失败..."<<endl;
		return false;
	}
	return true;
}
//投递accept请求
bool TcpSrv::postaccept(per_io_data* piodata)
{
	//为acceptEx准备socket（acceptEx比accept高效的重点）
	if((piodata->s_socket=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED))==INVALID_SOCKET)
	{
		cerr<<"为acceptEx创建套接字失败..."<<endl;
		return false;
	}
	//为acceptEx准备参数
	DWORD bytereceived;
	WSABUF* databuf=&piodata->s_databuf;

	//投递accpetEx请求
	if(m_lpAcceptEx(m_socketdata->s_socket,piodata->s_socket,databuf->buf, databuf->len - ((sizeof(SOCKADDR_IN)+16)*2),   
		sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, &bytereceived, &piodata->s_overlapped)==false)
	{
		cerr<<"投递acceptEx失败..."<<endl;
		return false;
	}
	return true;
}
//工作线程workthread中对accpet_type的操作
bool TcpSrv::_doAccept(per_socket_data* plistsockdata,per_io_data* piodata)
{
	//通过GetAcceptExSockAddrs()获得地址信息
	SOCKADDR_IN *LocalAddr=NULL;
	SOCKADDR_IN *ClientAddr=NULL;
	int localLen=sizeof(SOCKADDR_IN),clientLen=sizeof(SOCKADDR_IN);
	m_lpGetAcceptExSockAddrs(piodata->s_databuf.buf,piodata->s_databuf.len-((sizeof(SOCKADDR_IN)+16)*2),sizeof(SOCKADDR_IN)+16,sizeof(SOCKADDR_IN)+16,
		(LPSOCKADDR*)LocalAddr,&localLen,(LPSOCKADDR*)ClientAddr,&clientLen);
	cout<<"用户:"<<inet_ntoa(ClientAddr->sin_addr)<<"登陆服务器..."<<endl;
	cout<<inet_ntoa(ClientAddr->sin_addr)<<"	:"<<piodata->s_databuf.buf<<endl;
	//创建client的socketdata信息
	per_socket_data* pnew_sockdata=new per_socket_data;
	pnew_sockdata->s_socket=piodata->s_socket;
	memcpy(&pnew_sockdata->s_clientaddr,ClientAddr,sizeof(SOCKADDR_IN));			//这里要注意不能直接赋值，指针赋值的问题////////////////////
	//绑定clientsocket到完成端口中
	if(NULL==CreateIoCompletionPort((HANDLE)pnew_sockdata->s_socket,m_completionport,(DWORD)pnew_sockdata,0))
	{
		cerr<<"绑定clientsocket("<<inet_ntoa(ClientAddr->sin_addr)<<")到完成端口失败...."<<endl;
		if(m_socketdata->s_socket!=INVALID_SOCKET)
			closesocket(m_socketdata->s_socket);
		return false;
	}
	//为这个client投递第一个recv请求
	per_io_data* pnew_iodata=pnew_sockdata->add_new_iodata();
	pnew_iodata->s_optype=RECV_TYPE;
	pnew_iodata->s_socket=pnew_sockdata->s_socket;
	if(postrecv(pnew_iodata)==false)
	{
		cerr<<"为clientsocket("<<inet_ntoa(ClientAddr->sin_addr)<<")投递第一个recv请求失败..."<<endl;
		pnew_sockdata->dele_iodata(pnew_iodata);
		return false;
	}
	//把新建的clientdata放入lstclntdata中
	EnterCriticalSection(&m_cslock);
	lstclntdata.push_back(pnew_sockdata);
	LeaveCriticalSection(&m_cslock);
	//重置数据缓冲区，继续投递accpetEx请求
	piodata->ResetBuffer();
	return postrecv(piodata);
}
//工作线程workthread中对recv的操作
bool TcpSrv::_doRecv(per_socket_data* psockdata,per_io_data* piodata)
{
	cout<<"客户("<<inet_ntoa(psockdata->s_clientaddr.sin_addr)<<"):"<<endl<<"	"<<piodata->s_databuf.buf<<endl;
	return postrecv(piodata);
}
