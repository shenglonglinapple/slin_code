#include "core/CppSendEmailLib/src/MailSender.h"
#include "core/CppSendEmailLib/src/MailWrapper.h"
#include "core/CppSendEmailLib/src/Base64Helper.h"
#include "core/CppSendEmailLib/src/ErrorMessage.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <winsock2.h>

//
NS_BEGIN(TA_Base_Core)

static const int MAX_BUFFER_SIZE = 255;


// Member functions of class MailSender
/////////////////////////////////////

MailSender::MailSender(const std::string server_name, 
                       const std::string user_name, 
                       const std::string user_pwd)
    : m_strServerName(server_name), m_strUserName(user_name), 
      m_strUserPwd(user_pwd), m_pMail(0)
{
    _ConnectToSmtpServer();

    _SendSmtpHello();

	if ( !user_name.empty() )
	{
		_SendSmtpLogin();
	}
}

MailSender::~MailSender()
{
    _SendSmtpQuit();
}

void MailSender::setMail(MailWrapper* mail)
{
    m_pMail = mail;
}

void MailSender::sendMail()
{
    if (!m_pMail)
        return;

    _SendEmailHeader();
    _SendEmailContent();
    _SendEmailEnd();
}

void MailSender::_ConnectToSmtpServer()
{
    struct hostent* host = gethostbyname(m_strServerName.c_str());
    if (host == 0)
    {
        throw std::exception("Get server infomation error");
    }

    m_nSocketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = *(ULONG *)host->h_addr_list[0];
	server_addr.sin_port = ::htons(SERVICE_PORT);

    ::connect(m_nSocketHandle, (struct sockaddr *)&server_addr, sizeof(server_addr));
    _RcvResponseFromServer("220");
}

void MailSender::_SendSmtpHello()
{
    char local_host[MAX_BUFFER_SIZE];
	if (::gethostname(local_host, MAX_BUFFER_SIZE) != 0 )
    {
        throw std::exception("Get local host name error");
    }

    std::string msg;

    msg  = "HELO ";
    msg += std::string(local_host) + "\r\n";
    _SendRequestToServer(send_helo_cmd, msg);
    _RcvResponseFromServer("250");
}

void MailSender::_SendSmtpLogin()
{
    std::string msg;

    msg = "AUTH LOGIN\r\n";
    _SendRequestToServer(send_auth_cmd, msg);
    _RcvResponseFromServer("334");

    msg = Base64Helper::encode(m_strUserName) + "\r\n";
    _SendRequestToServer(send_username, msg);
    _RcvResponseFromServer("334");

    msg = Base64Helper::encode(m_strUserPwd) + "\r\n";
    _SendRequestToServer(send_password, msg);
    _RcvResponseFromServer("235");
}

void MailSender::_SendEmailHeader()
{
    std::string msg;

	//==========================================
    msg  = "MAIL FROM: ";
    msg += m_pMail->getSenderAddress() + "\r\n";
    _SendRequestToServer(send_mail_cmd, msg);
    _RcvResponseFromServer("250");

	//==========================================
    m_pMail->traverseReceiver();
    while ( m_pMail->hasMoreReceiver() )
    {
        msg  = "RCPT TO: ";
        msg += m_pMail->nextReceiverAddress() + "\r\n";
        _SendRequestToServer(send_rcpt_cmd, msg);
        _RcvResponseFromServer("250");
    }

	//==========================================
    msg  = "DATA\r\n";
    _SendRequestToServer(send_data_cmd, msg);
    _RcvResponseFromServer("354");

	//==========================================
    _SendRequestToServer(send_header, m_pMail->getHeader());
	//==========================================
}

void MailSender::_SendEmailContent()
{
    m_pMail->traverseContent();
    while ( m_pMail->hasMoreContent() )
    {
        _SendRequestToServer(send_content, m_pMail->nextContent());
    }
}

void MailSender::_SendEmailEnd()
{
    _SendRequestToServer(send_end, m_pMail->getEnd());
    _RcvResponseFromServer("250");
}

void MailSender::_SendSmtpQuit()
{
    _SendRequestToServer(send_quit_cmd, "QUIT\r\n");
    _RcvResponseFromServer("221");

    closesocket(m_nSocketHandle);
}

void MailSender::_RcvResponseFromServer(const std::string expected_response)
{
    int recv_bytes = 0;
    char response_buffer[MAX_BUFFER_SIZE];
	int nExpectedResponseSize = 3;
	std::string strRecvResponseFromServer;
	std::string response;

	nExpectedResponseSize = expected_response.size();//3

	recv_bytes = ::recv(m_nSocketHandle, response_buffer, MAX_BUFFER_SIZE, 0); 
    if (recv_bytes < 0)
    {
		std::cout<<"[ErrorMessage]:"<<ErrorMessage::getInstance().response(expected_response)<<std::endl;
        throw std::exception
		( 
            ErrorMessage::getInstance().response(expected_response).c_str()
        );
    }

    response = std::string(response_buffer, recv_bytes);
    std::cout << "[INFO]RECV(" << expected_response << "):" << response << std::endl;

	strRecvResponseFromServer = response.substr(0, nExpectedResponseSize);

    if ( strRecvResponseFromServer != expected_response )
    {
		std::cout<<"[ErrorMessage]:"<<ErrorMessage::getInstance().response(expected_response)<<std::endl;
        throw std::exception
		( 
            ErrorMessage::getInstance().response(expected_response).c_str()
        );
    }
}

void MailSender::_SendRequestToServer(Operaion operation, const std::string content)
{
    std::cout << "[INFO]SEND:" << content << std::endl;
	int nSindRes = 0;

	nSindRes = ::send(m_nSocketHandle, content.c_str(), content.length(), 0);
    if ( nSindRes < 0 )
    {
		std::cout<<"[ErrorMessage]:"<<ErrorMessage::getInstance().request(operation)<<std::endl;
        throw std::exception
		(
            ErrorMessage::getInstance().request(operation).c_str()
        );
    }
}


