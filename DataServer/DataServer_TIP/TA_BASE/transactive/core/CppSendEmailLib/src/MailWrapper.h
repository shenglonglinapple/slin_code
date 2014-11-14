#ifndef __CLASS_MAIL_WRAPPER_H___
#define __CLASS_MAIL_WRAPPER_H___

#include "core/utilities/src/UtilitiesCommonDef.h"


#include "core/CppSendEmailLib/src/MimeContent.h"


//
#include <string>
#include <vector>
#include <map>
#include <exception>
//
NS_BEGIN(TA_Base_Core)

class MailInfo;

// class MailWrapper
/////////////////////////////////////

class MailWrapper
{
public:
    MailWrapper(MailInfo* mail_info);
	virtual ~MailWrapper();
public:
    std::string getSenderAddress();
    std::string getHeader();
    std::string getEnd();

    void traverseReceiver();
    bool hasMoreReceiver();
    std::string nextReceiverAddress();

    void traverseContent();
    bool hasMoreContent();
    std::string& nextContent();
private:
	std::string _PrepareFrom();
	std::string _PrepareTo();
	std::string _PrepareDate();
	std::string _PrepareName(const std::string raw_name);
private:
    static const std::string s_strProgramMailerName;
    static const std::string s_strEmailBoundary;

    MailInfo* m_pMailInfo;
	Receivers::const_iterator m_conIterForReceivers;

    std::string m_strMailContent;
    MimeContents::const_iterator m_conIterForMimeContents;

};

NS_END(TA_Base_Core)


#endif // __CLASS_S_MAILER_H___




