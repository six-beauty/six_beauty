#include<iostream>
#include<WinSock2.h>
#include<string>
#include<time.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

const USHORT PORT = 12345;
const std::string ipaddr= "192.168.123.1";

int main()
{
	WSADATA wsaData;
	int nResult;
	nResult = WSAStartup(MAKEWORD(2,2), &wsaData);

	sockaddr_in serverAddr;
	serverAddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	SOCKET acceptSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(acceptSock == INVALID_SOCKET )
	{
		cout<<"create Socket Error"<<endl;
		return -1;
	}

	if(SOCKET_ERROR == connect(acceptSock,reinterpret_cast<const struct sockaddr *>(&serverAddr),sizeof(serverAddr)))
	{
		closesocket(acceptSock);
		cout<<"错误：连接至服务器失败！\n"<<endl;
		return -1; 
	}

	int nByteSend=0;
	char bufSend[1024] = {0};

	memset(bufSend,0,sizeof(bufSend));
	lstrcpyn(bufSend,"RecvThread",sizeof(bufSend));
	nByteSend = send(acceptSock,bufSend,strlen(bufSend)+1,0);
	if(nByteSend < 0)
	{
		cout<<"send fail!"<<endl;
	}
	
	/*
	cin>>nByteSend;

	memset(bufSend,0,sizeof(bufSend));
	lstrcpyn(bufSend,"发送第二句",sizeof(bufSend));
	nByteSend = send(acceptSock,bufSend,strlen(bufSend)+1,0);
	if(nByteSend < 0)
	{
		cout<<"send fail!"<<endl;
	}
	*/
	int nByteRecv=0;
	char szRecv[1024] = {0};

	/*
	while(true)
	{
		ZeroMemory(szRecv,sizeof(szRecv)/sizeof(szRecv[0]));
		int nBytesRecv = recv(acceptSock,szRecv,sizeof(szRecv),0);
		if(nBytesRecv > 0)
		{
			cout<<"【Recv】:"<<szRecv<<endl;
		}
	}
	*/
	SOCKADDR_IN    addrSender;
	int addrSize = sizeof(SOCKADDR_IN);

	struct fd_set fds; 
	struct timeval timeout={3,0}; //select等待3秒，3秒轮询，要非阻塞就置0 
	while(true)
	{ 
		FD_ZERO(&fds); //每次循环都要清空集合，否则不能检测描述符变化 
		FD_SET(acceptSock,&fds); //添加描述符 
		int nrecv = select(0,&fds,NULL,NULL,&timeout);
		switch(nrecv) //select使用 
		{ 
		case -1: 
			{
				//select错误
				return false;
			}
		case 0: 
			{
				// 监听用户的停止事件
				int nContinue=0;
				cout<<"是否继续(0/1):";
				cin>>nContinue;
				if(nContinue==0)
				{
					cout<<"接收到用户停止命令.\n";
					return 0;
				}	
				break;
			}
		default: 
			if(FD_ISSET(acceptSock,&fds)) //测试sock是否可读，即是否网络上有数据 
			{ 
				ZeroMemory(szRecv,sizeof(szRecv)/sizeof(szRecv[0]));
				int nBytesRecv = recv(acceptSock,szRecv,sizeof(szRecv),0);
				if(nBytesRecv > 0)
				{
					cout<<"【Recv】:"<<szRecv<<endl;
				}else
				{
					int nwrite = select(0,NULL,&fds,NULL,&timeout);
					if(nwrite == -1)
					{
						cout<<"写入失败!关闭连接..."<<endl;
						return -1;
					}
					else if(nBytesRecv ==0 && nwrite ==1)
					{
						cout<<"读取到0byte的数据，但socket扔可以写入..."<<endl;
					}
				}
			}// end if break; 
		}// end switch 
	}//end while 

	closesocket(acceptSock);
	WSACleanup();

	return 0;
};
