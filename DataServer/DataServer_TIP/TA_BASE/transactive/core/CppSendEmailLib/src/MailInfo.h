#ifndef __CLASS_MAIL_INFO_H___
#define __CLASS_MAIL_INFO_H___

#include "core/utilities/src/UtilitiesCommonDef.h"


#include "core/CppSendEmailLib/src/MimeContent.h"

//
#include <string>
#include <vector>
#include <map>
#include <exception>
//
NS_BEGIN(TA_Base_Core)



// class MailInfo
/////////////////////////////////////


class MailInfo
{

public:
    MailInfo();
	virtual ~MailInfo();
public:
    void setSenderName(const std::string name);
    void setSenderAddress(const std::string address);
    std::string getSenderName() const;
    std::string getSenderAddress() const;

    void addReceiver(const std::string name, const std::string address);
    void setReceiver(const std::string name, const std::string address);
    const Receivers& getReceivers() const;

    void setPriority(std::string priority);
    std::string getPriority() const;

    void setSubject(const std::string subject);
    std::string getSubject() const;

    void addMimeContent(MimeContent* content);
    void clearMimeContents();
    const MimeContents& getMimeContents() const;

private:

    std::string  m_strSenderName;
    std::string  m_SenderAddress;
    Receivers    m_MutimapReceivers;
    std::string  m_strPriority;
    std::string  m_strSubject;
    MimeContents m_VecContents;
};



NS_END(TA_Base_Core)


#endif // __CLASS_S_MAILER_H___




