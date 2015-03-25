
////////////////////////////////////////////////////////////////
/*




// MFCFindFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
// 唯一的应用程序对象


inline void printlevel(int level)
{
	for(int i=0;i<level;i++)
		cout<<"\t";
	return ;
}
void myFindFile(int level,CString csPath)
{
	CString Path=csPath;
	Path.Append("\\*.*");

	WIN32_FIND_DATA FindData;
	HANDLE stillfind=FindFirstFile(Path,&FindData);
	if(stillfind==INVALID_HANDLE_VALUE )
		cout<<"file path error\n"<<endl;
	do
	{	
		if(FindData.cFileName[0] == _T('.')||FindData.cFileName[0] == _T('..'))
			continue;
		if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			CString newPath=csPath;
			newPath.Append("\\");
			newPath.Append(FindData.cFileName);
			printlevel(level);
			cout<<"["<<FindData.cFileName<<"]"<<endl;
			myFindFile(++level,newPath);
			level--;
			continue;
		}
		printlevel(level);
		cout<<FindData.cFileName<<endl;
		memset(&FindData,0,sizeof(WIN32_FIND_DATA));
	}
	while(FindNextFile(stillfind,&FindData));
}		
int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	
	/*
	WIN32_FIND_DATA fileData;
	HANDLE fileHd=FindFirstFile(L"F://KuGou",&fileData);
	wcout<<fileData.cFileName<<endl;
	memset(&fileData,0,sizeof(WIN32_FIND_DATA));
	while(FindNextFile(fileHd,&fileData))
	{
		wcout<<fileData.cFileName<<endl;
		memset(&fileData,0,sizeof(WIN32_FIND_DATA));
	}
	*/

//	myFindFile(0,"D:\\office2010");
/*	CString mystr(L"违法");
	wcout<<mystr.GetBuffer(10)<<endl;
	return 0;		*/
//}


*////////////////////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include<windows.h>
#include<iostream>
	using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CString szPath="D:\\office2010\\*.*";
	WIN32_FIND_DATA fdata; 
	HANDLE h_fdFile=FindFirstFile(szPath,&fdata);
	if(h_fdFile==INVALID_HANDLE_VALUE)
		cout<<"error"<<endl;

	do
	{
		cout<<fdata.cFileName<<endl;
	}while(FindNextFile(h_fdFile,&fdata));
	return 0;
}

