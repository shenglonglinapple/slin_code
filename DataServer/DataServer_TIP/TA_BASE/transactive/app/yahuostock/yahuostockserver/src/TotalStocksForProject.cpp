#include "TotalStocksForProject.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


#include "BaseException.h"
#include "StockData.h"
#include "TotalStocksData.h"
#include "TotalStocksDataYahuoNodata.h"

#include "Log4cppLogger.h"

CTotalStocksForProject::CTotalStocksForProject()
{
	m_nWorkState = WorkState_Begin;

	_FreeData_MapStockDataItemT_UnKnown();

}

CTotalStocksForProject::~CTotalStocksForProject()
{
	_FreeData_MapStockDataItemT_UnKnown();
	_FreeData_MapStockDataItemT_Bad();
	_FreeData_MapStockDataItemT_Good();

}

void CTotalStocksForProject::do_init_data()
{
	m_nWorkState = WorkState_Begin;
	_LoadData_MapStockDataItemT_Good();

	m_nWorkState = WorkState_End;
}

void CTotalStocksForProject::_LoadData_MapStockDataItemT_UnKnown()
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
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_UnKnown);
		for (nIndex = 0; nIndex < nArrSize; nIndex++)
		{
			pCStockData = new CStockData();

			strSymbol = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
			//strName = s_SSSZ_Stocks[nIndex].m_psz_Name;
			strNamePinYin = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
			strSymbolExtern = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
			strSymbolUse = strSymbol + strSymbolExtern;

			
			pCStockData->m_strSymbol = strSymbol;
			pCStockData->m_strNamePinYin = strNamePinYin;
			pCStockData->m_strSymbolExtern = strSymbolExtern;
			pCStockData->m_nIndex = nIndex;
			pCStockData->m_strSymbolUse = strSymbolUse;
			pCStockData->m_strName = "";

			m_MapStockDataItemT_UnKnown.insert(
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


void CTotalStocksForProject::_FreeData_MapStockDataItemT_UnKnown()
{
	{
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_UnKnown);
		_FreeData_MapStockDataItemT(m_MapStockDataItemT_UnKnown);
	}

}


void CTotalStocksForProject::_FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData)
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

void CTotalStocksForProject::_LoadData_MapStockDataItemT_Bad()
{
	int nArrSize = 0;
	CStockData* pCStockData = NULL;
	int nIndex = 0;
	std::string strSymbol;
	std::string strName;
	std::string strNamePinYin;
	std::string strSymbolExtern;
	std::string strSymbolUse;


	nArrSize = sizeof(s_SSSZ_Stocks_NoDATA) / sizeof (*s_SSSZ_Stocks_NoDATA);
	MYLOG4CPP_INFO<<"s_SSSZ_Stocks_NoDATA ArrSize="<<nArrSize;

	{
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_Bad);
		for (nIndex = 0; nIndex < nArrSize; nIndex++)
		{
			pCStockData = new CStockData();

			strSymbol = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
			//strName = s_SSSZ_Stocks[nIndex].m_psz_Name;
			strNamePinYin = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
			strSymbolExtern = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
			strSymbolUse = strSymbol + strSymbolExtern;


			pCStockData->m_strSymbol = strSymbol;
			pCStockData->m_strNamePinYin = strNamePinYin;
			pCStockData->m_strSymbolExtern = strSymbolExtern;
			pCStockData->m_nIndex = nIndex;
			pCStockData->m_strSymbolUse = strSymbolUse;
			pCStockData->m_strName = "";

			m_MapStockDataItemT_Bad.insert(
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

void CTotalStocksForProject::_FreeData_MapStockDataItemT_Bad()
{
	{
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_Bad);
		_FreeData_MapStockDataItemT(m_MapStockDataItemT_Bad);
	}
}

void CTotalStocksForProject::_LoadData_MapStockDataItemT_Good()
{
	_FreeData_MapStockDataItemT_Good();

	_LoadData_MapStockDataItemT_UnKnown();
	_LoadData_MapStockDataItemT_Bad();



	MapStockDataItemIterT iterMap_UnKnown;
	MapStockDataItemIterT iterMap_Bad_Find;
	CStockData* pData_Unknown_Ref = NULL;
	CStockData* pData_Good = NULL;
	int nProcessIndex = 0;

	{
		boost::mutex::scoped_lock lock_UnKnown(m_mutexMapStockDataItemT_UnKnown);
		boost::mutex::scoped_lock lock_Bad(m_mutexMapStockDataItemT_Bad);
		boost::mutex::scoped_lock lock_Good(m_mutexMapStockDataItemT_Good);


		MYLOG4CPP_INFO<<"m_MapStockDataItemT_UnKnown.size="<<m_MapStockDataItemT_UnKnown.size();//3255
		MYLOG4CPP_INFO<<"m_MapStockDataItemT_Bad.size="<<m_MapStockDataItemT_Bad.size();//923
		MYLOG4CPP_INFO<<"m_MapStockDataItemT_Good.size="<<m_MapStockDataItemT_Good.size();//0




		iterMap_UnKnown = m_MapStockDataItemT_UnKnown.begin();
		while (iterMap_UnKnown != m_MapStockDataItemT_UnKnown.end())
		{
			pData_Unknown_Ref = (iterMap_UnKnown->second);

			iterMap_Bad_Find = m_MapStockDataItemT_Bad.end();
			iterMap_Bad_Find = m_MapStockDataItemT_Bad.find(pData_Unknown_Ref->m_strSymbolUse);
			if (iterMap_Bad_Find != m_MapStockDataItemT_Bad.end())
			{
				//find ok
				int neeror = 0;
			}
			else
			{
				pData_Good = new CStockData();
				*pData_Good = *pData_Unknown_Ref;
				m_MapStockDataItemT_Good.insert(
					MapStockDataItemValueTypeT(pData_Good->m_strSymbolUse, pData_Good));
				pData_Good = NULL;
			}

			printf("nProcessIndex=%d\n", nProcessIndex);
			nProcessIndex++;
			iterMap_UnKnown++;
		}//while
	}


	_FreeData_MapStockDataItemT_UnKnown();
	_FreeData_MapStockDataItemT_Bad();
	pData_Unknown_Ref = NULL;
	pData_Good = NULL;

	MYLOG4CPP_INFO<<"m_MapStockDataItemT_UnKnown.size="<<m_MapStockDataItemT_UnKnown.size();//3255
	MYLOG4CPP_INFO<<"m_MapStockDataItemT_Bad.size="<<m_MapStockDataItemT_Bad.size();//923
	MYLOG4CPP_INFO<<"m_MapStockDataItemT_Good.size="<<m_MapStockDataItemT_Good.size();//2332


}

void CTotalStocksForProject::_FreeData_MapStockDataItemT_Good()
{
	{
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_Good);
		_FreeData_MapStockDataItemT(m_MapStockDataItemT_Good);
	}
}




