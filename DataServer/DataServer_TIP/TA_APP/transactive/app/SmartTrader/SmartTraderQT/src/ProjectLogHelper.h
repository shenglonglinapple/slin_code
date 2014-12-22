#ifndef __CLASS_PROJECT_LOG_HELPER_H__
#define __CLASS_PROJECT_LOG_HELPER_H__

#include <string>
#include <time.h>
#include <QtCore/QString>

#include "MyBar.h"

class Instrument;
class CMyInstrument;
class CQtTimeHelper;

class CProjectLogHelper
{
public:
	CProjectLogHelper(void);	
	~CProjectLogHelper(void);
public:
	void log_MyInstrument_info(
		const std::string& file, int line, 
		const std::string& strLogInfo, 
		CMyInstrument* pInstrument);


public:
	std::string getStdString(const std::string& strValue);
	std::string getStdString(const QString& strValue);

private:
	CQtTimeHelper* m_QtTimeHelper;
};



//QT_END_NAMESPACE

#endif // __CLASS_PROJECT_LOG_HELPER_H__









