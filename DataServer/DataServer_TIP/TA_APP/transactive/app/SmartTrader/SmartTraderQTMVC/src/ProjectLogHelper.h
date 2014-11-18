#ifndef __CLASS_PROJECT_LOG_HELPER_H__
#define __CLASS_PROJECT_LOG_HELPER_H__




#include "TradeClient.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CProjectLogHelper
{
public:
	CProjectLogHelper(void);	
	~CProjectLogHelper(void);
public:
	void log_Instrument_info(const std::string& file, int line, 
		const std::string& strLogInfo, const Instrument &instrument);
	std::string dateTimeToStr_Qt(time_t nTimeValue);

};



//QT_END_NAMESPACE

#endif // __CLASS_PROJECT_LOG_HELPER_H__









