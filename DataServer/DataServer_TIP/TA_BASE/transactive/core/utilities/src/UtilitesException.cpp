#include "core/utilities/src/UtilitesException.h"
#include "core/utilities/src/DefUtilitesException.h"


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)

static const std::string  DEF_String_ErrCode_UnKnow = "ErrCode_UnKnow";//ErrCode_UnKnow
static const std::string  DEF_String_ErrCode_ParamError = "ErrCode_ParamError";//ErrCode_ParamError



CUtilitesException::CUtilitesException(int nErrorCode, const std::string strReason) : CBaseException(nErrorCode, strReason)
{

}


CUtilitesException::CUtilitesException(CUtilitesException&  e) : CBaseException(e.getErrorCode(), e.getReason())
{

}


CUtilitesException::~CUtilitesException()
{
	// Do nothing.
}

std::string CUtilitesException::errorCodeAsString( int nErrCode )
{
	std::string strErrString;
	int nErrCodeGet = 0;
	size_t nArrSize = 0;
	
	strErrString.clear();
	nArrSize = sizeof(s_UtilitesException_ErrCodeString) / sizeof (*s_UtilitesException_ErrCodeString);

	for (size_t nIndex = 0; nIndex < nArrSize; nIndex++)
	{		
		nErrCodeGet = s_UtilitesException_ErrCodeString[nIndex].m_nErrCode;
		if (nErrCodeGet == nErrCode)
		{
			strErrString = s_UtilitesException_ErrCodeString[nIndex].m_strErrString;
			break;
		}
	}

	if (strErrString.empty())
	{
		strErrString = "UNKNOWN_ERROR";
	}
	return strErrString;
}



NS_END(TA_Base_Core)



