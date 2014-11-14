#ifndef __CLASS_MINE_CONTENT_H___
#define __CLASS_MINE_CONTENT_H___

#include "core/utilities/src/UtilitiesCommonDef.h"

//
#include <string>
#include <vector>
#include <map>

//
NS_BEGIN(TA_Base_Core)




typedef std::multimap<std::string, std::string> Receivers;



// class MimeContent(Abstract class)
/////////////////////////////////////

class MimeContent
{
public:
    MimeContent(const std::string content = "");
	virtual ~MimeContent();
public:
    virtual std::string  getType() const = 0;
    virtual std::string  getTransEncoding() const = 0;
    virtual std::string& getContent() = 0;
public:
	virtual std::string  getDisposition() const;

protected:

    std::string m_strContent;
};

typedef std::vector<MimeContent*> MimeContents;



NS_END(TA_Base_Core)


#endif // __CLASS_MINE_CONTENT_H___




