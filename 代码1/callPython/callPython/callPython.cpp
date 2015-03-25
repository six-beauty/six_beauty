
#include "Python.h" 
#include <iostream>
#include <string>
#include <codecvt>
using namespace std;

void printDict(PyObject* obj) {
	if (!PyDict_Check(obj))
		return;
	PyObject *k, *keys;
	keys = PyDict_Keys(obj);
	for (int i = 0; i < PyList_GET_SIZE(keys); i++) {
		k = PyList_GET_ITEM(keys, i);
		char* c_name = PyBytes_AsString(k);
		printf("%s\n", c_name);
	}
}


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
	/*	
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv; 

	std::string  sr= conv.to_bytes(str); 
	//导入模块
	PyObject* pModule = PyImport_ImportModule(sr.c_str());
	*/
	PyObject* pName = PyUnicode_FromUnicode(str.c_str(),str.size());
	//导入模块
	PyObject* pModule = PyImport_Import(pName);

	PyObject* calFunc = PyObject_GetAttrString(pModule,"calculate");

	// 调用Python函数
	PyObject* pValue=PyObject_CallFunction(calFunc, "s","1+2*3-3/2");
	cout<<PyFloat_AS_DOUBLE(pValue)<<endl;

	//演示函数调用
	/*PyObject* pClassComputer = PyDict_GetItemString(pDict,"computer");
	PyObject* pInstanceComputer = PyInstanceMethod_New(pClassComputer); 

	if(!PyInstanceMethod_Check(pInstanceComputer))
	{
		cout<<"初始化类失败!"<<endl;
		return -1;
	}*/
	/*PyObject* pValue=PyObject_GC_New(pInstanceComputer, "calculate","s", "1+2*3-3/2");
	cout<<PyFloat_AS_DOUBLE(pValue)<<endl;*/
//	Py_DECREF(pInstanceComputer);

	Py_Finalize();

	return 0;
}

	

