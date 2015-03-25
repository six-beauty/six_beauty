#ifndef _TCPSRV_H
#define _TCPSRV_H

#include "StdAfx.h"
#include<vector>
#include<list>
#include <winsock2.h>
#include <MSWSock.h>
#pragma comment(lib,"ws2_32.lib")
#define SOCK_BUF_SIZE   8192
#define SERVERPORT	 65001
using namespace std;
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
	OVERLAPPED	s_overlapped;		//系统用异步IO信息结构体
	SOCKET	s_socket;				//本次I/O操作所使用的socket
	WSABUF	s_databuf;				//存储数据缓冲区，用来给重叠操作传递参数
	char	s_buffer[SOCK_BUF_SIZE];//对应WSABUF里的缓冲区
	OPERATION_TYPE	s_optype;				//网络操作类型
	//初始化
	_per_io_data()
	{
		memset(&s_overlapped,0,sizeof(OVERLAPPED));
		memset(&s_buffer,0,SOCK_BUF_SIZE);
		s_socket=INVALID_SOCKET;
		s_databuf.len=0;
		s_databuf.buf=s_buffer;
		s_optype=NULL_TYPE;
	}
	~_per_io_data()
	{
		if(s_socket!=INVALID_SOCKET)
		{
			closesocket(s_socket);
			s_socket=INVALID_SOCKET;
		}
	}
	void ResetBuffer()
	{
		memset(&s_buffer,0,SOCK_BUF_SIZE);
	}
}per_io_data,*p_per_io_data;

//定义单句柄数据结构体，每个“句柄”对应一个socket，每个socket可以对应多个I/O操作
typedef struct _per_socket_data
{
	SOCKET	s_socket;		//对应客户端的套接字
	SOCKADDR_IN	s_clientaddr;	//对应客户端的地址
	vector<p_per_io_data>	s_vtiodata;	//socket的I/O操作的数据结构体
	//对于listensocket即本地socket,存放的是acceptIO操作
	//对于clientsocket（客户端）,存放recv和send的IO操作
	_per_socket_data()
	{
		s_socket=INVALID_SOCKET;
		memset(&s_clientaddr,0,sizeof(s_clientaddr));
	}
	~_per_socket_data()
	{
		if(s_socket!=INVALID_SOCKET)
		{
			//循环删除客户端
			for(vector<p_per_io_data>::iterator iter=s_vtiodata.begin();iter!=s_vtiodata.end();iter++)
			{
				delete *iter;
				iter=s_vtiodata.erase(iter);
			}
			//关闭socket
			closesocket(s_socket);
		}
		for(vector<p_per_io_data>::iterator iter=s_vtiodata.begin();iter!=s_vtiodata.end();)
		{
			delete *iter;				//第一次解应用取得单I/O结构体地址，第二次取得结构体
			iter=s_vtiodata.erase(iter);
		}
	}//~_per_socket_data;
	p_per_io_data add_new_iodata()
	{
		p_per_io_data newiodata=new per_io_data;
		s_vtiodata.push_back(newiodata);
		return newiodata;

	}
	void dele_iodata(p_per_io_data deledata)
	{
		for(vector<p_per_io_data>::iterator iter=s_vtiodata.begin();iter!=s_vtiodata.end();iter++)
		{
			if(*iter==deledata)
			{
				delete *iter;
				iter=s_vtiodata.erase(iter);
			}
		}
	}
}per_socket_data,*p_per_socket_data;	

class TcpSrv
{
private:
	CRITICAL_SECTION m_cslock;				//临界锁
	HANDLE m_EndEvent;						//结束事件
	HANDLE m_completionport;				//完成端口句柄
	vector<per_socket_data*> lstclntdata;	//客户端的socket链表，方便释放内存
	int m_nThreads;							//工作线程的个数
	HANDLE *m_workthhdle;					//工作线程句柄
	per_socket_data* m_socketdata;				//监听socketdata
	LPFN_ACCEPTEX	m_lpAcceptEx;				//acceptex函数的指针
	LPFN_GETACCEPTEXSOCKADDRS m_lpGetAcceptExSockAddrs;		//GetAcceptSockAddrs函数的指针
	struct sockaddr_in	m_localsockaddr;		//本地地址
	TcpSrv*	m_this;								//类的所有者
public:
	//构造函数
	TcpSrv():
	  m_completionport(INVALID_HANDLE_VALUE),
		  m_workthhdle(NULL),
		  m_nThreads(0),
		  lstclntdata(NULL),
		  m_lpAcceptEx(NULL),
		  m_lpGetAcceptExSockAddrs(NULL)
	  {

	  }
	  //析构函数
	 	
	  //程序开始准备，加载动态库，创建完成端口，创建线程池
	  bool setout();							
	  //初始化监听socket
	  bool initlistensocket();		
	  //启动程序
	  void startup()
	  {
		  setout();
		  initlistensocket();
	  }
	  //关闭服务器	
	  void closeIocp();
	  //投递异步accept请求
	  bool postaccept(p_per_io_data persockdata);
	  //投递异步recv请求
	  bool postrecv(per_io_data* perIodata);
	  //工作者线程
	  static DWORD WINAPI WorkThread(LPVOID lParam);
	  //workthread线程accept处理函数
	  bool _doAccept(per_socket_data* psockdata,per_io_data* piodata);
	  //workthread线程recv处理函数
	  bool _doRecv(per_socket_data* psockdata,per_io_data* piodata);
	  //workthread线程send处理函数
	  //	bool _doSend(per_socket_data* psockdata,per_io_data* piodata);
	  //释放其中一个客户端的资源
	  void endconnect(per_socket_data* ppsocketdata);
};

#endif