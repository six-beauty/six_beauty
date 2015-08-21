#include "MySqlDataBase.h"
#include <sstream>

CMySqlError::CMySqlError()
{
}

CMySqlError::~CMySqlError()
{
}

void CMySqlError::SetErrorInfo(sql::SQLException &e)
{
	m_ErrorCode = e.getErrorCode();
	m_strErrorDescribe = e.what();

	throw this;
}

CMySqlDataBase::CMySqlDataBase():m_DBConnect(NULL),m_DBPrepareState(NULL),m_DBRecordSet(NULL),m_dwTryConnectTimes(1)
{	
}

CMySqlDataBase::~CMySqlDataBase()
{
	try
	{
		CloseConnect();

		m_DBRecordSet.reset(NULL);
		m_DBPrepareState.reset(NULL);
		m_DBConnect.reset(NULL);
	}
	catch(sql::SQLException &e) { SetErrorInfo(e);}
}

//设置错误
void CMySqlDataBase::SetErrorInfo(sql::SQLException &e)
{
	m_MySqlError.SetErrorInfo(e);
}

//打开连接
bool CMySqlDataBase::OpenConnect()
{
	//建立连接
	try
	{
		sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();

		m_DBConnect.reset(driver->connect(m_ConnectProperties["hostName"],m_ConnectProperties["userName"],m_ConnectProperties["password"]));
		m_DBConnect->setSchema(m_ConnectProperties["schema"]);
	}
	catch(sql::SQLException &e) { SetErrorInfo(e);}

	return true;
}

