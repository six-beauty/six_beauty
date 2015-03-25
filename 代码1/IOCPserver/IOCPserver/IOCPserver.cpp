// IOCPserver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpSrv.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TcpSrv myserver;
	myserver.startup();
	myserver.closeIocp();
	return 0;
}

