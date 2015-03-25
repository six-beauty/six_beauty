#include<iostream>
#include<string>
#include<windows.h>

using namespace std;
bool visitDirectory(string filepath) 
{
	filepath = filepath + "\\*";
	WIN32_FIND_DATA fdate;
	ZeroMemory(&fdate,sizeof(WIN32_FIND_DATA));
	HANDLE hFile=FindFirstFile(filepath.c_str(),&fdate);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		cout<<"no thing haved found!"<<endl;
		return false;
	}
	do 
	{
		if(fdate.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)
		{
			if(strcmp(fdate.cFileName,".") != 0 && strcmp(fdate.cFileName,"..") != 0)
			{
				cout<<"["<<fdate.cFileName<<"]is directory"<<endl;
			}
		}
		ZeroMemory(&fdate,sizeof(WIN32_FIND_DATA));
	} while (FindNextFile(hFile,&fdate));
	return true;
}

int main()
{
	string filePath = "E://GitHub";
	visitDirectory(filePath);

	return 0;
}
