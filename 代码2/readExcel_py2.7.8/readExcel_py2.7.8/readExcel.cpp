#include<iostream>
#include"Python.h"
#include<string>  
#include<vector>
#include<iomanip>
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

int main(void)
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

	//std::wstring str = L"pyExcel"; 

	//PyObject* pName = PyUnicode_FromUnicode(str.c_str(),str.size());
	////导入模块
	//PyObject* pModule = PyImport_Import(pName);

	PyObject* pModule= PyImport_ImportModule("pyExcel");
	if(!pModule)
	{
		cout<<"Excel打开脚本失败！"<<endl;
		return -1;
	}

	//导入类模块
	PyObject* pClassComputer = PyObject_GetAttrString(pModule,"pyExcel");

	if(!pClassComputer)
	{
		cout<<"Excel读取脚本失败！"<<endl;
		return -1;
	}

	//获取Excel文件名和index
	string fileName;
	int indexNum;
	cout<<"请输入excel的文件名（完整名字带后缀）：";
	cin>>fileName;
	cout<<endl<<"请输入excel要打开的Index:";
	cin>>indexNum;
	cout<<endl<<"================================================"<<endl;

	PyObject* pArg = PyTuple_New(2);


	PyTuple_SetItem(pArg, 0, Py_BuildValue("s",fileName.c_str()));
	PyTuple_SetItem(pArg, 1, Py_BuildValue("i",indexNum));

	PyObject* pClass=PyEval_CallObject(pClassComputer,pArg);
	if (!pClass )
	{
		cout<<"打开Excel失败，请确认文件存在!"<<endl;;
		return -1;
	}

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

	// 调用Python函数

	PyObject* pRows=PyEval_CallObject(pGetRows,NULL);
	PyObject* pCols=PyEval_CallObject(pGetCols,NULL);
	PyObject* pCell=NULL;
	PyObject* pType=NULL;
	for(int i=0;i<PyLong_AsLong(pRows);i++)
	{
		for(int j=0;j<PyLong_AsLong(pCols);j++)
		{
			pCell=PyObject_CallFunction(pGetCell, "i,i",i,j);
			pType=PyObject_CallFunction(pCellType, "i,i",i,j);

			if(pCell==NULL || pType==NULL)
			{
				cout<<"获取Excel中的单元值失败!"<<endl;
				return -1;
			}

			cout<<right;
			if(PyLong_AsLong(pType)==0)
			{
				cout<<setw(10)<<PyFloat_AS_DOUBLE(pCell)<<"|";
			}else
			{
				char *sz;
				PyArg_Parse(pCell,"s",&sz);
				std::wstring wSz=UT2WC(sz);

				const wchar_t *t=wSz.c_str();
				char *pcstr = (char *)malloc(sizeof(char)*(2 * wcslen(t)+1));
				memset(pcstr , 0 , 2 * wcslen(t)+1 );
				w2c(pcstr,t,2 * wcslen(t)+1);
				cout<<setw(10)<<pcstr<<"|";
				free(pcstr);
				
			}
		}

		cout<<endl;
		for(int j=0;j<PyLong_AsLong(pCols);j++)
			cout<<"------------";
		cout<<endl;
	}


	system("pause");

	Py_Finalize();

	return 0;
}



