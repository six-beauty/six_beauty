// cricital.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
#include <iostream>
using namespace std;
DWORD WINAPI threadFun1(
	LPVOID lpParameter   // 线程1的线程函数声明
	);
DWORD WINAPI threadFun2(
	LPVOID lpParameter   // 线程2的线程函数声明
	);

int my1[10]={0};
int my2[10]={0};
CRITICAL_SECTION g_cs;//临界区的参数
///////////////////////////////////////////////////////////////////////
//名称：main//
//功能：用两个线程模拟火车站的售票系统，并用临界区实现线程的同步//
//////////////////////////////////////////////////////////////////////
void main()
{
	InitializeCriticalSection(&g_cs);//初始化临界区
	HANDLE hThread1;
	hThread1=CreateThread(NULL,0,threadFun1,NULL,0,NULL);
	HANDLE hThread2;
	hThread2=CreateThread(NULL,0,threadFun2,NULL,0,NULL);
	CloseHandle(hThread1);//创建线程1
	CloseHandle(hThread2);//创建现成

	Sleep(4000);//主程序睡眠4秒，使线程函数得以运行
	DeleteCriticalSection(&g_cs);//程序执行完毕，销毁临界区
}
DWORD WINAPI threadFun1(LPVOID lpParameter)   // 线程1
{
	while(1)
	{
	//	EnterCriticalSection(&g_cs);
		Sleep(1000);
		printf("+++++++++\n");
	//	LeaveCriticalSection(&g_cs);//释放临界区资源
	}
	return 0;
}

DWORD WINAPI threadFun2(LPVOID lpParameter)   // 线程2
{
	while(1)
	{
	//	EnterCriticalSection(&g_cs);
		Sleep(400);
		printf("---------\n");
	//	LeaveCriticalSection(&g_cs);//释放临界区资源
	}
	return 0;
}