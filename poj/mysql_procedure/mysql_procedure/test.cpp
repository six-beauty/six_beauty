#include "MySqlDataBase.h"
#include "leakcheck.h"
using namespace std;


int main()
{
	CMySqlDataBase mysqldb;
	try{
		mysqldb.SetConnectionInfo("127.0.0.1",3306,"test","root","123456");
		mysqldb.OpenConnect();

		/*
		ConstructOutput();
		for(int i=0;i<10000;++i)
		{
			mysqldb.Query("select * from test.test");
			while(mysqldb.NextFieldExist())
			{
				int id;
				std::string name;
				mysqldb.GetFieldValue("id",id);
				mysqldb.GetFieldValue("name",name);
				//cout<<"id:"<<id<<", name:"<<name<<endl;
			}
		}
		//mysqldb.Execute("insert into test.test values (1005,\"jibatao\")");
		*/
		ConstructOutput();
		for(int i = 0;i<10;++i)
		{
			mysqldb.PreparedExcute("call test.testproc5()");
			mysqldb.ExecuteCommand(true);
			//读第一组select
			while(mysqldb.NextFieldExist())
			{
				int id;
				std::string name;
				mysqldb.GetFieldValue("id",id);
				mysqldb.GetFieldValue("name",name);
				//cout<<"id:"<<id<<", name:"<<name<<endl;
			}
			/*
			//读第二组select
			if(mysqldb.GetNextResultSet())
			{
				while(mysqldb.NextFieldExist())
				{
					int id;
					std::string name;
					mysqldb.GetFieldValue("id",id);
					mysqldb.GetFieldValue("name",name);
					cout<<"id2:"<<id<<", name2:"<<name<<endl;
				}
			}
			*/
		}
		ConstructOutput();

		mysqldb.CloseConnect();
	}
	catch(CMySqlError *pSqlError)
	{
		cout<<pSqlError->getErrorCode()<<":"<<pSqlError->GetErrorDestribe()<<endl;
		mysqldb.CloseConnect();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}




