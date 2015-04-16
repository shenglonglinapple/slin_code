#include "core/utilities/src/BaseException.h"


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)


CBaseException::CBaseException(int nErrorCode, const std::string strReason) throw()
{
	m_strReason = strReason;
	m_nErrorCode = nErrorCode;
	m_strErrMessage.clear();
	m_strErrorString.clear();
}

CBaseException::~CBaseException() throw()
{
	m_strErrMessage.clear();
	m_strErrorString.clear();
	// Do nothing
}


CBaseException::CBaseException(CBaseException&  e)
{
	m_strErrorString = e.getErrorString();
	m_strReason = e.getReason();
	m_nErrorCode = e.getErrorCode();

}



std::string CBaseException::getErrorMsg() 
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

std::string CBaseException::getErrorString() 
{
	return m_strErrorString;
}

std::string CBaseException::getReason() 
{
	return m_strReason;
}

int CBaseException::getErrorCode() 
{
	return m_nErrorCode;
}



void CBaseException::logInfo(const std::string& file, int line)
{
	BOOST_LOG_SEV(g_logHandleFile, trivial::error)<<" ["<<file<<":"<<line<<"] "<<"Exception Info:"<<getErrorMsg();
}





std::string CBaseException::errorCodeAsString(int nErrCode)
{
	return "UNKNOWN_ERROR";
}


NS_END(TA_Base_Core)



