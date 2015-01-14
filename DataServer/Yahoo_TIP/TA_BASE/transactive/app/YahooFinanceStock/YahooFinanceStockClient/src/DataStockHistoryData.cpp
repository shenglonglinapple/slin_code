#include "DataStockHistoryData.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"
#include "QtTimeHelper.h"
#include "HistoryData.h"

#include "ItemStockHistoryData.h"
#include "ItemStockHistoryDataHelper.h"

#include "SignalSlotManager.h"


CDataStockHistoryData* CDataStockHistoryData::m_pInstance = 0;
QMutex CDataStockHistoryData::m_mutexInstance;

CDataStockHistoryData& CDataStockHistoryData::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataStockHistoryData();
	}
	return (*m_pInstance);
}

void CDataStockHistoryData::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataStockHistoryData::CDataStockHistoryData()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();

	{
		QMutexLocker lock(&m_mutexForRoot);	
		m_pItem_Root = NULL;
		m_pItem_Root = new CItemStockHistoryData();
		m_pItemDataHelper = NULL;
		m_pItemDataHelper = new CItemStockHistoryDataHelper();
	}

	CSignalSlotManager::getInstance().set_Signal_DataChange_StockHistoryData(this);
	_FreeData();

}

CDataStockHistoryData::~CDataStockHistoryData()
{
	_FreeData();


	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}

	QMutexLocker lock(&m_mutexForRoot);	

	if (NULL != m_pItem_Root)
	{
		delete m_pItem_Root;
		m_pItem_Root = NULL;
	}
	if (NULL != m_pItemDataHelper)
	{
		delete m_pItemDataHelper;
		m_pItemDataHelper = NULL;
	}
}



void CDataStockHistoryData::_FreeData()
{
	CHistoryData* pData = NULL;
	QMap<qint32, CHistoryData*>::iterator  iterMap;

	{
		//check in total list
		QMutexLocker lock(&m_mutexForMapData);
		m_strSymbolUse.clear();
		iterMap = m_MapData.begin();
		while (iterMap != m_MapData.end())
		{
			pData = iterMap.value();

			delete pData;
			pData = NULL;

			iterMap++;
		}//while
		m_MapData.clear();
	}

	{
		QMutexLocker lock(&m_mutexForRoot);	
		if (NULL != m_pItem_Root)
		{
			delete m_pItem_Root;
			m_pItem_Root = NULL;
		}
		m_pItem_Root = new CItemStockHistoryData();
	}


}//


CItemStockHistoryData* CDataStockHistoryData::getRootItem()
{
	QMutexLocker lock(&m_mutexForRoot);
	return m_pItem_Root;
}



void CDataStockHistoryData::setData( const QString& strSymbolUse, const QList<CHistoryData*>& lstData )
{
	QList<CHistoryData*>::const_iterator iterLst = lstData.begin();
	QMap<qint32, CHistoryData*>::iterator  iterMap;
	qint32 nKeyTmp = 0;
	CHistoryData* pData = NULL;
	const CHistoryData* pDataGet = NULL;

	_FreeData();
	m_strSymbolUse = strSymbolUse;

	{
		QMutexLocker lockMap(&m_mutexForMapData);
		QMutexLocker lockRoot(&m_mutexForRoot);
		iterLst = lstData.begin();
		while (iterLst != lstData.end())
		{
			pDataGet = (*iterLst);
			iterMap = m_MapData.begin();
			nKeyTmp = m_pQtTimeHelper->getTimeValue(pDataGet->m_strDate);
			iterMap = m_MapData.find(nKeyTmp);
			if (iterMap != m_MapData.end())
			{
				//find same one
			}
			else
			{
				pData = new CHistoryData();
				(*pData) = (*pDataGet);
				m_MapData.insert(nKeyTmp, pData);
				pData = NULL;
			}

			iterLst++;
		}//while

	}//lock

	_ReSetRoot();
}



void CDataStockHistoryData::_ReSetRoot()
{
	CHistoryData* pData = NULL;
	QMap<qint32, CHistoryData*>::iterator  iterMap;

	{
		QMutexLocker lock(&m_mutexForRoot);	
		if (NULL != m_pItem_Root)
		{
			delete m_pItem_Root;
			m_pItem_Root = NULL;
		}
		m_pItem_Root = new CItemStockHistoryData();
	}

	{
		QMutexLocker lock(&m_mutexForMapData);
		iterMap = m_MapData.begin();
		while (iterMap != m_MapData.end())
		{
			pData = iterMap.value();

			QString strLog;
			strLog = "CDataStockHistoryData addNode";
			m_pItemDataHelper->setValue(m_strSymbolUse, pData);
			m_pItemDataHelper->logInfo(__FILE__, __LINE__, strLog);
			m_pItem_Root->appendChildByData(m_pItemDataHelper);

			iterMap++;
		}//while
		m_MapData.clear();
	}


	CSignalSlotManager::getInstance().emit_DataChange_StockHistoryData();

}//

