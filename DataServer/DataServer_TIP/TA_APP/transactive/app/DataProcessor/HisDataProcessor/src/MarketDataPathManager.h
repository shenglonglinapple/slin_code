/*
manager MarketData history Data All Files in one Path. sort by time
*/
#ifndef __CLASS_MARKET_DATA_PATH_MANAGER__HH__
#define __CLASS_MARKET_DATA_PATH_MANAGER__HH__

#include "CFDServerCommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "InstrumentBarInfoRequest.h"
#include "MarketDataFileManager.h"
#include "FileSystemManager.h"

QT_BEGIN_NAMESPACE 

class CMarketDataFileManager;
class CCFDServerUtilityFun;

class CMarketDataPathManager
{
public:
	CMarketDataPathManager(void);
	~CMarketDataPathManager(void);
public:
	int setInstrumentBarInfoRequest(const CInstrumentBarInfoRequest& instrumentBarInfoRequest);

	int analieAllFiles();
	time_t getNextStartTime();
private:
	int _AnalieAllFilesTypeMarketData(CFileSystemManager::MapTimeFileSystemItemT& mapTimeFileSystemItemTmp);
	int _ProcessRequest();
	int _LogInfo(const std::string& strLogInfo, CFileSystemManager::MapTimeFileSystemItemT& mapTimeFileSystemItemTmp);
	int _GetNextStartTime(CFileSystemManager::MapTimeFileSystemItemT& mapTimeFileSystemItemTmp);
private:
	CFileSystemManager*    m_pFileSystemManager;
	CInstrumentBarInfoRequest m_InstrumentBarInfoRequest;
	CMarketDataFileManager::enAnalierType  m_nAnalierType;

private:
	unsigned int       m_nLoadFilesToMemoryMaxSize;
	unsigned int       m_nLoadFilesToMemoryMaxIndex;
private:
	time_t  m_nNextStartTime;
	std::string m_strNextStartTime;
	CCFDServerUtilityFun* m_pUtilityFun;

};

QT_END_NAMESPACE 


#endif //__CLASS_MARKET_DATA_PATH_MANAGER__HH__


