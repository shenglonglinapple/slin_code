#include "core/CppSendEmailLib/src/ErrorMessage.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>

//
NS_BEGIN(TA_Base_Core)

// Member functions of class ErrorMessage
/////////////////////////////////////

ErrorMessage& ErrorMessage::getInstance()
{
    static ErrorMessage m_instance;
    return m_instance;
}

ErrorMessage::ErrorMessage()
{
    m_MapRequestErrMsgMap[MailSender::send_helo_cmd] = "Send HELO cmd error";
    m_MapRequestErrMsgMap[MailSender::send_auth_cmd] = "Send AUTH cmd error";
    m_MapRequestErrMsgMap[MailSender::send_username] = "Send user name error";
    m_MapRequestErrMsgMap[MailSender::send_password] = "Send user password error";
    m_MapRequestErrMsgMap[MailSender::send_mail_cmd] = "Send MAIL FROM cmd error";
    m_MapRequestErrMsgMap[MailSender::send_rcpt_cmd] = "Send RCPT TO cmd error";
    m_MapRequestErrMsgMap[MailSender::send_data_cmd] = "Send DATA cmd error";
    m_MapRequestErrMsgMap[MailSender::send_header  ] = "Send mail header error";
    m_MapRequestErrMsgMap[MailSender::send_content ] = "Send mail content error";
    m_MapRequestErrMsgMap[MailSender::send_end     ] = "Send mail end error";
    m_MapRequestErrMsgMap[MailSender::send_quit_cmd] = "Send QUIT cmd error";

    m_MapResponsErrMsgMap["220"] = "Server connect error";
    m_MapResponsErrMsgMap["250"] = "General server error";
    m_MapResponsErrMsgMap["334"] = "Server authentication error";
    m_MapResponsErrMsgMap["235"] = "Password error";
    m_MapResponsErrMsgMap["354"] = "Server not ready for data";
    m_MapResponsErrMsgMap["221"] = "Server didn't terminate session";
}

std::string& ErrorMessage::request(MailSender::Operaion request_operation)
{
    return m_MapRequestErrMsgMap[request_operation];
}

std::string& ErrorMessage::response(const std::string expected_response)
{
    return m_MapResponsErrMsgMap[expected_response];
}

NS_END(TA_Base_Core)

