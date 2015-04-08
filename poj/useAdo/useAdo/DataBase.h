#ifndef _ADO_DATABASE_H
#define _ADO_DATABASE_H
#include <ICrsint.h>

//ADO 导入库
#import "MSADO15.DLL" rename_namespace("ADOCG") rename("EOF","EndOfFile")
using namespace ADOCG;

//COM 错误类型
typedef _com_error					CComError;							//COM 错误

//数据库错误代码
enum enADOErrorType
{
	ErrorType_Nothing				=0,									//没有错误
	ErrorType_Connect				=1,									//连接错误
	ErrorType_Other					=2,									//其他错误
};

//数据库错误接口
struct IADOError 
{
	//错误描述
	virtual LPCTSTR __cdecl GetErrorDescribe()=NULL;
	//错误类型
	virtual enADOErrorType __cdecl GetErrorType()=NULL;
};


//ADO 错误类
class CADOError : public IADOError
{
	//变量定义
protected:
	enADOErrorType					m_enErrorType;						//错误代号
	CString							m_strErrorDescribe;					//错误信息

	//函数定义
public:
	//构造函数
	CADOError();
	//析构函数
	virtual ~CADOError();

	//功能接口
public:
	//错误类型
	virtual enADOErrorType __cdecl GetErrorType() { return m_enErrorType; }
	//错误描述
	virtual LPCTSTR __cdecl GetErrorDescribe() { return m_strErrorDescribe; }

	//功能函数
public:
	//设置错误
	void SetErrorInfo(enADOErrorType enErrorType, LPCTSTR pszDescribe);
};

//////////////////////////////////////////////////////////////////////////

//数据库对象
class CAdoDataBase 
{
	//信息变量
protected:
	CADOError						m_ADOError;							//错误对象
	CString							m_strConnect;						//连接字符串
	CString							m_strErrorDescribe;					//错误信息

	//状态变量
protected:
	DWORD							m_dwConnectCount;					//重试次数
	DWORD							m_dwConnectErrorTime;				//错误时间
	const DWORD						m_dwResumeConnectCount;				//恢复次数
	const DWORD						m_dwResumeConnectTime;				//恢复时间

	//内核变量
protected:
	_CommandPtr						m_DBCommand;						//命令对象
	_RecordsetPtr					m_DBRecordset;						//记录集对象
	_ConnectionPtr					m_DBConnection;						//数据库对象

	//函数定义
public:
	//构造函数
	CAdoDataBase();
	//析构函数
	virtual ~CAdoDataBase();

	//基础接口
public:
	//释放对象
	virtual void __cdecl Release() {delete this; }
	//是否有效
	bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CAdoDataBase))?true:false; }
	
	//管理接口
public:
	//打开连接
	virtual bool __cdecl OpenConnection();
	//关闭记录
	virtual bool __cdecl CloseRecordset();
	//关闭连接
	virtual bool __cdecl CloseConnection();
	//重新连接
	virtual bool __cdecl TryConnectAgain(bool bFocusConnect, CComError * pComError);
	//设置信息
	virtual bool __cdecl SetConnectionInfo(LPCTSTR szIP, WORD wPort, LPCTSTR szData, LPCTSTR szName, LPCTSTR szPass);

	//状态接口
public:
	//是否连接错误
	virtual bool __cdecl IsConnectError();
	//是否打开
	virtual bool __cdecl IsRecordsetOpened();

	//记录集接口
public:
	//往下移动
	virtual void __cdecl MoveToNext();
	//移到开头
	virtual void __cdecl MoveToFirst();
	//是否结束
	virtual bool __cdecl IsEndRecordset();
	//获取数目
	virtual long __cdecl GetRecordCount();
	//获取大小
	virtual long __cdecl GetActualSize(LPCTSTR pszParamName);
	//绑定对象
	virtual bool __cdecl BindToRecordset(CADORecordBinding * pBind);

	//字段接口
public:
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, BYTE & bValue);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, WORD & wValue);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, INT & nValue);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, LONG & lValue);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, DWORD & ulValue);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, UINT & ulValue);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, DOUBLE & dbValue);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, __int64 & llValue);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, TCHAR szBuffer[], UINT uSize);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, COleDateTime & Time);
	//获取参数
	virtual bool __cdecl GetFieldValue(LPCTSTR lpFieldName, bool & bValue);

	//命令对象接口
public:
	//设置存储过程
	virtual void __cdecl SetSPName(LPCTSTR pszSpName);
	//插入参数
	virtual void __cdecl AddParamter(LPCTSTR pszName, ADOCG::ParameterDirectionEnum Direction, ADOCG::DataTypeEnum Type, long lSize, _variant_t & vtValue);
	//删除参数
	virtual void __cdecl ClearAllParameters();
	//获得参数
	virtual void __cdecl GetParameterValue(LPCTSTR pszParamName, _variant_t & vtValue);
	//获取返回数值
	virtual long __cdecl GetReturnValue();

	//执行接口
public:
	//执行语句
	virtual bool __cdecl Execute(LPCTSTR pszCommand);
	//执行命令
	virtual bool __cdecl ExecuteCommand(bool bRecordset);

	//内部函数
private:
	//获取错误
	LPCTSTR GetComErrorDescribe(CComError & ComError);
	//设置错误
	void SetErrorInfo(enADOErrorType enErrorType, LPCTSTR pszDescribe);
};


#endif
