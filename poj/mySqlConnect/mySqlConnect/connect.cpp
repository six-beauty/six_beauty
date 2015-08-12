#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/statement.h"
#include "stdlib.h"

using namespace std;

int main()
{
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *state;
	sql::ResultSet *result;

	//初始化驱动
	driver = sql::mysql::get_mysql_driver_instance();
	//建立连接
	con = driver->connect("tcp://127.0.0.1:3306","root","123456");

	if(con->isValid() == false)
	{
		cout<<"连接失败"<<endl;
		return -1;
	}
	state = con->createStatement();

	state->execute("use test");
	//查询
	result = state->executeQuery("select * from test");

	// 输出结果	
	while(result->next())
	{
		int id = result->getInt("id");
		string name = result->getString("name");
		cout<<"testuser: "<< id <<" , "<<name<<endl;
	}

	result->close();

	state->close();
	con->close();

	return 0;
}
