#ifndef __CLASS_APP_OCT_STM_CONTENT_H___
#define __CLASS_APP_OCT_STM_CONTENT_H___

#include "core/utilities/src/UtilitiesCommonDef.h"


#include "core/CppSendEmailLib/src/MimeContent.h"

//
#include <string>
#include <vector>

NS_BEGIN(TA_Base_Core)



// class AppOctStrmContent
/////////////////////////////////////

class AppOctStrmContent : public MimeContent
{
public:

    AppOctStrmContent(const std::string file_name);

    virtual std::string  getType() const;
    virtual std::string  getDisposition() const;
    virtual std::string  getTransEncoding() const;
    virtual std::string& getContent();

private:

    std::string m_strFileName;
    std::string m_strName;
};


NS_END(TA_Base_Core)


#endif // __CLASS_APP_OCT_STM_CONTENT_H___




