#include "MySqlDataBase.h"
using namespace std;

int main()
{
	CMySqlDataBase mysqldb;
	try{
		mysqldb.SetConnectionInfo("127.0.0.1",3306,"test","root","123456");
		mysqldb.OpenConnect();
		mysqldb.Query("select * from test.test3");

		while(mysqldb.NextFieldExist())
		{
			int id;
			std::string date;
			mysqldb.GetFieldValue("id",id);
			mysqldb.GetFieldValue("date",date);
			cout<<"id:"<<id<<", date:"<<date<<endl;
		}

		mysqldb.PreparedExcute("call test.testproc1(?)");
		mysqldb.setInt(1,1002);
		mysqldb.ExecuteCommand(true);
		while(mysqldb.NextFieldExist())
		{
			int id;
			std::string name;
			mysqldb.GetFieldValue("id",id);
			mysqldb.GetFieldValue("name",name);
			cout<<"id:"<<id<<", name:"<<name<<endl;
		}

		mysqldb.CloseConnect();
	}
	catch(CMySqlError *pSqlError)
	{
		cout<<pSqlError->getErrorCode()<<":"<<pSqlError->GetErrorDestribe()<<endl;
		mysqldb.CloseConnect();
	}

	return 0;
}

