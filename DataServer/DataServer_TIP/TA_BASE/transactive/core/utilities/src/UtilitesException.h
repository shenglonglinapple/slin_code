#ifndef __CLASS_UTILITES_EXECPTION_H__
#define __CLASS_UTILITES_EXECPTION_H__

#include <string>
#include <map>
#include "core/utilities/src/BaseException.h"


NS_BEGIN(TA_Base_Core)


class CUtilitesException : public CBaseException
{

public:
	CUtilitesException(int nErrorCode,	const std::string strReason);
	CUtilitesException(CUtilitesException& e);
	virtual ~CUtilitesException();
public:
	std::string errorCodeAsString(int nErrCode);
private:


};


NS_END(TA_Base_Core)

#endif //__CLASS_UTILITES_EXECPTION_H__
