#include "MarketDataPathManager.h"


#include "MarketDataFileManager.h"
#include "FileSystemItem.h"
#include "FileSystemManager.h"
#include "CFDServerUtilityFun.h"
#include "WorkTime.h"
#include "ConfigInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;



////////QT_BEGIN_NAMESPACE 


static const int DEF_VALUE_INT_LoadMaxFilesSize = 1;

//////////////////////////////////////////////////////////////////////////

CMarketDataPathManager::CMarketDataPathManager(void)
{
	m_pFileSystemManager = new CFileSystemManager();
	m_nLoadMaxFilesSize = DEF_VALUE_INT_LoadMaxFilesSize;
	m_nLoadFilesToMemoryMaxIndex = 0;
	m_nNextStartTime = 0;
	m_pUtilityFun = NULL;
	m_pUtilityFun = new CCFDServerUtilityFun();
	_SetInstrumentBarInfoRequest();
}

CMarketDataPathManager::~CMarketDataPathManager(void)
{
	BOOST_LOG_FUNCTION();

	

	if (NULL != m_pFileSystemManager)
	{
		delete m_pFileSystemManager;
		m_pFileSystemManager = NULL;
	}

	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}

}


int CMarketDataPathManager::analieAllFilesOneByOne()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	std::string strLogInfo;
	CFileSystemManager::MapTimeFileSystemItemT mapTimeFileSystemItemTmp;

	while (1)
	{
		//reset m_nStartTime
		m_InstrumentBarInfoRequest.setValueByCfg();
		LOG_INFO<<"analies Directory ="<<m_InstrumentBarInfoRequest.m_strHistoryDataDirectory;
		m_pFileSystemManager->getAllFileSystemItemInPath(m_InstrumentBarInfoRequest.m_strHistoryDataDirectory, mapTimeFileSystemItemTmp);
		m_pFileSystemManager->removeOldFile(m_InstrumentBarInfoRequest.m_nStartTime, mapTimeFileSystemItemTmp);

		if (mapTimeFileSystemItemTmp.empty())
		{
			break;
		}

		_AnalieAllFilesTypeMarketDataOneByOne(mapTimeFileSystemItemTmp);

		m_pFileSystemManager->freeData(mapTimeFileSystemItemTmp);
		mapTimeFileSystemItemTmp.clear();
	}

	return nFunRes;
}


time_t CMarketDataPathManager::_GetNextStartTime(CFileSystemItem* pLastFile)
{
	//get last file time
	time_t nLastFileTime = 0;

	if (NULL == pLastFile)
	{
		return nLastFileTime;
	}

	nLastFileTime = pLastFile->getFileNameTime();
	m_nNextStartTime = nLastFileTime + 1;
	m_strNextStartTime = m_pUtilityFun->dataTimeToStr(m_nNextStartTime);

	LOG_INFO<<"_GetNextStartTime"
		<<" "<<"strLastFileFullPath="<<pLastFile->getFileFullPath()
		<<" "<<"nLastFileTime="<<nLastFileTime
		<<" "<<"m_nNextStartTime="<<m_nNextStartTime
		<<" "<<"m_strNextStartTime="<<m_strNextStartTime;

	LOG_INFO<<"-----Report--- CMarketDataPathManager"
		<<" "<<"m_strNextStartTime="<<m_strNextStartTime;

	return m_nNextStartTime;
}

