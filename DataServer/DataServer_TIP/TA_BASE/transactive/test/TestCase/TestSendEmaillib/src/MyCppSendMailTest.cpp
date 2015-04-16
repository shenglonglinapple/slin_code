#include "MyCppSendMailTest.h"
#include "core/CppSendEmailLib/src/CppSendEmailLibHH.h"




#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>




#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

#include <list>
#include <string>
#include <iostream>


NS_BEGIN(TA_Base_Test) 


//////////////////////////////////////////////////////////////////////////
CMyCppSendMailTest::CMyCppSendMailTest(void)
{	

	
}

CMyCppSendMailTest::~CMyCppSendMailTest(void)
{



}

void CMyCppSendMailTest::test_SendOneEmail()
{
	TA_Base_Core::WinSockHelper wshelper;

	// make sure the file 'boot.ini' is in the root directory on driver C
	TA_Base_Core::TextPlainContent  content_email_text("plain text content≤‚ ‘” º˛ƒ⁄»›");
	TA_Base_Core::TextHtmlContent   content_html("<a href='http://morningspace.51.net'>click me</a>");
	TA_Base_Core::AppOctStrmContent content_file("c:\\smtp_boot.ini");

	TA_Base_Core::MailInfo oneMailInfo;
	oneMailInfo.setSenderName("linshenglong888");
	oneMailInfo.setSenderAddress("linshenglong888@126.com");
	oneMailInfo.addReceiver("linshenglong777", "linshenglong777@126.com");
	oneMailInfo.addReceiver("shenglonglin1986", "shenglonglin1986@gmail.com");
	oneMailInfo.setPriority(TA_Base_Core::Priority::normal);
	oneMailInfo.setSubject("a test mail ≤‚ ‘” º˛");
	oneMailInfo.addMimeContent(&content_email_text);
	oneMailInfo.addMimeContent(&content_html);
	oneMailInfo.addMimeContent(&content_file);

	try
	{
		TA_Base_Core::MailSender sender("smtp.126.com", "linshenglong888", "051335");
		sender.setMail(&TA_Base_Core::MailWrapper(&oneMailInfo));
		sender.sendMail();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unkown error" << std::endl;
	}
}

NS_END(TA_Base_Test) 



