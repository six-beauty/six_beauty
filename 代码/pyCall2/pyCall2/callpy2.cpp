
#include "Python.h" 
#include <iostream>
#include <string>

using namespace std;


int main(void)
{
	Py_Initialize(); 
	// 检查初始化是否成功  
	if ( !Py_IsInitialized() ) 
	{ 
		return -1; 
	} 
	
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");
	
	std::wstring str = L"pyCalculate"; 
	
	PyObject* pName = PyUnicode_FromUnicode(str.c_str(),str.size());
	//导入模块
	PyObject* pModule = PyImport_Import(pName);

	//导入类模块
	PyObject* pClassComputer = PyObject_GetAttrString(pModule,"computer");

	//PyObject* pInstanceComputer = PyInstanceMethod_New(pClassComputer); 
	//if(!PyInstanceMethod_Check(pInstanceComputer))
	//{
	//	cout<<"初始化类失败!"<<endl;
	//	return -1;
	//}

	PyObject* pClass=PyEval_CallObject(pClassComputer,NULL);
	PyObject* pFunc=PyObject_GetAttrString(pClass,"calculate");
	if (!pFunc || !PyCallable_Check(pFunc))
	{
		printf("can't findfunction [AddMult]\n");
		return -1;
	}
	
	// 调用Python函数
	//PyObject* pValue=PyObject_CallFunction(pFunc, "s","1+2*3-3/2");
	//cout<<PyFloat_AS_DOUBLE(pValue)<<endl;
	
	
	PyObject* pArg = PyTuple_New(2);
	PyTuple_SetItem(pArg, 0, Py_BuildValue("i",1));
	PyTuple_SetItem(pArg, 1, Py_BuildValue("i",2));

	//PyObject* pValue=PyEval_CallObject(pFunc,pArg);
	PyObject* pValue=PyObject_CallFunction(pFunc, NULL);

	char *sz=new char(32);
	PyArg_Parse(pValue,"s",&sz);
	cout<<sz<<endl;

	delete sz;

	Py_Finalize();

	return 0;
}

	

