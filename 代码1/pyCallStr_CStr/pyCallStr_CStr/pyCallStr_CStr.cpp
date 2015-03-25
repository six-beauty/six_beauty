// pyCallStr_CStr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<Python.h>
#include<string>  
using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
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

	//	PyArg_Parse(pValue,"s",&sz);

	TCHAR *t;
	PyArg_Parse(pValue,"s",&t);
	cout<<t<<endl;
	


	Py_Finalize();
	return 0;
}
