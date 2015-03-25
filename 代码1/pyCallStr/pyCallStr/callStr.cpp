#include<iostream>
#include<Python.h>
#include<string>  
#include<vector>
#include<windows.h>

using namespace std;
//中文的内容读出来后要进行编码的转换，这个为转换函数：wchar_t to char
char *w2c(char *pcstr,const wchar_t *pwstr, int len)
{
	int nlength=wcslen(pwstr);
	//获取转换后的长度
	int nbytes = WideCharToMultiByte( 0, 0, pwstr, nlength, NULL,0,NULL, NULL ); 
	if(nbytes > len)   nbytes=len;
	// 通过以上得到的结果，转换unicode 字符为ascii 字符
	WideCharToMultiByte( 0,0, pwstr, nlength,   pcstr, nbytes, NULL,   NULL );
	return pcstr ;
}

std::wstring UT2WC(const char* buf)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);

	return std::wstring(&unicode[0]);
}



std::wstring ut2wc(const char* buf)
{
	int len=MultiByteToWideChar(CP_UTF8,0,buf,-1,NULL,NULL);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_UTF8,0,buf,-1,&unicode[0],len);
	return std::wstring(&unicode[0]);
}
int main()
{
	Py_Initialize();
	if ( !Py_IsInitialized() ) 
	{ 
		return -1; 
	} 
	PyObject *pModule,*pFunc,*pValue; 
	PyRun_SimpleString("import sys"); 
	PyRun_SimpleString("sys.path.append('./')");


	pModule = PyImport_ImportModule("getStr");
	pFunc = PyObject_GetAttrString(pModule, "getStr");
	pValue=PyEval_CallObject(pFunc, NULL);//执行该实例的成员函数

	char *sz;
	PyArg_Parse(pValue,"s",&sz);
	std::wstring wSz=UT2WC(sz);

	const wchar_t *t=wSz.c_str();
	char *pcstr = (char *)malloc(sizeof(char)*(2 * wcslen(t)+1));
	memset(pcstr , 0 , 2 * wcslen(t)+1 );
	w2c(pcstr,t,2 * wcslen(t)+1);
	cout<<""<<pcstr<<endl;
	cout<<strlen(pcstr)<<endl;
	free(pcstr);

	/*
	char * sz;
	PyArg_Parse(pValue,"s",&sz);
	cout<<sz<<endl;
	*/

	Py_Finalize();
	return 0;	
}