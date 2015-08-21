#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/prepared_statement.h"
#include "stdlib.h"
#include <crtdbg.h>  

using namespace std;

typedef boost::scoped_ptr<sql::mysql::MySQL_Driver> MySQL_Driver;
typedef boost::scoped_ptr<sql::Connection> Connection;
typedef boost::scoped_ptr<sql::PreparedStatement> PreparedStatement;
typedef boost::scoped_ptr<sql::Statement> Statement;
typedef boost::scoped_ptr<sql::ResultSet> ResultSet;

#define CRTDBG_MAP_ALLOC  
int main()
{
	sql::mysql::MySQL_Driver *driver;
	Connection con(NULL);
	PreparedStatement prepareState(NULL);
	ResultSet result(NULL);

	//初始化驱动
	try
	{
		driver=(sql::mysql::get_mysql_driver_instance());
		//建立连接
		con.reset(driver->connect("tcp://127.0.0.1:3306","root","123456"));

		if(con->isValid() == false)
		{
		cout<<"连接失败"<<endl;
		return -1;
		}

		// 查询存储过程
		prepareState.reset(con->prepareStatement("call test.testproc1(?)"));
		prepareState->setInt(1,1001);
		prepareState->executeUpdate();

		result.reset(prepareState->getResultSet());
		// 输出结果	
		while(result->next())
		{
			int id = result->getInt("id");
			string name = result->getString("name");
			cout<<"testuser: "<< id <<" , "<<name<<endl;
		}

		result->close();
		prepareState->close();
		con->close();

		/*
		result.reset(NULL);
		prepareState.reset(NULL);
		con.reset(NULL);
		*/

		_CrtDumpMemoryLeaks(); 

	//_CrtDumpMemoryLeaks();  
	}
	catch (sql::SQLException &e)
	{
		cout<<e.what()<<",state:"<<e.getSQLState()<<endl;
		cout<<"errorCode: " << e.getErrorCode()<<endl;
	}

	return 0;
}

