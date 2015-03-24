#include<iostream>
#include<WinSock2.h>
#include<string>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

const USHORT PORT = 12345;
const std::string ipaddr= "127.0.0.1";

string GetLocalIP()
{
	char hostname[MAX_PATH];
	gethostname(hostname,MAX_PATH);                // 获得本机主机名

	struct hostent FAR* lpHostEnt = gethostbyname(hostname);

	if(lpHostEnt == NULL)
	{
		return "";
	}

	LPSTR lpAddr = lpHostEnt->h_addr_list[0];      // 取得IP地址列表中的第一个为返回的IP

	struct in_addr inAddr;
	memmove(&inAddr,lpAddr,4);

	string ipStr = string( inet_ntoa(inAddr) );   // 转化成标准的IP地址形式

	return ipStr;
}


int main()
{
	WSADATA wsaData;
	int nResult;
	nResult = WSAStartup(MAKEWORD(2,2), &wsaData);

	string ipaddr = GetLocalIP();
	sockaddr_in localaddr;
	localaddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(PORT);
	SOCKET acceptSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(acceptSock == INVALID_SOCKET )
	{
		cout<<"create Socket Error"<<endl;
		return -1;
	}

	int nRet = bind(acceptSock , (struct sockaddr*)&localaddr , sizeof(localaddr)) ;
	if( nRet != 0)
	{
		cout<<"bind Error"<<endl;
		return -1;
	}

	nRet = listen(acceptSock,3);
	if( nRet != 0)
	{
		cout<<"listen Error"<<endl;
		return -1;
	}
	SOCKADDR_IN clientsocket;
	int len=sizeof(SOCKADDR);
	SOCKET serConn=accept(acceptSock,(SOCKADDR*)&clientsocket,&len);
	if(serConn == INVALID_SOCKET)
	{
		cout<<"accept Error"<<endl;
		return -1;
	}
	/*
	char bufRecv[1024]={0};
	int nByteRecv=0;
	memset(bufRecv,0,sizeof(bufRecv));
	nByteRecv=recv(serConn,bufRecv,sizeof(bufRecv),0);
	if(nByteRecv<0)
	{
		cout<<"recvFail"<<endl;
	}
	else
		cout<<"recv:"<<bufRecv<<endl;


	memset(bufRecv,0,sizeof(bufRecv));
	nByteRecv=recv(serConn,bufRecv,sizeof(bufRecv),0);
	if(nByteRecv<0)
	{
		cout<<"recvFail"<<endl;
	}
	else
		cout<<"recv:"<<bufRecv<<endl;
		*/
	int nByteSend=0;
	char bufSend[1024] = {0};
	memset(bufSend,0,sizeof(bufSend));
	lstrcpyn(bufSend,"Server端返回第一句",sizeof(bufSend));
	nByteSend = send(serConn,bufSend,strlen(bufSend)+1,0);
	if(nByteSend < 0)
	{
		cout<<"send fail!"<<endl;
	}

	closesocket(serConn);
	WSACleanup();
	return 0;
};
