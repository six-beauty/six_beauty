// IOCP服务器noclass.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
#include<cstdio>
#include <winsock2.h>
#include <MSWSock.h>
#include <ws2tcpip.h>
#include <mswsock.h>    //微软扩展的类库

#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_BUF_SIZE   8192
#define SERVERPORT	 12345

//定义IO操作类型
typedef enum _operation_type
{
	ACCEPT_TYPE,
	SEND_TYPE,
	RECV_TYPE,
	NULL_TYPE
}OPERATION_TYPE;

//定义完成端口中的单I/O数据结构体，每一个I/O操作对应一个_per_io_data
typedef struct _per_io_data
{	
	OVERLAPPED	m_overlapped;		//系统用异步IO信息结构体
	SOCKET	m_socket;				//本次I/O操作所使用的socket
	WSABUF	m_databuf;				//存储数据缓冲区，用来给重叠操作传递参数
	char	m_buffer[SOCK_BUF_SIZE];//对应WSABUF里的缓冲区
	OPERATION_TYPE	m_optype;				//网络操作类型
	//初始化
	_per_io_data()
	{
		memset(&m_overlapped,0,sizeof(OVERLAPPED));
		memset(m_buffer,0,SOCK_BUF_SIZE);
		m_socket=INVALID_SOCKET;
		m_databuf.len=SOCK_BUF_SIZE;;
		m_databuf.buf=m_buffer;
		m_optype=NULL_TYPE;
	}
	~_per_io_data()
	{
		if(m_socket!=INVALID_SOCKET)
		{
			closesocket(m_socket);
			m_socket=INVALID_SOCKET;
		}
	}
	void ResetBuffer()
	{
		ZeroMemory(m_buffer,SOCK_BUF_SIZE);
	}
}per_io_data,*p_per_io_data;

//定义单句柄数据结构体，每个“句柄”对应一个socket，每个socket可以对应多个I/O操作
typedef struct _per_socket_data
{
	SOCKET	m_socket;		//对应客户端的套接字
	SOCKADDR_IN	m_clientaddr;	//对应客户端的地址
	vector<p_per_io_data>	m_vtiodata;	//socket的I/O操作的数据结构体
	//对于listensocket即本地socket,存放的是acceptIO操作
	//对于clientsocket（客户端）,存放recv和send的IO操作
	_per_socket_data()
	{
		m_socket=INVALID_SOCKET;
		memset(&m_clientaddr,0,sizeof(m_clientaddr));
	}
	~_per_socket_data()
	{
		if(m_socket!=INVALID_SOCKET)
		{
			//循环删除客户端
			for(vector<p_per_io_data>::iterator iter=m_vtiodata.begin();iter!=m_vtiodata.end();iter++)
			{
				delete *iter;
				iter=m_vtiodata.erase(iter);
			}
			//关闭socket
			closesocket(m_socket);
		}
		for(vector<p_per_io_data>::iterator iter=m_vtiodata.begin();iter!=m_vtiodata.end();)
		{
			delete *iter;				//第一次解应用取得单I/O结构体地址，第二次取得结构体
			iter=m_vtiodata.erase(iter);
		}
	}//~_per_socket_data;
	p_per_io_data add_new_iodata()
	{
		p_per_io_data newiodata=new per_io_data;
		m_vtiodata.push_back(newiodata);
		return newiodata;

	}
	void dele_iodata(p_per_io_data deledata)
	{
		for(vector<p_per_io_data>::iterator iter=m_vtiodata.begin();iter!=m_vtiodata.end();)
		{
			if(*iter==deledata)
			{
				delete deledata;
				iter=m_vtiodata.erase(iter);
			}
			else
				iter++;
		}
	}
}per_socket_data,*p_per_socket_data;	
//定义完成端口中的单I/O数据结构体，每一个I/O操作对应一个_per_io_data
typedef struct work_thread_struct
{
	int threadid;				//线程id
	HANDLE m_completionport;	//完成端口句柄
}work_struct;
DWORD WINAPI WorkThread(LPVOID lParam);		//工作者线程

