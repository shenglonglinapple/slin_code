#ifndef __CLASS_PROJECT_LOG_HELPER_H__
#define __CLASS_PROJECT_LOG_HELPER_H__




#include "TradeClient.h"
#include "Bar.h"

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
public:
	time_t getTimeNow_Qt();
	std::string dateTimeToStr_Qt(time_t secsSince1Jan1970UTC);
	std::string getString_BarType(enum BarType nBarType);
	enum BarType getBarTypeByString(const std::string& strBarType );
};



//QT_END_NAMESPACE

#endif // __CLASS_PROJECT_LOG_HELPER_H__









