#include<iostream>
#include<windows.h>

using namespace std;

int main()
{
	char szPath[128];
	memset(szPath,0,sizeof(szPath));
//	GetModuleFileName(NULL,szPath,sizeof(szPath));
	GetCurrentDirectory(sizeof(szPath),szPath);
	cout<<szPath<<endl;


	return 0;
}