LPFN_ACCEPTEX	m_lpAcceptEx=NULL;		//acceptex函数的指针
LPFN_GETACCEPTEXSOCKADDRS m_lpGetAcceptExSockAddrs=NULL;		//GetAcceptSockAddrs函数的指针
CRITICAL_SECTION m_cslock;				//临界锁
HANDLE m_EndEvent;						//结束事件
vector<per_socket_data*> lstclntdata;	//客户端的socket链表，方便释放内存
SOCKET m_ListenSocket;					//监听套接字


//投递recv请求
bool postrecv(per_io_data* pIodata)
{
	//WSARecv的参数准备
	DWORD dwRecvBytes=0;
	DWORD dwInfo=0;
	WSABUF *databuf=&pIodata->m_databuf;
	pIodata->ResetBuffer();
	pIodata->m_optype=RECV_TYPE;
	OVERLAPPED *p_ol=&pIodata->m_overlapped;
	//投递WSARecv请求
	if(WSARecv(pIodata->m_socket,databuf,1,&dwRecvBytes,&dwInfo,p_ol,NULL)==SOCKET_ERROR)
	{
		printf("投递recv请求失败...\n");
		return false;
	}
	return true;
}
//投递accept请求
bool postaccept(per_socket_data* m_socketdata,per_io_data* pIodata)
{
	if(m_socketdata->m_socket==INVALID_SOCKET)
	{
		printf("监听套接字有错误...\n");
		return false;
	}
	
	//为acceptEx准备参数
	DWORD bytereceived=0;
	pIodata->m_optype = ACCEPT_TYPE; 
	WSABUF* databuf=&pIodata->m_databuf;
	OVERLAPPED *p_ol=&pIodata->m_overlapped;
	//	pIodata->m_databuf.len=SOCK_BUF_SIZE;			//之前空间为0，改为初始化时设为SOCK_BUF_SIZE就好
	//投递accpetEx请求,m_lpAcceptEx是acceptEx通过WSAIoctl获得的函数指针
	
	//为acceptEx准备socket（acceptEx比accept高效的重点）
	pIodata->m_socket=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if((pIodata->m_socket)==INVALID_SOCKET)
	{
		printf("为acceptEx创建套接字失败...\n");
		return false;
	}
	if(FALSE==m_lpAcceptEx(m_socketdata->m_socket,pIodata->m_socket,databuf->buf, databuf->len - ((sizeof(SOCKADDR_IN)+16)*2),   
		sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, &bytereceived,p_ol))
	{
		if(WSA_IO_PENDING != WSAGetLastError())  
		{  
			printf("投递acceptEx失败，错误代码:%d\n",WSAGetLastError()); 
			return false;  
		}  
	}
	//等待线程结束
	return true;
}


