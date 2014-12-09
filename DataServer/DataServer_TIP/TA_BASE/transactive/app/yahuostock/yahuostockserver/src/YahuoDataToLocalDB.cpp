#include "YahuoDataToLocalDB.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>

#include "BaseException.h"
#include "StockData.h"
#include "TotalStocksData.h"

#include "ProcessYahuoDataToLocalDB.h"
#include "ProcessFileDataToDB.h"

#include "Log4cppLogger.h"



CYahuoDataToLocalDB* CYahuoDataToLocalDB::m_pInstance = 0;
QMutex CYahuoDataToLocalDB::m_mutexInstance;

CYahuoDataToLocalDB& CYahuoDataToLocalDB::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CYahuoDataToLocalDB();
	}
	return (*m_pInstance);
}

void CYahuoDataToLocalDB::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CYahuoDataToLocalDB::CYahuoDataToLocalDB()
{
	m_pProcessYahuoDataToLocalDB = NULL;
	m_pProcessYahuoDataToLocalDB = new CProcessYahuoDataToLocalDB();

	_FreeData_MapStockDataItemT_Total();
	_LoadData_MapStockDataItemT_Total();


}

CYahuoDataToLocalDB::~CYahuoDataToLocalDB()
{	

	_FreeData_MapStockDataItemT_Total();

	if (NULL != m_pProcessYahuoDataToLocalDB)
	{
		delete m_pProcessYahuoDataToLocalDB;
		m_pProcessYahuoDataToLocalDB = NULL;
	}

	
}



void CYahuoDataToLocalDB::_LoadData_MapStockDataItemT_Total()
{
	int nArrSize = 0;
	CStockData* pCStockData = NULL;
	int nIndex = 0;
	std::string strSymbol;
	std::string strName;
	std::string strNamePinYin;
	std::string strSymbolExtern;
	std::string strSymbolUse;


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

			pCStockData->m_nIndex = nIndex;
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


void CYahuoDataToLocalDB::_FreeData_MapStockDataItemT_Total()
{
	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		_FreeData_MapStockDataItemT(m_MapStockDataItemT_Total);
	}

}


void CYahuoDataToLocalDB::_FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData)
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

void CYahuoDataToLocalDB::doWork_YahuoDataToLocalDB()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	int nFunCheckRes = 0;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		qSleep(10);

		pData = (iterMap->second);
		m_pProcessYahuoDataToLocalDB->processStock(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
	}

}


void CYahuoDataToLocalDB::doWork_Local_FileDB_To_SQLiteDB()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
	CProcessFileDataToDB myProcessFileDataToDB;
	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	int nFunCheckRes = 0;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		qSleep(10);

		pData = (iterMap->second);
		myProcessFileDataToDB.proceeFileData(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
	}
}

void CYahuoDataToLocalDB::qSleep(int nMilliseconds)
{
#ifdef Q_OS_WIN
	Sleep(uint(nMilliseconds));
#else
	struct timespec ts = { nMilliseconds / 1000, (nMilliseconds % 1000) * 1000 * 1000 };
	nanosleep(&ts, NULL);
#endif

}
void CYahuoDataToLocalDB::qWait(int nMilliseconds)
{
	QElapsedTimer timer;
	timer.start();
	do 
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, nMilliseconds);
		qSleep(10);
	} while (timer.elapsed() < nMilliseconds);

}




