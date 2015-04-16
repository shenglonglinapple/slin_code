#include "core/CppExceptionLib/src/CppException.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;


NS_BEGIN(TA_Base_Core)


CCppException::CCppException(int nErrorCode, const std::string strReason) throw()
{
	m_strReason = strReason;
	m_nErrorCode = nErrorCode;
	m_strErrMessage.clear();
	m_strErrorString.clear();
}

CCppException::~CCppException() throw()
{
// Do nothing.
}


CCppException::CCppException(CCppException&  e)
{
	m_strErrorString = e.getErrorString();
	m_strReason = e.getReason();
	m_nErrorCode = e.getErrorCode();

}


std::string CCppException::errorCodeAsString(int nErrCode)
{
	//CPP_ERR_CODE
	switch (nErrCode)
	{	
	case CPP_ERR_CODE_UNKNOWN:
		return "CPP_ERR_CODE_UNKNOWN";
	default: 
		return "UNKNOWN_ERROR";
	}
}


std::string CCppException::getErrorMsg() 
{
	//std::ostringstream ostr;
	std::stringstream stringStream;
	
	m_strErrMessage.clear();
	m_strErrorString.clear();

	m_strErrorString = errorCodeAsString(m_nErrorCode);
	stringStream<<"ErrorCode="<<m_nErrorCode
		<<" "<<"ErrorString="<<m_strErrorString
		<<" "<<"Reason="<<m_strReason;

	m_strErrMessage = stringStream.str();	

	stringStream.clear();
	stringStream.str("");

	return m_strErrMessage;
}

std::string CCppException::getErrorString() 
{
	return m_strErrorString;
}

std::string CCppException::getReason() 
{
	return m_strReason;
}

int CCppException::getErrorCode() 
{
	return m_nErrorCode;
}

void CCppException::logInfo()
{
	LOG_ERROR<<"DataAccessException Info:"<<getErrorMsg();
}





NS_END(TA_Base_Core)



