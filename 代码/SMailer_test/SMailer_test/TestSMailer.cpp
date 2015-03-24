///////////////////////////////////////////////////////////////////
// This program is a demostration about how to use SMailer.
// Written by Morning, mailto:moyingzz@etang.com
//
// Date:2003-5
///////////////////////////////////////////////////////////////////

#include <iostream>
#include "SMailer.h"
#include "../MUtils/WinSockHelper.h"

void main()
{
    MUtils::WinSockHelper wshelper;

    // make sure the file 'boot.ini' is in the root directory on driver C
    SMailer::TextPlainContent  content1("plain text content");
    SMailer::TextHtmlContent   content2("<a href='http://morningspace.51.net'>click me</a>");
    SMailer::AppOctStrmContent content3("c:\\boot.ini");

    SMailer::MailInfo info;
    info.setSenderName("morning");
    info.setSenderAddress("moyingzz@etang.com");
    info.addReceiver("friend1", "friend1@etang.com");
    info.addReceiver("friend2", "friend2@etang.com");
    info.setPriority(SMailer::Priority::normal);
    info.setSubject("a test mail");
    info.addMimeContent(&content1);
    info.addMimeContent(&content2);
    info.addMimeContent(&content3);

    try
    {
        SMailer::MailSender sender("smtp.etang.com", "username", "password");
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
}