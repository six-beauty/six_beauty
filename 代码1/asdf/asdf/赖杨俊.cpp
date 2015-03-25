// asdf.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
void delPoint(CString &sourStr)
{
	int ptPos=sourStr.Find('.');
	int sourLen=sourStr.GetLength();
	if(ptPos==-1)return;		//没带点则跳出

	CString leftStr=sourStr.Right(sourLen-ptPos-1);		//小数点后面的数字
	CString zeroStr('0',sourLen-ptPos-1);				//构造全0的CString

	if(leftStr.Compare(zeroStr)==0)						//小数点后全为0则截断
	{
		sourStr=sourStr.Left(ptPos);
	}
}
int main()
{
	CString my;
	
	my.Format("101.222");
	delPoint(my);
	cout<<"flag:"<<my<<endl;

	my.Format("101.000");
	delPoint(my);
	cout<<"flag:"<<my<<endl;


	my.Format("101.20");
	delPoint(my);
	cout<<"flag:"<<my<<endl;
	return 0;
}