int main()
{
	int m_nThreads;							//工作线程的个数
	HANDLE *m_workthhdle=NULL;				//工作线程句柄
	per_socket_data* m_socketdata=NULL;		//监听socketdata
	struct sockaddr_in	m_localsockaddr;	//本地地址
	HANDLE m_completionport=INVALID_HANDLE_VALUE;				//完成端口句柄
	//加载socket库
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=NO_ERROR)
	{
		printf("打开socket动态链接库错误.\n");
		return false;  
	}else
		printf("打开socket动态链接库完成.\n");

	/////////////////////////////////////////////
	//初始化互斥锁和退出事件
	InitializeCriticalSection(&m_cslock);
	m_EndEvent=CreateEvent(NULL,true,false,NULL);

	/////////////////////////////////////////////
	//创建完成端口
	if((m_completionport=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0))==NULL)
	{
		printf("创建端口失败.\n");
		return false;
	}else
		printf("创建完成端口成功.\n");



	/////////////////////////////////////////////
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
		work_struct *workstruct=new work_struct;
		workstruct->threadid=i+1;
		workstruct->m_completionport=m_completionport;
		if((m_workthhdle[i]=CreateThread(NULL,0,WorkThread,(void*)workstruct,0,NULL))==NULL)
		{
			printf("线程池创建失败...\n");
			return false;  
		}
	}

	/////////////////////////////////////////////
	// 生成用于监听的Socket的信息
	m_socketdata=new per_socket_data;
	//创建监听socket
	m_ListenSocket=m_socketdata->m_socket=WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	if((m_socketdata->m_socket)==INVALID_SOCKET)
	{
		printf("监听socket初始化失败...\n");
		return false;
	}else
		printf("监听socket创建成功.\n");
	//将listensocket绑定到完成端口中
	if(NULL==CreateIoCompletionPort((HANDLE)m_socketdata->m_socket,m_completionport,(DWORD)m_socketdata,0))
	{
		printf("绑定listensocket到完成端口失败....\n");
		if(m_socketdata->m_socket!=INVALID_SOCKET)
			closesocket(m_socketdata->m_socket);
		return false;
	}else
		printf("绑定listensocket到完成端口完成.\n");
	//设置本地addr
	memset(&m_localsockaddr,0,sizeof(m_localsockaddr));
	m_localsockaddr.sin_family=AF_INET;
	m_localsockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	m_localsockaddr.sin_port=htons(SERVERPORT);
	//绑定监听socket和端口
	if(bind(m_socketdata->m_socket,(SOCKADDR*)&m_localsockaddr,sizeof(SOCKADDR_IN))==SOCKET_ERROR)
	{
		printf("监听socket和端口绑定失败...\n");
		return false;
	}
	//监听开始
	if(listen(m_socketdata->m_socket,SOMAXCONN)!=0)
	{
		printf("监听启动失败...\n");
		return false;
	}

	/////////////////////////////////////////////
	//若未获取accpetex函数就调用它消耗较大，先用WSAIoctl获取函数指针
	// AcceptEx 和 GetAcceptExSockaddrs 的GUID，用于导出函数指针
	GUID GuidAcceptEx = WSAID_ACCEPTEX;  
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS; 
	DWORD acByte=0;
	//下面获取GetAcceptExSockAddrs的地址
	DWORD dwBytes = 0;  
	if(SOCKET_ERROR == WSAIoctl(
		m_socketdata->m_socket, 
		SIO_GET_EXTENSION_FUNCTION_POINTER, 
		&GuidAcceptEx, 
		sizeof(GuidAcceptEx), 
		&m_lpAcceptEx, 
		sizeof(m_lpAcceptEx), 
		&dwBytes, 
		NULL, 
		NULL))  
	{
		printf("AcceptEx函数获取失败: %d\n", WSAGetLastError());  
		return false;
	}
	if(WSAIoctl(m_socketdata->m_socket,SIO_GET_EXTENSION_FUNCTION_POINTER,&GuidGetAcceptExSockAddrs,sizeof(GuidGetAcceptExSockAddrs),
		&m_lpGetAcceptExSockAddrs,sizeof(m_lpGetAcceptExSockAddrs),&dwBytes,0,0)==SOCKET_ERROR)
	{
		printf("GetAcceptExSockAddrs函数获取失败: %d\n", WSAGetLastError());  ;
		return false;
	}
	/////////////////////////////////////////////
	//acceptEx在完成端口上投递多个请求	
	for(int i=0;i<14;i++)
	{
		per_io_data *periodata=m_socketdata->add_new_iodata();
		if(postaccept(m_socketdata,periodata)==false)
		{
			m_socketdata->dele_iodata(periodata);
			return false;
		}
	}
	printf("14个accept请求投递完毕...\n");
	printf("开始工作模块:\n");

	WaitForMultipleObjects(m_nThreads,m_workthhdle,TRUE,INFINITE);
	closesocket(m_ListenSocket);
	WSACleanup();
	return 0;
}

