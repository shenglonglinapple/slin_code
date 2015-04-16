#ifndef __CLASS_CPP_EXECPTION_H__
#define __CLASS_CPP_EXECPTION_H__

#include <string>
#include <exception>
#include "core/utilities/src/UtilitiesCommonData.h"


NS_BEGIN(TA_Base_Core)


enum CCppException_ERR_CODE
{
	CPP_ERR_CODE_BEGIN = -10000,
	CPP_ERR_CODE_UNKNOWN = -9999,


	CPP_ERR_CODE_END = 100000
};

class CCppException : public std::exception
{
public:
	CCppException(int nErrorCode,	const std::string strReason) throw();
	CCppException(CCppException& e);
	virtual ~CCppException() throw();

public:
	std::string getErrorMsg();
	std::string getErrorString();
	std::string getReason();
	int getErrorCode();
	void logInfo();

public:
	std::string errorCodeAsString(int nErrCode);

private:
	int				m_nErrorCode;
	std::string     m_strReason;

	std::string		m_strErrMessage;
	std::string     m_strErrorString;

};


NS_END(TA_Base_Core)

#endif //__CLASS_DATA_ACCESS_EXECPTION_H__
