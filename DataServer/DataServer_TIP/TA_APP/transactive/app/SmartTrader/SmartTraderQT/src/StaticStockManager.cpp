#include "StaticStockManager.h"

#include "StockData.h"
#include "TotalStocksData.h"

#include "Log4cppLogger.h"



CStaticStockManager* CStaticStockManager::m_pInstance = 0;
QMutex CStaticStockManager::m_mutexInstance;

CStaticStockManager& CStaticStockManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CStaticStockManager();
	}
	return (*m_pInstance);
}

void CStaticStockManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
}

CStaticStockManager::CStaticStockManager()
{
	_FreeData_MapStockDataItemT_Total();
	_LoadData_MapStockDataItemT_Total();
}

CStaticStockManager::~CStaticStockManager()
{	
	_FreeData_MapStockDataItemT_Total();	
}



void CStaticStockManager::_LoadData_MapStockDataItemT_Total()
{
	int nArrSize = 0;
	CStockData* pCStockData = NULL;
	int nIndex = 0;
	std::string strSymbol;
	std::string strName;
	std::string strNamePinYin;
	std::string strSymbolExtern;
	std::string strSymbolUse;
	std::string strStockID;
	int nStockID = 0;

	nArrSize = sizeof(s_SSSZ_Stocks) / sizeof (*s_SSSZ_Stocks);
	MYLOG4CPP_INFO<<"s_SSSZ_Stocks ArrSize="<<nArrSize;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

		for (nIndex = 0; nIndex < nArrSize; nIndex++)
		{
			pCStockData = new CStockData();

			strSymbol = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
			//strName = s_SSSZ_Stocks[nIndex].m_psz_Name;
			strNamePinYin = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
			strSymbolExtern = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
			strSymbolUse = strSymbol + strSymbolExtern;
			strStockID = strSymbolUse.substr(0, strSymbolUse.find("."));
			nStockID = atoi(strStockID.c_str());
			if (strSymbolExtern.empty())
			{
				strSymbolExtern = strSymbolUse.substr(strSymbolUse.find(".") + 1);
			}

			pCStockData->m_nIndex = nIndex;
			pCStockData->m_nStockID = nStockID;
			pCStockData->m_strSymbol = strSymbol;
			pCStockData->m_strNamePinYin = strNamePinYin;
			pCStockData->m_strSymbolExtern = strSymbolExtern;
			pCStockData->m_strSymbolUse = strSymbolUse;
			pCStockData->m_strName = strNamePinYin;

			m_MapStockDataItemT_Total.insert(
				MapStockDataItemValueTypeT(strSymbolUse, pCStockData));

			pCStockData = NULL;
		}//for
	}

	if (NULL != pCStockData)
	{
		delete pCStockData;
		pCStockData = NULL;
	}
}

void CStaticStockManager::_FreeData_MapStockDataItemT_Total()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
	_FreeData_MapStockDataItemT(m_MapStockDataItemT_Total);
}


void CStaticStockManager::_FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData)
{
	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = mapStockData.begin();
	while (iterMap != mapStockData.end())
	{
		pData = (iterMap->second);

		delete pData;
		pData = NULL;

		iterMap++;
	}
	mapStockData.clear();
	return;
}

void CStaticStockManager::doWork_getStockID(std::list<int>& LstStockID)
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	LstStockID.clear();

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap->second);
		
		LstStockID.push_back(pData->m_nStockID);

		pData = NULL;
		iterMap++;
	}
}

void CStaticStockManager::doWork_getStockSymbolUse(std::list<std::string>& LstStockSymbolUse)
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap->second);

		LstStockSymbolUse.push_back(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
	}
}

void CStaticStockManager::doWork_getStockData( std::list<CStockData*>& LstStockData )
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	CStockData* pStockDataTmp = NULL;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap->second);

		pStockDataTmp = new CStockData();
		*pStockDataTmp =*pData;

		LstStockData.push_back(pStockDataTmp);

		pData = NULL;
		pStockDataTmp = NULL;
		iterMap++;
	}
}

const CStockData* CStaticStockManager::find_StockData_BySymbolUse( const std::string& strSymbolUse )
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap->second);
		
		if (pData->m_strSymbolUse == strSymbolUse)
		{
			break;
		}

		pData = NULL;
		iterMap++;
	}
	
	return pData;
}

const CStockData* CStaticStockManager::find_StockData_BySymbolUse( int nStockID )
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap->second);

		if (pData->m_nStockID == nStockID)
		{
			break;
		}

		pData = NULL;
		iterMap++;
	}

	return pData;
}



