#include "core/CppSendEmailLib/src/MailInfo.h"
#include "core/CppSendEmailLib/src/Priority.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>

//
NS_BEGIN(TA_Base_Core)



// Member functions of class MailInfo
/////////////////////////////////////

MailInfo::MailInfo() : m_strPriority(Priority::normal)
{
}

MailInfo::~MailInfo()
{

}


void MailInfo::setSenderName(const std::string name)
{
    m_strSenderName = name;
}

void MailInfo::setSenderAddress(const std::string address)
{
    m_SenderAddress = address;
}

std::string MailInfo::getSenderName() const
{
    return m_strSenderName;
}

std::string MailInfo::getSenderAddress() const
{
    return m_SenderAddress;
}

void MailInfo::addReceiver(const std::string name, const std::string address)
{
    m_MutimapReceivers.insert(Receivers::value_type(name, address));
}

void MailInfo::setReceiver(const std::string name, const std::string address)
{
    m_MutimapReceivers.clear();
    m_MutimapReceivers.insert(Receivers::value_type(name, address));
}

const Receivers& MailInfo::getReceivers() const
{
    return m_MutimapReceivers;
}

void MailInfo::setPriority(std::string priority)
{
    m_strPriority = priority;
}

std::string MailInfo::getPriority() const
{
    return m_strPriority;
}

void MailInfo::setSubject(const std::string subject)
{
    m_strSubject = subject;
}

std::string MailInfo::getSubject() const
{
    return m_strSubject;
}

void MailInfo::addMimeContent(MimeContent* content)
{
    m_VecContents.push_back(content);
}

void MailInfo::clearMimeContents()
{
    m_VecContents.clear();
}

const MimeContents& MailInfo::getMimeContents() const
{
    return m_VecContents;
}


NS_END(TA_Base_Core)

