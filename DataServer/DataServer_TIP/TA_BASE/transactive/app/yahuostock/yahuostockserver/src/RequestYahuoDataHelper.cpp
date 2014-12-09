#include "RequestYahuoDataHelper.h"
#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>

#include "ProjectCommonData.h"
#include "QtTimeHelper.h"
#include "FileDBOper.h"
#include "ConfigInfo.h"

#include "Log4cppLogger.h"




CRequestYahuoDataHelper::CRequestYahuoDataHelper()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	m_pFileDBOper = NULL;
	m_pFileDBOper = new CFileDBOper();

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
	const std::string& strSymbolUse, 
	unsigned int& startYear, unsigned int& startMonth, unsigned int& startDay, 
	unsigned int& endYear, unsigned int& endMonth, unsigned int& endDay )
{
	QString strLastUpdateTime_CfgFile;
	QString strLastUpdateTime_FileDB;
	time_t nLastUpdateTime_CfgFile = 0;
	time_t nLastUpdateTime_FileDB = 0;
	time_t nTimeLastUpdateDateTime = 0;
	time_t nTimeNow = 0;

	strLastUpdateTime_CfgFile = CConfigInfo::getInstance().getLastUpdateTime();
	strLastUpdateTime_FileDB = m_pFileDBOper->getLastUpdateTime(strSymbolUse);//"1970-01-01 08:00:00"

	nLastUpdateTime_CfgFile = m_pQtTimeHelper->strToDateTime_Qt(strLastUpdateTime_CfgFile.toStdString());
	nLastUpdateTime_FileDB = m_pQtTimeHelper->strToDateTime_Qt(strLastUpdateTime_FileDB.toStdString());

	nTimeLastUpdateDateTime = nLastUpdateTime_CfgFile;
	if (nLastUpdateTime_CfgFile < nLastUpdateTime_FileDB)
	{
		nTimeLastUpdateDateTime = nLastUpdateTime_FileDB;
		CConfigInfo::getInstance().setLastUpdateTime(strLastUpdateTime_FileDB);
	}

	nTimeLastUpdateDateTime += DEF_INT_ONE_DAY_SECONDS;
	nTimeNow = m_pQtTimeHelper->getTimeNow_Qt();

	m_pQtTimeHelper->getTimeInfo_Qt(nTimeNow, endYear, endMonth, endDay);
	m_pQtTimeHelper->getTimeInfo_Qt(nTimeLastUpdateDateTime, startYear, startMonth, startDay);

}



