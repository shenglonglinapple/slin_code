#include "MyCppSendMailTest.h"
#include "core/CppSendEmailLib/src/AppOctStrmContent.h"
#include "core/CppSendEmailLib/src/Base64Helper.h"
#include "core/CppSendEmailLib/src/ErrorMessage.h"
#include "core/CppSendEmailLib/src/FileHelper.h"
#include "core/CppSendEmailLib/src/MailInfo.h"
#include "core/CppSendEmailLib/src/MailSender.h"
#include "core/CppSendEmailLib/src/MailWrapper.h"
#include "core/CppSendEmailLib/src/MimeContent.h"
#include "core/CppSendEmailLib/src/Priority.h"
#include "core/CppSendEmailLib/src/TextHtmlContent.h"
#include "core/CppSendEmailLib/src/TextPlainContent.h"
#include "core/CppSendEmailLib/src/WinSockHelper.h"


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
	TA_Base_Core::TextPlainContent  content1("plain text content");
	TA_Base_Core::TextHtmlContent   content2("<a href='http://morningspace.51.net'>click me</a>");
	TA_Base_Core::AppOctStrmContent content3("c:\\smtp_boot.ini");

	TA_Base_Core::MailInfo info;
	info.setSenderName("linshenglong888");
	info.setSenderAddress("linshenglong888@126.com");
	info.addReceiver("linshenglong777", "linshenglong777@126.com");
	info.addReceiver("shenglonglin1986", "shenglonglin1986@gmail.com");
	info.setPriority(TA_Base_Core::Priority::normal);
	info.setSubject("a test mail");
	info.addMimeContent(&content1);
	info.addMimeContent(&content2);
	info.addMimeContent(&content3);

	try
	{
		TA_Base_Core::MailSender sender("smtp.126.com", "linshenglong888", "051335");
		sender.setMail(&TA_Base_Core::MailWrapper(&info));
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



