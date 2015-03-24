#include<afx.h>
#include<iostream>
#include<time.h>
#include<sstream>

using namespace std;

//__time64_t,头文件time.h
void get___time64_t()
{
	__time64_t curTime;
	_time64(&curTime);
	tm tmCurTime;
	_localtime64_s(&tmCurTime,&curTime);

	stringstream ss;
	ss<<tmCurTime.tm_year+1900<<"-";
	ss<<tmCurTime.tm_mon+1<<"-";
	ss<<tmCurTime.tm_mday<<" ";
	ss<<tmCurTime.tm_hour<<":";
	ss<<tmCurTime.tm_min<<":";
	ss<<tmCurTime.tm_sec;

	cout<<ss.str()<<endl;
}

//time_t，头文件time.h
void get_time_t()
{
	time_t curTime;
	time(&curTime);
	tm tmCurTime;
	localtime_s(&tmCurTime,&curTime);

	stringstream ss;
	ss<<tmCurTime.tm_year+1900<<"-";
	ss<<tmCurTime.tm_mon+1<<"-";
	ss<<tmCurTime.tm_mday<<" ";
	ss<<tmCurTime.tm_hour<<":";
	ss<<tmCurTime.tm_min<<":";
	ss<<tmCurTime.tm_sec;

	cout<<ss.str()<<endl;
}

//Ctime 头文件afx.h,MFC动态
void get_CTime()
{
	CTime curTime=CTime::GetCurrentTime();
	cout<<curTime.Format("%Y-%m-%d %H:%M:%S %B，%A")<<endl;
	cout<<curTime.Format("%x %X")<<endl;
}

int main()
{
	get___time64_t();
//	get_time_t();
//	get_CTime();
	return 0;
}