// SMailer_test.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include "SMailer_test.h"

#include <iostream>
#include "SMailer.h"
#include "../MUtils/WinSockHelper.h"

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	MUtils::WinSockHelper wshelper;

	// make sure the file 'boot.ini' is in the root directory on driver C
	SMailer::TextPlainContent  content1("你想快速发家致富吗？你想一夜成名吗？访问 http://www.sb.com");
//	SMailer::TextHtmlContent   content2("<a href='http://morningspace.51.net'>click me</a>");
	SMailer::AppOctStrmContent content3("C:\\Program Files\\Vim\\vim74\\diff.exe");

	SMailer::MailInfo info;
	info.setSenderName("sanyue9394@126.com");
	info.setSenderAddress("sanyue9394@126.com");
	info.addReceiver("不笑猫", "939445950@qq.com");
	info.addReceiver("six_beauty", "sanyue9394@163.com");
	info.setPriority(SMailer::Priority::normal);
	info.setSubject("Smailer_test:我是要成为海贼王的男人");
	info.addMimeContent(&content1);
//	info.addMimeContent(&content2);
	info.addMimeContent(&content3);

	try
	{
		SMailer::MailSender sender("smtp.126.com", "sanyue9394@126.com", "sanyue214008");
		sender.setMail(&SMailer::MailWrapper(&info));
		sender.sendMail();
	}
	catch (SMailer::MailException& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unkown error" << std::endl;
	}
	return 0;
}