NS_END(TA_Base_Core)




#if 0


static const char *payload_text[] = 
{
	"Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
	"To: " TO "\r\n",
	"From: " FROM "(Example User)\r\n",
	"Cc: " CC "(Another example User)\r\n",
	"Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n",
	"Subject: SMTP multi example message\r\n",
	"\r\n", /* empty line to divide headers from body, see RFC5322 */
	"The body of the message starts here.\r\n",
	"\r\n",
	"It could be a lot of lines, could be MIME encoded, whatever.\r\n",
	"Check RFC5322.\r\n",
	NULL
};




1.SMTP 常用命令
HELO/EHLO 向服务器标识用户身份
MAIL 初始化邮件传输
mail from:
RCPT 标识单个的邮件接收人；常在MAIL 命令后面
可有多个rcpt to:
DATA 在单个或多个RCPT 命令后，表示所有的邮件接收人已标识，并初始化数据传输，以. 结束。
VRFY 用于验证指定的用户/ 邮箱是否存在；由于安全方面的原因，服务器常禁止此命令
EXPN 验证给定的邮箱列表是否存在，扩充邮箱列表，也常被禁用
HELP 查询服务器支持什么命令
NOOP 无操作，服务器应响应OK
QUIT 结束会话
RSET 重置会话，当前传输被取消






2.SMTP 返回码含义
*   邮件服务返回代码含义 
*   500   格式错误，命令不可识别（此错误也包括命令行过长）
*   501   参数格式错误 
*   502   命令不可实现 
*   503   错误的命令序列 
*   504   命令参数不可实现 
*   211    系统状态或系统帮助响应 
*   214   帮助信息 
*   220     服务就绪 
*   221     服务关闭传输信道 
*   421     服务未就绪，关闭传输信道（当必须关闭时，此应答可以作为对任何命令的响应） 
*   250   要求的邮件操作完成 
*   251   用户非本地，将转发向 
*   450   要求的邮件操作未完成，邮箱不可用（例如，邮箱忙） 
*   550   要求的邮件操作未完成，邮箱不可用（例如，邮箱未找到，或不可访问）
*   451   放弃要求的操作；处理过程中出错 
*   551   用户非本地，请尝试 
*   452   系统存储不足，要求的操作未执行
*   552   过量的存储分配，要求的操作未执行 
*   553   邮箱名不可用，要求的操作未执行（例如邮箱格式错误）
*   354   开始邮件输入，以. 结束 
*   554   操作失败 
*   535   用户验证失败 
*   235   用户验证成功 
*   334   等待用户输入验证信息 for next connection>;



3. 发送SMTP 命令及数据
const char HEADER[] = 
"HELO smtpSrv/r/n"
"MAIL FROM: sender@126.com/r/n"
"RCPT TO: recv@gmail.com/r/n"
"DATA/r/n"
"FROM: sender@126.com/r/n"
"TO: recv@gmail.com/r/n"
"SUBJECT: this is a test/r/n"
"Date: Fri, 8 Jan 2010 16:12:30/r/n"
"X-Mailer: shadowstar's mailer/r/n"
"MIME-Version: 1.0/r/n"
"Content-type: text/plain/r/n/r/n";
"./r/n"
"QUIT/r/n"

4. 附件功能
要使用SMTP 发送附件, 需要对SMTP 头信息进行说明, 改变Content-type 及为每一段正文添加BOUNDARY 名, 示例如下:
"DATA/r/n"
"FROM: sender@126.com/r/n"
"TO: recv@gmail.com/r/n"
"SUBJECT: this is a test/r/n"
"Date: Fri, 8 Jan 2010 16:12:30/r/n"
"X-Mailer: shadowstar's mailer/r/n"
"MIME-Version: 1.0/r/n"
"Content-type: multipart/mixed; boundary=/"#BOUNDARY#/"/r/n/r/n";
// 正文
"--#BOUNDARY#/r/n"
"Content-Type: text/plain; charset=gb2312/r/n"
"Content-Transfer-Encoding: quoted-printable/r/n"
//邮件正文……….
// 附件
"/r/n--#BOUNDARY#/r/n"
"Content-Type: application/octet-stream; name=att.txt/r/n"
"Content-Disposition: attachment; filename=att.txt/r/n"
"Content-Transfer-Encoding: base64/r/n"
"/r/n"
//附件正信息(base64 编码)…..



5. 实现抄送及密送

在SMTP 命令集中并没有RCPT CC 或RCPT BCC 相关命令, 那要如何来实现抄送和密送功能呢?

在网络上找到这样一句话: “ 所有的接收者协商都通过RCPT TO 命令来实现，如果是BCC ，则协商发送后在对方接收时被删掉信封接收者”, 
			 开始一直不明白这句话是什么意思? 后来通看查看foxmail 的邮件原文发现:
Date: Wed, 6 Jan 2010 12:11:48 +0800
From: "carven_li" < carven_li @smtp.com>
To: "carven" <carven@smtp.com>
Cc: "sam" <sam@smtp.com>,
	"yoyo" <yoyo@smtp.com>
BCC: "clara" <clara@tsmtp.com>
Subject: t
		 X-mailer: Foxmail 5.0 [cn]
Mime-Version: 1.0
Content-Type: multipart/mixed;
boundary="=====001_Dragon237244850520_====="
才恍然大悟, 所谓的” 协商” 应该就是指发送方在Data 中指定哪些为CC, 哪些为BCC, 
默认情况下什么都不写, 只发送第一个RCPT TO 的mail, 其他的都被过滤掉.
#endif




