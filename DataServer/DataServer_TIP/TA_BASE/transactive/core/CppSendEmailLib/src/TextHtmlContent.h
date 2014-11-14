#ifndef __CLASS_TEXT_HTML_CONTENT_H___
#define __CLASS_TEXT_HTML_CONTENT_H___

#include "core/utilities/src/UtilitiesCommonDef.h"

#include "core/CppSendEmailLib/src/MimeContent.h"

//
#include <string>
#include <vector>

NS_BEGIN(TA_Base_Core)


class TextHtmlContent : public MimeContent
{
public:

    TextHtmlContent(const std::string content, 
                    const std::string charset = "gb2312");

    virtual std::string  getType() const;
    virtual std::string  getTransEncoding() const;
    virtual std::string& getContent();

private:

    std::string m_strCharset;
};


NS_END(TA_Base_Core)


#endif // __CLASS_TEXT_HTML_CONTENT_H___