//工作者线程workthread的实现
DWORD WINAPI WorkThread(LPVOID lpParam)
{
	work_struct* workstruct=(work_struct*)lpParam;
	int threadid=(int)workstruct->threadid;
	HANDLE m_completionport=(HANDLE)workstruct->m_completionport;
	//	HANDLE m_completionport=(HANDLE)lpParam;
	LPOVERLAPPED	pOverapped=NULL;
	per_socket_data	*pSocketdata=NULL;
	per_io_data	*pIodata=NULL;
	DWORD	dwBytesTransfered=0;

	printf("工作线程:%d	启动...\n",threadid);
	//循环处理请求
	while(WAIT_OBJECT_0!=WaitForSingleObject(&m_EndEvent,0))
	{
		BOOL bRet=GetQueuedCompletionStatus(
			m_completionport,
			&dwBytesTransfered,
			(PULONG_PTR)&pSocketdata,
			(LPOVERLAPPED*)&pOverapped,
			INFINITE);
		if(bRet==0)
		{		
			printf("工作线程GetQueuedCompletionStatus错误,错误码:%d\n",WSAGetLastError());			
			return false;
		}//if
		pIodata=(per_io_data*)CONTAINING_RECORD(pOverapped,_per_io_data,m_overlapped);
		if(dwBytesTransfered==0 && ( pIodata->m_optype==RECV_TYPE || pIodata->m_optype==SEND_TYPE))
		{
			//释放掉线客户端的资源
			closesocket(pSocketdata->m_socket);
			delete pSocketdata;
			delete pIodata;
			continue;
		}//if
		switch(pIodata->m_optype)
		{
			//工作线程workthread中对accpet_type的操作
		case ACCEPT_TYPE:
			{
				printf("ACCEPT_TYPE的IO操作开始\n");
				//通过GetAcceptExSockAddrs()获得地址信息
				SOCKADDR_IN *LocalAddr=NULL;
				SOCKADDR_IN *ClientAddr=NULL;
				int localLen=sizeof(SOCKADDR_IN),clientLen=sizeof(SOCKADDR_IN);
				m_lpGetAcceptExSockAddrs(pIodata->m_databuf.buf,pIodata->m_databuf.len-((sizeof(SOCKADDR_IN)+16)*2),
					sizeof(SOCKADDR_IN)+16,sizeof(SOCKADDR_IN)+16,(LPSOCKADDR*)LocalAddr,&localLen,(LPSOCKADDR*)ClientAddr,&clientLen);

				printf("用户%s登陆服务器...\n",inet_ntoa(ClientAddr->sin_addr));
				printf("用户%s\t:%s.\n",inet_ntoa(ClientAddr->sin_addr),pIodata->m_databuf.buf);
				//创建client的socketdata信息
				per_socket_data* pnew_sockdata=new per_socket_data;
				pnew_sockdata->m_socket=pIodata->m_socket;
				memcpy(&pnew_sockdata->m_clientaddr,ClientAddr,sizeof(SOCKADDR_IN));			//这里要注意不能直接赋值，指针赋值的问题////////////////////
				//绑定clientsocket到完成端口中
				if(NULL==CreateIoCompletionPort((HANDLE)pnew_sockdata->m_socket,m_completionport,(DWORD)pnew_sockdata,0))
				{
					printf("绑定clientsocket(%d)到完成端口失败....\n",inet_ntoa(ClientAddr->sin_addr));
					if(pnew_sockdata->m_socket!=INVALID_SOCKET)
						closesocket(pnew_sockdata->m_socket);
					return false;
				}
				//为这个client投递第一个recv请求
				per_io_data* pnew_iodata=pnew_sockdata->add_new_iodata();
				pnew_iodata->m_optype=RECV_TYPE;
				pnew_iodata->m_socket=pnew_sockdata->m_socket;
				if(postrecv(pnew_iodata)==false)
				{
					printf("为clientsocket(%d)投递第一个recv请求失败...\n",inet_ntoa(ClientAddr->sin_addr));
					pnew_sockdata->dele_iodata(pnew_iodata);
					return false;
				}
				//把新建的clientdata放入lstclntdata中
				EnterCriticalSection(&m_cslock);
				lstclntdata.push_back(pnew_sockdata);
				LeaveCriticalSection(&m_cslock);
				//重置数据缓冲区，继续投递accpetEx请求
				pIodata->ResetBuffer();
				postaccept(pSocketdata,pIodata);
				printf("ACCEPT_TYPE的IO操作结束\n");
				break;
			}
		case RECV_TYPE:
			//工作线程workthread中对recv的操作
			printf("客户(%d):\n\t%s\n",inet_ntoa(pSocketdata->m_clientaddr.sin_addr),pIodata->m_databuf.buf);
			postrecv(pIodata);
			break;
		case SEND_TYPE:
			//		mythis->_doSend(pSocketdata,pIodata);
			break;
		default:
			printf("workthread工作异常...\n");
			break;			
		}//switch						
	}//while
	printf("工作线程:%d	退出...\n",threadid);
	delete workstruct;
	return 0;
}
