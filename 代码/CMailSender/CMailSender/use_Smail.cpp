#include "CSendMail.h"
#include "iostream"
using namespace std;


int main()
{
	CSendMail sMailer;
//	freopen("F://mailfile//out.txt","w+",stdout);
	
	sMailer.setServerName("smtp.126.com");														//邮箱smtp,如"smtp.126.com"
	sMailer.setUserName(userName);																//邮箱账号名，如"****@126.com"
	sMailer.setUserPwd(userPwd);																//邮箱密码
	sMailer.setSenderName("陈家喵");																//发件人名字
	sMailer.setSenderAddress("sanyue9394@126.com");												//发送邮箱地址，填你账号的地址,上面的邮箱账号名"****@126.com"

	sMailer.setReceiver("show_ball","939445950@qq.com");										//添加邮件接收者
	sMailer.addReceiver("six_beauty","sanyue9394@126.com");

	sMailer.AddFilePath("F:\\mailfile\\55e736d12f2eb938e9ea5eb1d5628535e4dd6fe9.jpg");			//添加附件
	sMailer.AddFilePath("F:/mailfile/libcurl.exp");												//添加附件

	if(sMailer.Connent())																		//每次发邮件前都需要connect
	{
		if(sMailer.SendMail("CMailSender:阿垃垃圾君","你想快速发家致富吗？你想一夜成名吗？访问 http://www.sb.com"))			//第一个字符串是邮件标题，第二个是邮件内容
				cout<<"邮件发送完成！";

	}	

	if(sMailer.Connent())																		//每次发邮件前都需要connect
	{
		std::string title,content;
		title="测试邮件part_2";
		content="柯林是个大八嘎！";
		if(sMailer.SendMail(title,content))														//第一个字符串是邮件标题，第二个是邮件内容
				cout<<"邮件发送完成！";
	
	}
	

	return 0;
}