#include <iostream>
#include <string>
#include "namespace.h"
namespace SMailer 
{
class MailSender
{
public:
	void getContent();
};
}

namespace SMailer
{
	void MailSender::getContent()
	{
		std::string msg;
		msg=MUtils::Base64Helper::encode(std::string("hahaha")) + "\r\n";
	}
}

int main()
{
	SMailer::MailSender sendMail;
	sendMail.getContent();

	return 0;
}