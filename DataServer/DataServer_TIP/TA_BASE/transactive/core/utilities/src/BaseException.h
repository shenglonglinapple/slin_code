#ifndef __CLASS_BASE_EXECPTION_H__
#define __CLASS_BASE_EXECPTION_H__

#include <string>
#include <exception>
#include "core/utilities/src/UtilitiesCommonData.h"


NS_BEGIN(TA_Base_Core)


class CBaseException : public std::exception
{
public:
	CBaseException(int nErrorCode,	const std::string strReason) throw();
	CBaseException(CBaseException& e);
	virtual ~CBaseException() throw();

public:
	std::string getErrorMsg();
	std::string getErrorString();
	std::string getReason();
	int getErrorCode();
	void logInfo(const std::string& file, int line);

public:
	virtual std::string errorCodeAsString(int nErrCode);
private:
	int				m_nErrorCode;
	std::string     m_strReason;

	std::string		m_strErrMessage;
	std::string     m_strErrorString;

};


NS_END(TA_Base_Core)

#endif //__CLASS_BASE_EXECPTION_H__
