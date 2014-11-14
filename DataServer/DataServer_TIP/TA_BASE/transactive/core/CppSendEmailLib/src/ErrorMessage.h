#ifndef __CLASS_ERROR_MESSAGE_H___
#define __CLASS_ERROR_MESSAGE_H___

#include "core/utilities/src/UtilitiesCommonDef.h"


#include "core/CppSendEmailLib/src/MimeContent.h"
#include "core/CppSendEmailLib/src/MailSender.h"

//
#include <string>
#include <vector>
#include <map>
#include <exception>
//
NS_BEGIN(TA_Base_Core)


// class ErrorMessage(Helper class)
/////////////////////////////////////

class ErrorMessage
{
public:
    static ErrorMessage& getInstance();
public:
    std::string& request (MailSender::Operaion request_operation);
    std::string& response(const std::string expected_response);
private:
	ErrorMessage();
private:
    std::map<MailSender::Operaion, std::string> m_MapRequestErrMsgMap;
    std::map<std::string, std::string> m_MapResponsErrMsgMap;

};



NS_END(TA_Base_Core)


#endif // __CLASS_ERROR_MESSAGE_H___




