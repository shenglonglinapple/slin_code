#ifndef __CLASS_REQUEST_YAHUO_DATA_HELPER_H__
#define __CLASS_REQUEST_YAHUO_DATA_HELPER_H__

#include <string>
#include <time.h>

#include <QtCore/QString>
#include <QtCore/QStringList>

class CQtTimeHelper;
class CFileDBOper;

class CRequestYahuoDataHelper 
{
public:
	CRequestYahuoDataHelper();
	virtual ~CRequestYahuoDataHelper();
public:
	void getStartEndTimeValue( const std::string& strSymbolUse, 
		unsigned int& startYear, unsigned int& startMonth, unsigned int& startDay, 
		unsigned int& endYear, unsigned int& endMonth, unsigned int& endDay );

private:
	CQtTimeHelper* m_pQtTimeHelper;
	CFileDBOper* m_pFileDBOper;
};


#endif //__CLASS_REQUEST_YAHUO_DATA_HELPER_H__
