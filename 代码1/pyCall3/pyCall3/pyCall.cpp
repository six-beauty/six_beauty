
#include "Python.h" 
#include <iostream>
#include <string> 
#include <Windows.h>

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


int main()
{
	Py_Initialize(); 
	// 检查初始化是否成功  
	if ( !Py_IsInitialized() ) 
	{ 
		cout<<"初始化python失败"<<endl;
		return -1; 
	}
	PyRun_SimpleString("import sys"); 
	PyRun_SimpleString("sys.path.append('./')");


	PyObject *pModule = PyImport_ImportModule("pyExcel");

	//导入类模块
	PyObject* pClassComputer = PyObject_GetAttrString(pModule,"pyExcel");

	//获取Excel文件名和index
	string fileName="1.xlsx";
	int indexNum=0;
	//cout<<"请输入excel的文件名（完整名字带后缀）：";
	//cin>>fileName;
	//cout<<endl<<"请输入excel要打开的Index:";
	//cin>>indexNum;
	//cout<<endl<<"========================================="<<endl;

	PyObject* pArg = PyTuple_New(2);

	PyTuple_SetItem(pArg, 0, Py_BuildValue("s",fileName.c_str()));
	PyTuple_SetItem(pArg, 1, Py_BuildValue("i",indexNum));

	PyObject* pClass=PyEval_CallObject(pClassComputer,pArg);

	//获取pyExcel中的各种函数;
	PyObject* pGetCell=PyObject_GetAttrString(pClass,"getCell");
	PyObject* pGetRows=PyObject_GetAttrString(pClass,"getRows");
	PyObject* pGetCols=PyObject_GetAttrString(pClass,"getCols");
	PyObject* pCellType=PyObject_GetAttrString(pClass,"cellType");

	if (!pGetCell || !pGetCols || !pGetRows || !pCellType ||
		!PyCallable_Check(pGetCell) || !PyCallable_Check(pGetCols) ||
		!PyCallable_Check(pGetRows) || !PyCallable_Check(pCellType) )
	{
		cout<<"获取类中的函数失败！"<<endl;
		return -1;
	}

	PyObject *pValue=PyObject_CallFunction(pGetCell, "i,i",0,0);		//执行该实例的成员函数
	/*
	const wchar_t *t;
	PyArg_Parse(pValue,"s",&t);
	char *pcstr = (char *)malloc(sizeof(char)*(2 * wcslen(t)+1));
	memset(pcstr , 0 , 2 * wcslen(t)+1 );
	w2c(pcstr,t,2 * wcslen(t)+1);
	cout<<"result:"<<pcstr<<endl;
	cout<<strlen(pcstr)<<endl;
	free(pcstr);
	*/

	char *t;
	PyArg_Parse(pValue,"s",&t);
	wcout<<t<<endl;

	Py_Finalize();
	return 0;	
}
