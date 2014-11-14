#ifndef __CLASS_MAIL_SENDER_H___
#define __CLASS_MAIL_SENDER_H___

#include "core/utilities/src/UtilitiesCommonDef.h"


#include "core/CppSendEmailLib/src/MimeContent.h"


//
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <winsock2.h>
//
NS_BEGIN(TA_Base_Core)

class MailWrapper;

// class MailSender
/////////////////////////////////////

class MailSender
{

private:
	enum 
	{
		SERVICE_PORT = 25 /*smtp.126.com:25  smtp default port*/
	};

	enum Operaion
	{
		send_helo_cmd, 
		send_auth_cmd, 
		send_username, 
		send_password, 
		send_mail_cmd, 
		send_rcpt_cmd, 
		send_data_cmd, 
		send_header, 
		send_content, 
		send_end, 
		send_quit_cmd, 
	};

public:

    MailSender(const std::string server_name, 
               const std::string user_name = "", 
               const std::string user_pwd = "");

    ~MailSender();

    void setMail(MailWrapper* mail);

    void sendMail();

private:
	void _ConnectToSmtpServer();
	void _SendSmtpHello();
	void _SendSmtpLogin();

	void _SendEmailHeader();
	void _SendEmailContent();
	void _SendEmailEnd();

	void _SendSmtpQuit();

	void _SendRequestToServer(Operaion operation, const std::string content);
	void _RcvResponseFromServer(const std::string expected_response);

private:
    std::string m_strServerName;
    std::string m_strUserName;
    std::string m_strUserPwd;
    SOCKET m_nSocketHandle;

    MailWrapper* m_pMail;
private:
    friend class ErrorMessage;
};


NS_END(TA_Base_Core)


#endif // __CLASS_MAIL_SENDER_H___




