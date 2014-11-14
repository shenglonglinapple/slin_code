#ifndef __CLASS_BASE64HELPERH_H__
#define __CLASS_BASE64HELPERH_H__

#include "core/utilities/src/UtilitiesCommonDef.h"

//
#include <string>
//


NS_BEGIN(TA_Base_Core)


class Base64Helper
{
public:
	Base64Helper();
	virtual ~Base64Helper();
public:

	// convert from Base64 to ANSI
	static std::string encode(const std::string in_str);

	// convert from ANSI to Base64
	static std::string decode(const std::string in_str);

private:

	// encode table
	const static std::string m_strBase64EnCodeChars;

	// decode table
	const static char m_szBase64DeCodeChars[128];
};

NS_END(TA_Base_Core)



#endif  // __CLASS_BASE64HELPERH_H__