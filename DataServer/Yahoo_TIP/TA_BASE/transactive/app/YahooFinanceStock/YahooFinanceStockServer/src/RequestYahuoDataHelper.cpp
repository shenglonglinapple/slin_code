#include "RequestYahuoDataHelper.h"
#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>

#include "QtTimeHelper.h"
#include "FileDBOper.h"
#include "ConfigInfo.h"

#include "Log4cppLogger.h"


static const int DEF_INT_ONE_DAY_SECONDS = 60*60*24;


CRequestYahuoDataHelper::CRequestYahuoDataHelper( const QString& strSymbolUse )
{
	m_strSymbolUse = strSymbolUse;

	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	m_pFileDBOper = NULL;
	m_pFileDBOper = new CFileDBOper(m_strSymbolUse);

}



CRequestYahuoDataHelper::~CRequestYahuoDataHelper()
{
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}

	if (NULL != m_pFileDBOper)
	{
		delete m_pFileDBOper;
		m_pFileDBOper = NULL;
	}
}


void CRequestYahuoDataHelper::getStartEndTimeValue( 
	unsigned int& startYear, unsigned int& startMonth, unsigned int& startDay, 
	unsigned int& endYear, unsigned int& endMonth, unsigned int& endDay )
{
	QString strLastUpdateTime_CfgFile;
	QString strLastUpdateTime_FileDB;
	time_t nLastUpdateTime_FileDB = 0;
	time_t nTimeLastUpdateDateTime = 0;
	time_t nTimeNow = 0;

	strLastUpdateTime_FileDB = m_pFileDBOper->getLastUpdateTime();//"1970-01-01 08:00:00"

	nLastUpdateTime_FileDB = m_pQtTimeHelper->getTimeValue(strLastUpdateTime_FileDB);

	nTimeLastUpdateDateTime = nLastUpdateTime_FileDB;

	nTimeLastUpdateDateTime += DEF_INT_ONE_DAY_SECONDS;//"1970-01-02 08:00:00"
	nTimeNow = m_pQtTimeHelper->getCurrentTime();

	m_pQtTimeHelper->getTimeYearMonthDay(nTimeNow, endYear, endMonth, endDay);
	m_pQtTimeHelper->getTimeYearMonthDay(nTimeLastUpdateDateTime, startYear, startMonth, startDay);

	
}



