#include "core/CppSendEmailLib/src/MailWrapper.h"
#include "core/CppSendEmailLib/src/MailInfo.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Base64Helper.h"
#include "FileHelper.h"
//
NS_BEGIN(TA_Base_Core)

static const int MAX_BUFFER_SIZE = 255;

const std::string MailWrapper::s_strProgramMailerName = "core.CppSendEmaillib";
const std::string MailWrapper::s_strEmailBoundary    = "#BOUNDARY#";


// Member functions of class MailWrapper
/////////////////////////////////////

MailWrapper::MailWrapper(MailInfo* mail_info) : m_pMailInfo(mail_info)
{
}

MailWrapper::~MailWrapper()
{

}


std::string MailWrapper::getSenderAddress()
{
	std::string strSenderAddress;
    std::string address;

	strSenderAddress = m_pMailInfo->getSenderAddress();

    address  = "<";
    address += strSenderAddress;
    address += ">";

    return address;
}

std::string MailWrapper::getHeader()
{
    std::string header;

	//==========================================
    header  = "From: ";
    header += _PrepareFrom() + "\r\n";

	//==========================================
    header += "To: ";
    header += _PrepareTo() + "\r\n";

	//==========================================
    header += "Date: ";
    header += _PrepareDate() + "\r\n";

	//==========================================
    header += "Subject: ";
    header += m_pMailInfo->getSubject() + "\r\n";

	//==========================================
    header += "X-Mailer: ";
    header += s_strProgramMailerName + "\r\n";

	//==========================================
    header += "X-Priority: ";
    header += m_pMailInfo->getPriority() + "\r\n";

	//==========================================
    header += "MIME-Version: 1.0\r\n";
    header += "Content-type: multipart/mixed; boundary=\"";
    header += s_strEmailBoundary + "\"\r\n";
	
	//==========================================
    header += "\r\n";

    return header;
}

void MailWrapper::traverseReceiver()
{
    m_conIterForReceivers = m_pMailInfo->getReceivers().begin();
}

bool MailWrapper::hasMoreReceiver()
{
	bool bHasMore = false;
	bHasMore = (m_conIterForReceivers != m_pMailInfo->getReceivers().end());
    return bHasMore;
}

std::string MailWrapper::nextReceiverAddress()
{
	std::string strAddressSrc;
    std::string address;
	strAddressSrc = (m_conIterForReceivers++)->second;

    address  = "<";
    address += strAddressSrc;
    address += ">";

    return address;
}

void MailWrapper::traverseContent()
{
    m_conIterForMimeContents = m_pMailInfo->getMimeContents().begin();
}

bool MailWrapper::hasMoreContent()
{
	bool bHasMore = false;
	bHasMore = (m_conIterForMimeContents != m_pMailInfo->getMimeContents().end());
	return bHasMore;
}

std::string& MailWrapper::nextContent()
{
    m_strMailContent  = "--" + s_strEmailBoundary + "\r\n";

    m_strMailContent += "Content-Type: ";
    m_strMailContent += (*m_conIterForMimeContents)->getType() + "\r\n";

    std::string disposition = (*m_conIterForMimeContents)->getDisposition();
    if ( !disposition.empty() )
    {
        m_strMailContent += "Content-Disposition: ";
        m_strMailContent += disposition + "\r\n";
    }

    m_strMailContent += "Content-Transfer-Encoding: ";
    m_strMailContent += (*m_conIterForMimeContents)->getTransEncoding() + "\r\n\r\n";

    m_strMailContent += (*m_conIterForMimeContents)->getContent() + "\r\n\r\n";

    m_conIterForMimeContents++;

    return m_strMailContent;
}

std::string MailWrapper::getEnd()
{
    std::string end;

    end += "\r\n--" + s_strEmailBoundary + "--\r\n";

    end += ".\r\n";

    return end;
}

std::string MailWrapper::_PrepareFrom()
{
    std::string from_string;

    from_string = _PrepareName(m_pMailInfo->getSenderName());
    from_string += getSenderAddress();

    return from_string;
}

std::string MailWrapper::_PrepareTo()
{
    std::string to_string;

    traverseReceiver();
    while ( hasMoreReceiver() )
    {
        to_string += _PrepareName(m_conIterForReceivers->first);
        to_string += nextReceiverAddress() + ", ";
    }

    return to_string.substr(0, to_string.length()-2);
}

std::string MailWrapper::_PrepareDate()
{
    char date_string[MAX_BUFFER_SIZE];

    time_t seconds;
    time(&seconds);
    strftime(date_string, MAX_BUFFER_SIZE, 
             "%a, %d %b %y %H:%M:%S +0800", 
             localtime(&seconds));          // +0800 maybe hard code

    return date_string;
}

std::string MailWrapper::_PrepareName(const std::string raw_name)
{
    std::string decorated_name;

    if (!raw_name.empty())
    {
        decorated_name  = "\"";
        decorated_name += raw_name;
        decorated_name += "\" ";
    }

    return decorated_name;
}


NS_END(TA_Base_Core)

