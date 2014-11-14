#include "core/CppSendEmailLib/src/TextPlainContent.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>

//
NS_BEGIN(TA_Base_Core)


// Member functions of class PlainTextContent
/////////////////////////////////////

TextPlainContent::TextPlainContent(const std::string content, 
                                   const std::string charset)
    : MimeContent(content), m_strCharset(charset)
{
}

std::string TextPlainContent::getType() const
{
	//"text/plain; charset=gb2312"
    return "text/plain; charset=" + m_strCharset;
}

std::string TextPlainContent::getTransEncoding() const
{
    return "8bit";
}

std::string& TextPlainContent::getContent()
{
    // you can add more codes here, such as wrapping lines 
    // or replacing '\n' with '\r\n', etc.
    return m_strContent;
}

NS_END(TA_Base_Core)

