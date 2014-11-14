#include "core/CppSendEmailLib/src/TextHtmlContent.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>

NS_BEGIN(TA_Base_Core)


// Member functions of class TextHtmlContent
/////////////////////////////////////

TextHtmlContent::TextHtmlContent(const std::string content, 
                                 const std::string charset)
    : MimeContent(content), m_strCharset(charset)
{
}

std::string TextHtmlContent::getType() const
{
	//"text/html; charset=gb2312"
    return "text/html; charset=" + m_strCharset;
}

std::string TextHtmlContent::getTransEncoding() const
{
    return "8bit";
}

std::string& TextHtmlContent::getContent()
{
    // you can add more codes here, such as wrapping lines 
    // or replacing '\n' with '\r\n', etc.
    return m_strContent;
}

NS_END(TA_Base_Core)

