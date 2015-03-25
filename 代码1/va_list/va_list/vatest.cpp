#include<iostream>
#include<stdarg.h>
using namespace std;

void  LogInfo(char *szFormat,...)
{
	char szBuf[4096]={};
	va_list args;							//第一步
	va_start(args,szFormat);				//第二步
	_vsnprintf(szBuf,4096,szFormat,args);	//第三步

	//在这里对字符串  szBuf  作处理，输出到日志文件或直接打印信息
	cout<<szBuf<<endl;
	//********************************************************

	va_end(args);							//第四步

	return ;
}

int main()
{
	LogInfo("收到网关服务器中转命令，主命令:%d,副命令:%d,附带信息",1,2,"hahahaha");

	//拼接日志字符串
	char logStr[4096]={};
	sprintf(logStr,"收到网关服务器中转命令，主命令:%d,副命令:%d,附带信息",1,2,"hahahaha");
	//输出
	cout<<logStr<<endl;
	//********************************************************


	return 0;
}