int CMarketDataPathManager::_AnalieAllFilesTypeMarketDataOneByOne(CFileSystemManager::MapTimeFileSystemItemT& mapTimeFileSystemItemTmp)
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	CFileSystemManager::MapTimeFileSystemItemIterT iterMap;
	CFileSystemItem* pFileSystemItem = NULL;
	CMarketDataFileManager*  pMarketDataFileManager = NULL;
	std::string strLogLevel;
	std::string strLogFun;
	std::string strLogMsgStr0;
	std::ostringstream sreaamTmp;
	CAWorkTime* pTime = new CWorkTimeNoLock();


	if (NULL == pMarketDataFileManager)
	{
		pMarketDataFileManager = new CMarketDataFileManager(CMarketDataFileManager::AnalierType_Dispatch_MarkketData);
	}


	iterMap = mapTimeFileSystemItemTmp.begin();
	if (iterMap != mapTimeFileSystemItemTmp.end())
	{
		pFileSystemItem = iterMap->second;

		m_InstrumentBarInfoRequest.m_strCurrentAnalierFileName = pFileSystemItem->getFileFullPath();
	
		pTime->workBegin();
		pMarketDataFileManager->setInstrumentBarInfoRequest(m_InstrumentBarInfoRequest);
		nFunRes = pMarketDataFileManager->analierFile();
		pTime->workEnd();

		strLogLevel = "INFO";
		strLogFun = "_AnalieAllFilesTypeMarketDataOneByOne";
		sreaamTmp.str("");
		sreaamTmp<<" "<<"AnalierFileName="<<m_InstrumentBarInfoRequest.m_strCurrentAnalierFileName
			<<" "<<"using="<<pTime->getWorkTime()
			<<" "<<"ms";
		strLogMsgStr0 = sreaamTmp.str();		
		CConfigInfo::getInstance().logToDB(strLogLevel, strLogFun, strLogMsgStr0);


		_GetNextStartTime(pFileSystemItem);//m_nNextStartTime m_strNextStartTime
		CConfigInfo::getInstance().setStartTime(m_strNextStartTime);
		CConfigInfo::getInstance().logInfo();
	}

	//free
	if (NULL != pMarketDataFileManager)
	{
		delete pMarketDataFileManager;
		pMarketDataFileManager = NULL;
	}

	if (NULL != pTime)
	{
		delete pTime;
		pTime = NULL;
	}

	return nFunRes;
}

int CMarketDataPathManager::_SetInstrumentBarInfoRequest()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	

	m_nAnalierType = CMarketDataFileManager::AnalierType_Dispatch_MarkketData;

	m_InstrumentBarInfoRequest.setValueByCfg();
	_ProcessRequest();

	return nFunRes;
}



int CMarketDataPathManager::_ProcessRequest()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;

	LOG_INFO<<"check HisData Directory ="<<m_InstrumentBarInfoRequest.m_strHistoryDataDirectory;
	if (m_pFileSystemManager->checkDirectory(m_InstrumentBarInfoRequest.m_strHistoryDataDirectory))
	{
		//hisData Directory exists
		if (m_InstrumentBarInfoRequest.m_nDBType == enumSqliteDb)
		{
			LOG_INFO<<"check and create savedataBAR Directory ="<<m_InstrumentBarInfoRequest.m_strSaveDataDirectoryBAR;
			m_pFileSystemManager->createDirectory(m_InstrumentBarInfoRequest.m_strSaveDataDirectoryBAR);

			LOG_INFO<<"check and create savedataTIK Directory ="<<m_InstrumentBarInfoRequest.m_strSaveDataDirectoryTIK;
			m_pFileSystemManager->createDirectory(m_InstrumentBarInfoRequest.m_strSaveDataDirectoryTIK);

		}
	}
	else
	{
		nFunRes = -1;
		LOG_ERROR<<"HisData Directory="<<m_InstrumentBarInfoRequest.m_strHistoryDataDirectory<<" not exists!!";
	}

	m_nLoadMaxFilesSize = m_InstrumentBarInfoRequest.m_nLoadMaxFilesSize;
	if (m_nLoadMaxFilesSize <= 0)
	{
		m_nLoadMaxFilesSize = DEF_VALUE_INT_LoadMaxFilesSize;
	}
	LOG_INFO<<"CMarketDataPathManager m_nLoadMaxFilesSize="<<m_nLoadMaxFilesSize;

	return nFunRes;
}



//////QT_END_NAMESPACE 



