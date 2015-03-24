// sendMail.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sendMail.h"
#include "CSendMail.h"

using namespace std;

void sa_sendmail()
{
	//sMailInfo sm;
	//sm.m_pcUserName = "xujingping@lkgame.com";//"";
	//sm.m_pcUserPassWord ="xjp000";// "";
	//sm.m_pcSenderName = "布蓝闻";
	//sm.m_pcSender = "xujingping@lkgame.com";//发送者的邮箱地址  
	//sm.m_pcReceiver = "sanyue9394@163.com";//接收者的邮箱地址  
	//sm.m_pcTitle = "测试垃圾邮件";//邮箱标题  
	//sm.m_pcBody = "你想快速发家致富吗？你想一夜成名吗？访问 http://www.sb.com";//邮件文本正文  
	//sm.m_pcIPAddr = "" ;//服务器的IP可以留空 
	//sm.m_pcIPName ="smtp.lkgame.com" ;//服务器的名称（IP与名称二选一，优先取名称）  
	sMailInfo sm;
	lstrcpyn(sm.m_pcUserName , "sanyue9394@126.com",128);//"",128);
	lstrcpyn(sm.m_pcUserPassWord ,"sanyue214008",128);// "",128);
	lstrcpyn(sm.m_pcSenderName , "six_beauty科技",128);
	lstrcpyn(sm.m_pcSender , "sanyue9394@126.com",128);//发送者的邮箱地址  
	lstrcpyn(sm.m_pcReceiver , "sanyue9394@163.com",128);//接收者的邮箱地址  
	lstrcpyn(sm.m_pcTitle , "From:sendMail,发财机会来了！！！",128);//邮箱标题  
	lstrcpyn(sm.m_pcBody , "你想快速发家致富吗？你想一夜成名吗？访问 http://www.sb.com",1024);//邮件文本正文  
	lstrcpyn(sm.m_pcIPAddr , "" ,128);//服务器的IP可以留空 
	lstrcpyn(sm.m_pcIPName ,"smtp.126.com" ,128);//服务器的名称（IP与名称二选一，优先取名称）

	CSendMail csm;
	//csm.AddFilePath("F:\\mailfile\\55e736d12f2eb938e9ea5eb1d5628535e4dd6fe9.jpg");
	csm.AddFilePath("F:\\mailfile\\libcurl.exp");
	//while(TRUE)
	{
		csm.SendMail(sm);
		//Sleep(1000 * 20);
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	freopen("F://mailfile//sendmail_out.txt","w+",stdout);
	sa_sendmail();
	return 0;
}
