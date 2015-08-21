#ifndef __MYSQL_DATABASE_H
#define __MYSQL_DATABASE_H

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/statement.h"
#include <map>

typedef boost::scoped_ptr<sql::Connection> Connection;
typedef boost::scoped_ptr<sql::PreparedStatement> PreparedStatement;
typedef boost::scoped_ptr<sql::Statement> Statement;
typedef boost::scoped_ptr<sql::ResultSet> ResultSet;
typedef sql::mysql::MySQL_Driver MySQL_Driver;

//mysql 错误类
class CMySqlError
{
	//存储变量
protected:
	int						m_ErrorCode;				
	std::string				m_strErrorDescribe;			

public:
	//构造函数
	CMySqlError();
	//析构函数
	~CMySqlError();
public:
	//获取ErrorCode
	int getErrorCode(){	return m_ErrorCode;	}	
	//错误描述
	std::string GetErrorDestribe(){	return m_strErrorDescribe;	}

public:
	//设置错误
	void SetErrorInfo(sql::SQLException &e);
};

class CMySqlDataBase
{	
	//信息变量
protected:
	CMySqlError							m_MySqlError;			//当前错误信息
	std::map<std::string, std::string>	m_ConnectProperties;	//连接信息

	//状态变量
protected:
	const unsigned int		m_dwTryConnectTimes;

	//连接变量
protected:
	Connection			m_DBConnect;
	PreparedStatement	m_DBPrepareState;
	ResultSet			m_DBRecordSet;

	//函数定义
public:
	//构造函数
	CMySqlDataBase();
	//析构函数
	~CMySqlDataBase();

	//管理接口
public:
	//打开连接
	bool OpenConnect();
	//关闭记录
	bool CloseRecordset();
	//关闭连接
	bool CloseConnect();
	//重新连接(未实现)
	bool TryConnectAgain();
	//设置信息
	bool SetConnectionInfo(const std::string &hostIp,unsigned short hostPort,const std::string &dataBaseName,const std::string &userName,const std::string &password);

	//状态接口(未实现)
public:
	//是否连接错误
	bool IsConnectError();
	//是否打开
	bool IsRecordsetOpened();

	//
public:
	//准备prepareState
	bool PreparedExcute(const std::string &szCommand);

	bool setBigInt(unsigned int parameterIndex, const std::string& value);
	
	bool setBlob(unsigned int parameterIndex, std::istream * blob);			//长文本字符串

	bool setBoolean(unsigned int parameterIndex, bool value);

	bool setDateTime(unsigned int parameterIndex, const std::string& value);

	bool setDouble(unsigned int parameterIndex, double value);

	bool setInt(unsigned int parameterIndex, int32_t value);

	bool setUInt(unsigned int parameterIndex, uint32_t value);

	bool setInt64(unsigned int parameterIndex, int64_t value);

	bool setUInt64(unsigned int parameterIndex, uint64_t value);

	bool setString(unsigned int parameterIndex, const std::string& value);

	bool setNull(unsigned int parameterIndex, int sqlType);

	//执行命令(存储过程）
	bool ExecuteCommand(bool bRecordset);

	//执行语句接口
public:
	//执行查询(Select)
	bool Query(const std::string &szCommand);
	//执行语句(Insert,Update,Delete)
	bool Execute(const std::string &szCommand);

	//字段接口
	/* next() must been used before getdata */
public:
	//get Next Record set
	bool GetNextResultSet();
	//move resultset to the nth result in the set
	bool NextFieldExist();
	//获取参数
	bool GetFieldValue(const std::string& columnLabel,bool &bValue);
	//获取参数
	bool GetFieldValue(const std::string& columnLabel,long double &dbValue);
	//获取参数
	bool GetFieldValue(const std::string& columnLabel,int32_t &nValue);
	//获取参数
	bool GetFieldValue(const std::string& columnLabel,uint32_t &uValue);
	//获取参数
	bool GetFieldValue(const std::string& columnLabel,int64_t &llValue);
	//获取参数
	bool GetFieldValue(const std::string& columnLabel,uint64_t &lluValue);
	//获取参数
	bool GetFieldValue(const std::string& columnLabel,char szBuffer[],uint32_t uSize);
	//获取参数
	bool GetFieldValue(const std::string& columnLabel,std::string &szValue);

	//内部函数
private:
	//设置错误
	void SetErrorInfo(sql::SQLException &e);
};

#endif
