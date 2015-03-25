
#include"stdafx.h"
#include<iostream>
#include<string>
#include"json\json.h"


using namespace std; 
int main()
{
	Json::Value rootValue;
	string jsonstr;
	cin>>jsonstr;
	cout<<jsonstr<<endl;
	/*

	if(!Json::Reader().parse(jsonstr.c_str(),rootValue))
	{
		cout<<"解析出错"<<endl;
	}

	string msgStr=rootValue["err_msg"].asString().c_str();

	cout<<msgStr<<endl;

	rootValue["number"]="5201314";

	Json::FastWriter writer;
	jsonstr=writer.write(rootValue).c_str();
	cout<<rootValue["number"].asString().c_str();
	*/

	if(!Json::Reader().parse(jsonstr.c_str(),rootValue))
	{
		cout<<"解析出错"<<endl;
	}

	bool bSu = rootValue.isArray();
	return 0;

}

void parseArray(string strContent)
{
	Json::Value result;
	Json::Reader reader;

	if(!reader.parse(strContent,result)){
		return FALSE;
	}
	//m_MachineId.Format("%s",result["machineId"]);
	m_MachineId=result["machineId"].asCString();
	m_TableId=result["tableId"].asCString();
	m_StreamLine=result["streamLine"].asCString();
	m_PersonCount=result["personCount"].asCString();
	double totalPrice=0;
	Json::Value list=result["dishItem"];
	if(list.isArray()){
		int count=list.size();
		Json::Value element;
		for(int i=0;i<count;i++){
			element=list[i];
			OrderItem *pItem=new OrderItem();
			pItem->dishUnit=element["dishUnit"].asCString();
			pItem->dishMake=element["dishMake"].asCString();
			pItem->dishId=element["dishId"].asCString();
			pItem->dishName=element["dishName"].asCString();
			pItem->dishNum.Format("%d",element["dishNum"].asInt());
			pItem->dishPrice=element["dishPrice"].asCString();
			totalPrice+=atof(element["dishPrice"].asCString());
			m_Items.AddTail(pItem);

		}

	}
	m_Price.Format("%.2f",totalPrice);
}