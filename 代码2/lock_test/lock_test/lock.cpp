#include<iostream>
#include<process.h>
#include<windows.h>
using namespace std;
char g_cArray[100]={};

// 临界区结构对象
CRITICAL_SECTION g_cs;
void workThread1(void *p)
{ 
	// 进入临界区
	EnterCriticalSection(&g_cs);
	for (int i = 0; i < 10; i++)
	{
		g_cArray[i] = 'a';
		Sleep(1);
	}
	LeaveCriticalSection(&g_cs);
}

void workThread2(void *p)
{
	// 进入临界区
	EnterCriticalSection(&g_cs);
	for(int i=0;i<10;i++)
	{
		g_cArray[9-i]='b';
		Sleep(1);
	}
	LeaveCriticalSection(&g_cs);
}


int main()
{
	InitializeCriticalSection(&g_cs);
	_beginthread(workThread1,0,NULL);
	_beginthread(workThread2,0,NULL);
	Sleep(300);
	cout<<g_cArray<<endl;
	
}
