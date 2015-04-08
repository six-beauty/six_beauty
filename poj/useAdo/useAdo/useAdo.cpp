// useAdo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DataBase.h"
#include "useAdo.h"

bool InitInstance()
{
	AfxEnableControlContainer();
	//初始化 com
	CoInitialize(NULL);
	//初始化 OLE DLLs
	if(!AfxOleInit())
	{
		AfxMessageBox("初始化OLE DLLs失败！");
		return false;
	}
	return true;
}

bool unInitInstance()
{
	AfxOleTerm();
	CoUninitialize();
	return true;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	InitInstance();

	CAdoDataBase *pDataBase = new CAdoDataBase();
	pDataBase->SetConnectionInfo("192.168.3.214",1433,"LK78TestDB","sixbeauty","sanyue9394");
	pDataBase->OpenConnection();

	delete pDataBase;
	unInitInstance();
	return 0;
}
