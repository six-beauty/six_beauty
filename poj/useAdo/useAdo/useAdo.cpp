// useAdo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DataBase.h"
#include "useAdo.h"
#include "debug.h"

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

void myRun(CAdoDataBase *pDataBase)
{
	try
	{
		pDataBase->ClearAllParameters();
		pDataBase->SetSPName("GSP_GP_LoadGameRoomConfig");
		pDataBase->AddParamter(_TEXT("RETURN_VALUE"),adParamReturnValue,adInteger,sizeof(long),_variant_t(0L));
		pDataBase->AddParamter(_TEXT("@serverID"),adParamInput,adInteger,sizeof(long),_variant_t(7794L));
		pDataBase->ExecuteCommand(true);

		long lRetValue = pDataBase->GetReturnValue();
		long kindID;
		char roomName[64]={0};
		pDataBase->GetFieldValue(_TEXT("KindID"),kindID);
		pDataBase->GetFieldValue(_TEXT("RoomName"),roomName,sizeof(roomName));
		pDataBase->CloseRecordset();
	//	CString valMsg;
	//	valMsg.Format("查询到房间kindID:%d,房间名：%s",kindID,roomName);
	//	std::cout<<valMsg<<std::endl;
	}
	catch (IADOError* pIADOError)
	{
		CString errmsg;
		errmsg.Format(_T("数据库操作发生异常:%s"),pIADOError->GetErrorDescribe());
		AfxMessageBox(errmsg);
	}

}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	InitInstance();

	CAdoDataBase *pDataBase = new CAdoDataBase();
	pDataBase->SetConnectionInfo("192.168.3.214",1433,"LK78TestDB","sixbeauty","sanyue9394");
	pDataBase->OpenConnection();
	ConstructOutput();
	for(int i=0;i<100;++i)
		myRun(pDataBase);
	delete pDataBase;
	unInitInstance();
	ConstructOutput();

	return 0;
}
