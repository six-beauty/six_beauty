
#include "stdafx.h"
#include<windows.h>
#include<iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	LPCTSTR szPath="D:\\office2010\\*.*";
	WIN32_FIND_DATA fdata; 
	HANDLE h_fdFile=FindFirstFile("D:\\office2010\\*.*",&fdata);
	if(h_fdFile==INVALID_HANDLE_VALUE)
		cout<<"error"<<endl;

	do
	{
		cout<<fdata.cFileName<<endl;
	}while(FindNextFile(h_fdFile,&fdata));
	return 0;
}

