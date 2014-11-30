#include "MarketDataPathManager.h"


#include "MarketDataFileManager.h"
#include "FileSystemItem.h"
#include "FileSystemManager.h"
#include "CFDServerUtilityFun.h"

#include "BoostLogger.h"
USING_BOOST_LOG;



QT_BEGIN_NAMESPACE 


static const int DEF_VALUE_INT_LoadFilesToMemoryMaxSize = 30;

//////////////////////////////////////////////////////////////////////////

CMarketDataPathManager::CMarketDataPathManager(void)
{
	m_pFileSystemManager = new CFileSystemManager();
	m_nLoadFilesToMemoryMaxSize = DEF_VALUE_INT_LoadFilesToMemoryMaxSize;
	m_nLoadFilesToMemoryMaxIndex = 0;
	m_nNextStartTime = 0;
	m_pUtilityFun = NULL;
	m_pUtilityFun = new CCFDServerUtilityFun();
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


int CMarketDataPathManager::analieAllFiles()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	std::string strLogInfo;
	CFileSystemManager::MapTimeFileSystemItemT mapTimeFileSystemItemTmp;

	LOG_INFO<<"analies Directory ="<<m_InstrumentBarInfoRequest.m_strHistoryDataDirectory;

	m_pFileSystemManager->getAllFileSystemItemInPath(m_InstrumentBarInfoRequest.m_strHistoryDataDirectory, mapTimeFileSystemItemTmp);

	m_pFileSystemManager->removeOldFile(m_InstrumentBarInfoRequest.m_nStartTime, mapTimeFileSystemItemTmp);
	
	strLogInfo = "after remove old files, program will Process these file:";
	_LogInfo(strLogInfo, mapTimeFileSystemItemTmp);

	_AnalieAllFilesTypeMarketData(mapTimeFileSystemItemTmp);


	_GetNextStartTime(mapTimeFileSystemItemTmp);


	strLogInfo = "-----Report--- CMarketDataPathManager";
	_LogInfo(strLogInfo, mapTimeFileSystemItemTmp);


	m_pFileSystemManager->freeData(mapTimeFileSystemItemTmp);
	mapTimeFileSystemItemTmp.clear();


	return nFunRes;
}


int CMarketDataPathManager::_GetNextStartTime(CFileSystemManager::MapTimeFileSystemItemT& mapTimeFileSystemItemTmp)
{
	//get last file time

	CFileSystemManager::MapTimeFileSystemItemIterT iterMap;
	CFileSystemItem* pLastFile = NULL;
	time_t nLastFileTime = 0;


	iterMap = mapTimeFileSystemItemTmp.begin();
	while (iterMap != mapTimeFileSystemItemTmp.end())
	{
		pLastFile = iterMap->second;

		iterMap++;
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

int CMarketDataPathManager::_AnalieAllFilesTypeMarketData(CFileSystemManager::MapTimeFileSystemItemT& mapTimeFileSystemItemTmp)
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	CFileSystemManager::MapTimeFileSystemItemIterT iterMap;
	CFileSystemItem* pFileSystemItem = NULL;
	CMarketDataFileManager*  pMarketDataFileManager = NULL;



	iterMap = mapTimeFileSystemItemTmp.begin();
	while (iterMap != mapTimeFileSystemItemTmp.end())
	{
		pFileSystemItem = iterMap->second;

		m_InstrumentBarInfoRequest.m_strCurrentAnalierFileName = pFileSystemItem->getFileFullPath();

		m_nLoadFilesToMemoryMaxIndex++;
		if (m_nLoadFilesToMemoryMaxIndex > m_nLoadFilesToMemoryMaxSize)
		{
			if (NULL != pMarketDataFileManager)
			{
				LOG_INFO<<m_nLoadFilesToMemoryMaxIndex<<">"<<m_nLoadFilesToMemoryMaxSize<<"  reset";

				LOG_INFO<<"-----Report--- CMarketDataPathManager"
					<<" "<<m_nLoadFilesToMemoryMaxIndex<<">"<<m_nLoadFilesToMemoryMaxSize<<"  reset";


				delete pMarketDataFileManager;
				pMarketDataFileManager = NULL;
			}
			m_nLoadFilesToMemoryMaxIndex = 0;
		}

		if (NULL == pMarketDataFileManager)
		{
			pMarketDataFileManager = new CMarketDataFileManager(CMarketDataFileManager::AnalierType_Dispatch_MarkketData);
		}


		pMarketDataFileManager->setInstrumentBarInfoRequest(m_InstrumentBarInfoRequest);
		nFunRes = pMarketDataFileManager->analierFile();

		iterMap++;
	}

	//free
	if (NULL != pMarketDataFileManager)
	{
		delete pMarketDataFileManager;
		pMarketDataFileManager = NULL;
	}


	return nFunRes;
}

int CMarketDataPathManager::setInstrumentBarInfoRequest(const CInstrumentBarInfoRequest& instrumentBarInfoRequest )
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	
	m_InstrumentBarInfoRequest = instrumentBarInfoRequest;

	m_nAnalierType = CMarketDataFileManager::AnalierType_Dispatch_MarkketData;

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

	return nFunRes;
}



int CMarketDataPathManager::_LogInfo(const std::string& strLogInfo,
	CFileSystemManager::MapTimeFileSystemItemT& mapTimeFileSystemItemTmp)
{
	int nFunRes = 0;
	CFileSystemManager::MapTimeFileSystemItemIterT iterMap;
	CFileSystemItem* pFileSystemItem = NULL;

	LOG_DEBUG<<"strLogInfo="<<strLogInfo
		<<" "<<"mapTimeFileSystemItemTmp.size()="<<mapTimeFileSystemItemTmp.size();

	iterMap = mapTimeFileSystemItemTmp.begin();
	while (iterMap != mapTimeFileSystemItemTmp.end())
	{
		pFileSystemItem = iterMap->second;

		LOG_DEBUG<<"FileName="<<pFileSystemItem->getFileFullPath();

		iterMap++;
	}

	return nFunRes;
}

time_t CMarketDataPathManager::getNextStartTime()
{
	return m_nNextStartTime;
}


QT_END_NAMESPACE 



