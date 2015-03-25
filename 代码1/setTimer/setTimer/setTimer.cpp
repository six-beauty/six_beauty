// setTimer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "setTimer.h"

void CALLBACK TimerProc(HWND hwnd,UINT umsg,UINT idEvent,DWORD dwTime)
{
	
	
			
			MessageBox(NULL,_T("123f"),NULL,true);
			printf("asdf\n");
		
KillTimer(hwnd,idEvent);

}
int main()
{
//	MessageBox(NULL,_T("asdf"),NULL,true);
	SetTimer(NULL,0,300,&TimerProc);
	
}