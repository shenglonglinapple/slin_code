#include "BaseException.h"

#include <fstream>
#include <sstream>
#include "Log4cppLogger.h"

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

CBaseException::CBaseException(
const std::string &fileName, 
unsigned lineNumber, 
const std::string &errorMessage ) throw()
{
	std::stringstream stringStream;

	stringStream<<"["<<fileName<<":"<<lineNumber<<"]"<<errorMessage;

	m_strReason = stringStream.str();
	m_nErrorCode = 0;
	m_strErrMessage.clear();
	m_strErrorString.clear();
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

void CBaseException::logInfo()
{
	MYLOG4CPP_ERROR_Base<<getErrorMsg();
}

void CBaseException::logInfo(const std::string& file, int line)
{
	//BOOST_LOG_SEV(g_logHandleFile, trivial::error)<<" ["<<file<<":"<<line<<"] "<<"Exception Info:"<<getErrorMsg();
	//MYLOG4CPP_ERROR_Base<<__FILE__<<" "<<__LINE__<<"LOG4CPP_FATAL";
	MYLOG4CPP_ERROR_Base<<" ["<<file<<":"<<line<<"] "<<"Exception Info:"<<getErrorMsg();
}





std::string CBaseException::errorCodeAsString(int nErrCode)
{
	return "UNKNOWN_ERROR";
}



