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

//mysql ������
class CMySqlError
{
	//�洢����
protected:
	int						m_ErrorCode;				
	std::string				m_strErrorDescribe;			

public:
	//���캯��
	CMySqlError();
	//��������
	~CMySqlError();
public:
	//��ȡErrorCode
	int getErrorCode(){	return m_ErrorCode;	}	
	//��������
	std::string GetErrorDestribe(){	return m_strErrorDescribe;	}

public:
	//���ô���
	void SetErrorInfo(sql::SQLException &e);
};

class CMySqlDataBase
{	
	//��Ϣ����
protected:
	CMySqlError							m_MySqlError;			//��ǰ������Ϣ
	std::map<std::string, std::string>	m_ConnectProperties;	//������Ϣ

	//״̬����
protected:
	const unsigned int		m_dwTryConnectTimes;

	//���ӱ���
protected:
	Connection			m_DBConnect;
	PreparedStatement	m_DBPrepareState;
	ResultSet			m_DBRecordSet;

	//��������
public:
	//���캯��
	CMySqlDataBase();
	//��������
	~CMySqlDataBase();

	//����ӿ�
public:
	//������
	bool OpenConnect();
	//�رռ�¼
	bool CloseRecordset();
	//�ر�����
	bool CloseConnect();
	//��������(δʵ��)
	bool TryConnectAgain();
	//������Ϣ
	bool SetConnectionInfo(const std::string &hostIp,unsigned short hostPort,const std::string &dataBaseName,const std::string &userName,const std::string &password);

	//״̬�ӿ�(δʵ��)
public:
	//�Ƿ����Ӵ���
	bool IsConnectError();
	//�Ƿ��
	bool IsRecordsetOpened();

	//
public:
	//׼��prepareState
	bool PreparedExcute(const std::string &szCommand);

	bool setBigInt(unsigned int parameterIndex, const std::string& value);
	
	bool setBlob(unsigned int parameterIndex, std::istream * blob);			//���ı��ַ���

	bool setBoolean(unsigned int parameterIndex, bool value);

	bool setDateTime(unsigned int parameterIndex, const std::string& value);

	bool setDouble(unsigned int parameterIndex, double value);

	bool setInt(unsigned int parameterIndex, int32_t value);

	bool setUInt(unsigned int parameterIndex, uint32_t value);

	bool setInt64(unsigned int parameterIndex, int64_t value);

	bool setUInt64(unsigned int parameterIndex, uint64_t value);

	bool setString(unsigned int parameterIndex, const std::string& value);

	bool setNull(unsigned int parameterIndex, int sqlType);

	//ִ������(�洢���̣�
	bool ExecuteCommand(bool bRecordset);

	//ִ�����ӿ�
public:
	//ִ�в�ѯ(Select)
	bool Query(const std::string &szCommand);
	//ִ�����(Insert,Update,Delete)
	bool Execute(const std::string &szCommand);

	//�ֶνӿ�
	/* next() must been used before getdata */
public:
	//get Next Record set
	bool GetNextResultSet();
	//move resultset to the nth result in the set
	bool NextFieldExist();
	//��ȡ����
	bool GetFieldValue(const std::string& columnLabel,bool &bValue);
	//��ȡ����
	bool GetFieldValue(const std::string& columnLabel,long double &dbValue);
	//��ȡ����
	bool GetFieldValue(const std::string& columnLabel,int32_t &nValue);
	//��ȡ����
	bool GetFieldValue(const std::string& columnLabel,uint32_t &uValue);
	//��ȡ����
	bool GetFieldValue(const std::string& columnLabel,int64_t &llValue);
	//��ȡ����
	bool GetFieldValue(const std::string& columnLabel,uint64_t &lluValue);
	//��ȡ����
	bool GetFieldValue(const std::string& columnLabel,char szBuffer[],uint32_t uSize);
	//��ȡ����
	bool GetFieldValue(const std::string& columnLabel,std::string &szValue);

	//�ڲ�����
private:
	//���ô���
	void SetErrorInfo(sql::SQLException &e);
};

#endif
