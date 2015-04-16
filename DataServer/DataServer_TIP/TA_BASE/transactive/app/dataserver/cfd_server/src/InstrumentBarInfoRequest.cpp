#include "InstrumentBarInfoRequest.h"

#include "CFDServerUtilityFun.h"
#include <boost/algorithm/string.hpp>

#include "ConfigInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

////////QT_BEGIN_NAMESPACE

static const int DEF_VALUE_INT_LoadMaxFilesSize = 1;

CInstrumentBarInfoRequest::CInstrumentBarInfoRequest(void)
{
	BOOST_LOG_FUNCTION();

	m_strHistoryDataDirectory.clear();
	m_strSaveDataDirectoryBAR.clear();
	m_strSaveDataDirectoryTIK.clear();
	m_strCurrentAnalierFileName.clear();
	m_nDBType = enumSqliteDb;
	m_nStartTime = 0;
	m_nLoadMaxFilesSize = DEF_VALUE_INT_LoadMaxFilesSize;

	m_lstBarTime.clear();
	_AddBarTimeNormal();
}

CInstrumentBarInfoRequest::~CInstrumentBarInfoRequest(void)
{
	BOOST_LOG_FUNCTION();
	m_lstBarTime.clear();
}


CInstrumentBarInfoRequest& CInstrumentBarInfoRequest::operator=(const CInstrumentBarInfoRequest& instrumentBarInfoRequest )
{
	BOOST_LOG_FUNCTION();

	m_strHistoryDataDirectory = instrumentBarInfoRequest.m_strHistoryDataDirectory;
	m_strSaveDataDirectoryBAR = instrumentBarInfoRequest.m_strSaveDataDirectoryBAR;
	m_strSaveDataDirectoryTIK = instrumentBarInfoRequest.m_strSaveDataDirectoryTIK;

	m_nStartTime = instrumentBarInfoRequest.m_nStartTime;
	m_nDBType = instrumentBarInfoRequest.m_nDBType;

	m_nLoadMaxFilesSize = instrumentBarInfoRequest.m_nLoadMaxFilesSize;

	m_nAutoRun = instrumentBarInfoRequest.m_nAutoRun;
	m_strAutoRunTime24Clock = instrumentBarInfoRequest.m_nAutoRun;
	m_strCurrentAnalierFileName = instrumentBarInfoRequest.m_strCurrentAnalierFileName;

	m_lstBarTime.clear();
	_AddBarTimeNormal();
	return *this;
}

void CInstrumentBarInfoRequest::logInfo(const std::string& strLogInfo)
{
	BOOST_LOG_FUNCTION();

	LOG_INFO<<"strLogInfo="<<strLogInfo;
	LOG_INFO<<"m_strHistoryDataDirectory="<<m_strHistoryDataDirectory;
	LOG_INFO<<"m_strSaveDataDirectoryBAR="<<m_strSaveDataDirectoryBAR;
	LOG_INFO<<"m_strSaveDataDirectoryTIK="<<m_strSaveDataDirectoryTIK;

	LOG_INFO<<"m_nStartTime="<<m_nStartTime;
	LOG_INFO<<"m_nDBType="<<m_nDBType;
	LOG_INFO<<"m_nLoadMaxFilesSize="<<m_nLoadMaxFilesSize;

	LOG_INFO<<"m_nAutoRun="<<m_nAutoRun;
	LOG_INFO<<"m_strAutoRunTimeHour24Clock="<<m_strAutoRunTime24Clock;
	LOG_INFO<<"m_strCurrentAnalierFileName="<<m_strCurrentAnalierFileName;

	LOG_INFO<<"Calculator TIME_BASE_S_5S="<<TIME_BASE_S_5S;
	LOG_INFO<<"Calculator TIME_BASE_S_1MIN="<<TIME_BASE_S_1MIN;
	LOG_INFO<<"Calculator TIME_BASE_S_5MIN="<<TIME_BASE_S_5MIN;
	LOG_INFO<<"Calculator TIME_BASE_S_15MIN="<<TIME_BASE_S_15MIN;
	LOG_INFO<<"Calculator TIME_BASE_S_30MIN="<<TIME_BASE_S_30MIN;
	LOG_INFO<<"Calculator TIME_BASE_S_1HOUR="<<TIME_BASE_S_1HOUR;
	LOG_INFO<<"Calculator TIME_BASE_S_1DAY="<<TIME_BASE_S_1DAY;

	//
// 	LOG_INFO<<"Calculator TIME_BASE_S_1MON="<<TIME_BASE_S_1MON;
// 	LOG_INFO<<"Calculator TIME_BASE_S_1YEAR="<<TIME_BASE_S_1YEAR;

	return;
}

void CInstrumentBarInfoRequest::_AddBarTimeNormal()
{
	BOOST_LOG_FUNCTION();

	m_lstBarTime.push_back(TIME_BASE_S_5S);//seconds
	m_lstBarTime.push_back(TIME_BASE_S_1MIN);//seconds
	m_lstBarTime.push_back(TIME_BASE_S_5MIN);//seconds
	m_lstBarTime.push_back(TIME_BASE_S_15MIN);//seconds
	m_lstBarTime.push_back(TIME_BASE_S_30MIN);//seconds
	m_lstBarTime.push_back(TIME_BASE_S_1HOUR);//seconds
	m_lstBarTime.push_back(TIME_BASE_S_1DAY);//seconds

	//fix memory 2GB problem just calc to 1day
	//m_lstBarTime.push_back(TIME_BASE_S_1MON);//seconds
	//m_lstBarTime.push_back(TIME_BASE_S_1YEAR);//seconds

	return;
}





void CInstrumentBarInfoRequest::getLstBarTime( std::list<int>& lstBarTime )
{
	std::list<int>::iterator iterList;
	iterList = m_lstBarTime.begin();
	while (iterList != m_lstBarTime.end())
	{
		int nSeconds = *iterList;
		lstBarTime.push_back(nSeconds);
		iterList++;
	}
}

void CInstrumentBarInfoRequest::setValueByCfg()
{
	m_strHistoryDataDirectory = CConfigInfo::getInstance().getHistoryDataDirectory();
	m_strSaveDataDirectoryBAR = CConfigInfo::getInstance().getSaveDataDirectoryBAR();
	m_strSaveDataDirectoryTIK = CConfigInfo::getInstance().getSaveDataDirectoryTIK();
	m_nDBType =  CConfigInfo::getInstance().getDbType();
	m_nStartTime = CConfigInfo::getInstance().getStartTime();
	m_nAutoRun = CConfigInfo::getInstance().getAutoRunType();
	m_strAutoRunTime24Clock = CConfigInfo::getInstance().getAutoRunTime();
	m_nLoadMaxFilesSize = CConfigInfo::getInstance().getLoadMaxFilesSize();
}

//////QT_END_NAMESPACE
