//关闭记录
bool CMySqlDataBase::CloseRecordset()
{
	try
	{
		if(m_DBPrepareState != NULL)
		{
			while(m_DBPrepareState->getMoreResults())
				m_DBRecordSet.reset(m_DBPrepareState->getResultSet());

			m_DBPrepareState.reset(NULL);
		}

		if(m_DBRecordSet != NULL)
			m_DBRecordSet.reset(NULL);
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//关闭连接
bool CMySqlDataBase::CloseConnect()
{
	try
	{
		CloseRecordset();

		//close connect
		if(m_DBConnect != NULL)
		{
			m_DBConnect.reset(NULL);
		}

		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//设置信息
bool CMySqlDataBase::SetConnectionInfo(const std::string &hostIp,unsigned short hostPort,const std::string &dataBaseName,const std::string &userName,const std::string &password)
{
	try
	{	
		std::stringstream hostss;
		hostss<<"tcp://"<<hostIp<<":"<<hostPort;

		m_ConnectProperties["hostName"] = hostss.str();
		m_ConnectProperties["userName"] = userName;
		m_ConnectProperties["password"] = password;
		m_ConnectProperties["schema"] = dataBaseName;

		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//是否打开
bool CMySqlDataBase::IsRecordsetOpened()
{
	if(m_DBRecordSet == NULL)
		return false; 

	if(m_DBRecordSet->isClosed())
		return false;

	return true;
}

//准备prepareState
bool CMySqlDataBase::PreparedExcute(const std::string &szCommand)
{
	if(szCommand.empty())	return false;

	//close RecordSet;
	CloseRecordset();
	try
	{
		m_DBPrepareState.reset(m_DBConnect->prepareStatement(szCommand));
		m_DBPrepareState->clearParameters();

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setBigInt(unsigned int parameterIndex, const std::string& value)
{
	try
	{
		m_DBPrepareState->setBigInt(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setBlob(unsigned int parameterIndex, std::istream * value)			//长文本字符串
{
	try
	{
		m_DBPrepareState->setBlob(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setBoolean(unsigned int parameterIndex, bool value)
{
	try
	{
		m_DBPrepareState->setBoolean(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setDateTime(unsigned int parameterIndex, const std::string& value)
{
	try
	{
		m_DBPrepareState->setDateTime(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setDouble(unsigned int parameterIndex, double value)
{
	try
	{
		m_DBPrepareState->setDouble(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setInt(unsigned int parameterIndex, int32_t value)
{
	try
	{
		m_DBPrepareState->setInt(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setUInt(unsigned int parameterIndex, uint32_t value)
{
	try
	{
		m_DBPrepareState->setUInt(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setInt64(unsigned int parameterIndex, int64_t value)
{
	try
	{
		m_DBPrepareState->setInt64(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setUInt64(unsigned int parameterIndex, uint64_t value)
{
	try
	{
		m_DBPrepareState->setUInt64(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setString(unsigned int parameterIndex, const std::string& value)
{
	try
	{
		m_DBPrepareState->setString(parameterIndex,value);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

bool CMySqlDataBase::setNull(unsigned int parameterIndex, int sqlType)
{
	try
	{
		m_DBPrepareState->setNull(parameterIndex,sqlType);

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//执行命令(存储过程）
bool CMySqlDataBase::ExecuteCommand(bool bRecordset)
{
	try
	{
		m_DBPrepareState->executeUpdate();

		if(bRecordset)
			m_DBRecordSet.reset(m_DBPrepareState->getResultSet());

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//执行查询(Select)
bool CMySqlDataBase::Query(const std::string &szCommand)
{
	if(szCommand.empty())	return false;

	//close RecordSet;
	CloseRecordset();
	try
	{
		m_DBPrepareState.reset(m_DBConnect->prepareStatement(szCommand));

		m_DBPrepareState->executeUpdate();
		m_DBRecordSet.reset(m_DBPrepareState->getResultSet());
		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//执行语句(Insert,Update,Delete)
bool CMySqlDataBase::Execute(const std::string &szCommand)
{
	if(szCommand.empty())	return false;

	//close RecordSet;
	CloseRecordset();
	try
	{
		m_DBPrepareState.reset(m_DBConnect->prepareStatement(szCommand));
		m_DBPrepareState->executeUpdate();

		return true;
	} 
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//get Next Record set
bool CMySqlDataBase::GetNextResultSet()
{
	if(m_DBPrepareState == NULL)
		return false;

	if(m_DBPrepareState->getMoreResults())
	{
		m_DBRecordSet.reset(m_DBPrepareState->getResultSet());
		return true;
	}
	return false;
}

//next
bool CMySqlDataBase::NextFieldExist()
{
	if(m_DBRecordSet == NULL)
		return false;

	return m_DBRecordSet->next();
}

//获取参数
bool CMySqlDataBase::GetFieldValue(const std::string& columnLabel,bool &bValue)
{
	bValue = false;

	if(!IsRecordsetOpened())
		return false;

	try
	{
		bValue =  m_DBRecordSet->getBoolean(columnLabel);
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//获取参数
bool CMySqlDataBase::GetFieldValue(const std::string& columnLabel,long double &dbValue)
{
	dbValue = 0.00;

	if(!IsRecordsetOpened())
		return false;

	try
	{
		dbValue =  m_DBRecordSet->getDouble(columnLabel);
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//获取参数
bool CMySqlDataBase::GetFieldValue(const std::string& columnLabel,int32_t &nValue)
{
	nValue = 0;

	if(!IsRecordsetOpened())
		return false;

	try
	{
		nValue =  m_DBRecordSet->getInt(columnLabel);
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//获取参数
bool CMySqlDataBase::GetFieldValue(const std::string& columnLabel,uint32_t &uValue)
{
	uValue = 0;

	if(!IsRecordsetOpened())
		return false;

	try
	{
		uValue =  m_DBRecordSet->getUInt(columnLabel);
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//获取参数
bool CMySqlDataBase::GetFieldValue(const std::string& columnLabel,int64_t &llValue)
{
	llValue = 0;

	if(!IsRecordsetOpened())
		return false;

	try
	{
		llValue =  m_DBRecordSet->getInt64(columnLabel);
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//获取参数
bool CMySqlDataBase::GetFieldValue(const std::string& columnLabel,uint64_t &lluValue)
{
	lluValue = 0;

	if(!IsRecordsetOpened())
		return false;

	try
	{
		lluValue =  m_DBRecordSet->getUInt64(columnLabel);
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//获取参数
bool CMySqlDataBase::GetFieldValue(const std::string& columnLabel,char szBuffer[],uint32_t uSize)
{
	memset(szBuffer,0,uSize);

	if(!IsRecordsetOpened())
		return false;

	try
	{
		stl::SQLString tempstr =  m_DBRecordSet->getString(columnLabel);
		strncpy(szBuffer,tempstr.c_str(),uSize-1);
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}

//获取参数
bool CMySqlDataBase::GetFieldValue(const std::string& columnLabel,std::string &szValue)
{
	if(!IsRecordsetOpened())
		return false;

	try
	{
		szValue =  m_DBRecordSet->getString(columnLabel).asStdString();
		return true;
	}
	catch (sql::SQLException &e) { SetErrorInfo(e);}

	return false;
}
