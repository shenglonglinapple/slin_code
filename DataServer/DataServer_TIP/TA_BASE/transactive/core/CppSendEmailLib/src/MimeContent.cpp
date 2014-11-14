#include "core/CppSendEmailLib/src/MimeContent.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>
//
NS_BEGIN(TA_Base_Core)




MimeContent::MimeContent(const std::string content) : m_strContent(content)
{
}

MimeContent::~MimeContent()
{

}

std::string MimeContent::getDisposition() const
{
    return "";
}

NS_END(TA_Base_Core)

