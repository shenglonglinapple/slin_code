#ifndef __CLASS_PROJECT_LOG_HELPER_H__
#define __CLASS_PROJECT_LOG_HELPER_H__

#include <string>
#include <time.h>

#include "MyBar.h"

class CMyInstrument;
class CQtTimeHelper;

class CProjectLogHelper
{
public:
	CProjectLogHelper(void);	
	~CProjectLogHelper(void);
public:
	void log_Instrument_info(
		const std::string& file, int line, 
		const std::string& strLogInfo, 
		CMyInstrument* pInstrument);

private:
	CQtTimeHelper* m_QtTimeHelper;
};



//QT_END_NAMESPACE

#endif // __CLASS_PROJECT_LOG_HELPER_H__









