#include "core/CppSendEmailLib/src/AppOctStrmContent.h"
#include "core/CppSendEmailLib/src/FileHelper.h"
#include "core/CppSendEmailLib/src/Base64Helper.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>

//
NS_BEGIN(TA_Base_Core)



// Member functions of class AppOctStrmContent
/////////////////////////////////////

AppOctStrmContent::AppOctStrmContent(const std::string file_name)
    : m_strFileName(file_name)
{
    char drive[_MAX_DRIVE];
    char direc[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath(file_name.c_str(), drive, direc, fname, ext);
    m_strName  = fname;
    m_strName += ext;
}

std::string AppOctStrmContent::getType() const
{
	//"application/octet-stream; name=testfile.txt";
    return "application/octet-stream; name=" + m_strName;
}

std::string AppOctStrmContent::getDisposition() const
{
	//"attachment; filename==testfile.txt";
    return "attachment; filename=" + m_strName;
}

std::string AppOctStrmContent::getTransEncoding() const
{
    return "base64";
}

std::string& AppOctStrmContent::getContent()
{
    // you can add more codes here, such as wrapping lines 
    // or replacing '\n' with '\r\n', etc.
    FileHelper::open(m_strFileName, m_strContent);
    m_strContent = Base64Helper::encode(m_strContent);
    return m_strContent;
}


NS_END(TA_Base_Core)

