//转换unicode代码为Ansi代码的程序
//programed by six_beauty

#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//unicode转ansi
std::string utf82ansi(const char* utf8sz)
{
	int nUnichars = MultiByteToWideChar(CP_UTF8,0,utf8sz,-1,NULL,0);
	std::vector<wchar_t> wchars(nUnichars);
	MultiByteToWideChar(CP_UTF8,0,utf8sz,-1,&wchars[0],(int)wchars.size());
	int nAnsiChars = WideCharToMultiByte(CP_ACP,0,&wchars[0],-1,NULL,0,NULL,NULL);
	std::vector<char> ansichars(nAnsiChars);
	WideCharToMultiByte(CP_ACP,0,&wchars[0],-1,&ansichars[0],(int)ansichars.size(),NULL,NULL);
	return std::string(&ansichars[0]);
}

//ansi转unicode
std::wstring ansi2utf8(const wchar_t* ansisz)
{
	int nAnsiChars = WideCharToMultiByte(CP_ACP,0,ansisz,-1,NULL,0,NULL,NULL);
	std::vector<char> ansichars(nAnsiChars);
	WideCharToMultiByte(CP_ACP,0,ansisz,-1,&ansichars[0],(int)ansichars.size(),NULL,NULL);
	int nUnichars = MultiByteToWideChar(CP_UTF8,0,&ansichars[0],-1,NULL,0);
	std::vector<wchar_t> wchars(nUnichars);
	MultiByteToWideChar(CP_UTF8,0,&ansichars[0],-1,&wchars[0],(int)wchars.size());
	return std::wstring(&wchars[0]);
}


//ansi转unicode
std::wstring Ansi2utf8(const char* ansichars)
{
	int nUnichars = MultiByteToWideChar(CP_UTF8,0,ansichars,-1,NULL,0);
	std::vector<wchar_t> wchars(nUnichars);
	MultiByteToWideChar(CP_UTF8,0,ansichars,-1,&wchars[0],(int)wchars.size());
	return std::wstring(&wchars[0]);
}

int main()
{
	ifstream in("F:\\赖杨俊 vimrc.txt",ios::binary|ios::in);					//读入文件
	ofstream out("F:\\vimrc.txt",ios::binary|ios::out);						//写入文件
	if(!in)
	{
		cout<<"no exit!"<<endl;
		return -1;
	}
	in.seekg(0,ios::beg);

	std::ostringstream tmp; 
	tmp << in.rdbuf(); 
	std::string str = tmp.str();

	std::wstring unicin;
	unicin.resize(str.length()*2+1);
	std::copy(str.begin(), str.end(), unicin.begin());

	//std::wstring unicout=ansi2utf8(unicin.c_str());
	std::wstring unicout=Ansi2utf8(str.c_str());

	std::string ansiout;
	ansiout.resize(unicout.length()*2+1);
	std::copy(unicout.begin(), unicout.end(), ansiout.begin());

	out<<ansiout;


	in.close();
	out.close();
}