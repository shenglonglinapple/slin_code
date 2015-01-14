#include "DataStockMinTimeMaxTime.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"
#include "QtTimeHelper.h"
#include "StockMinTimeMaxTime.h"

#include "ItemStockMinTimeMaxTime.h"
#include "ItemStockMinTimeMaxTimeHelper.h"

#include "SignalSlotManager.h"


CDataStockMinTimeMaxTime* CDataStockMinTimeMaxTime::m_pInstance = 0;
QMutex CDataStockMinTimeMaxTime::m_mutexInstance;

CDataStockMinTimeMaxTime& CDataStockMinTimeMaxTime::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataStockMinTimeMaxTime();
	}
	return (*m_pInstance);
}

void CDataStockMinTimeMaxTime::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataStockMinTimeMaxTime::CDataStockMinTimeMaxTime()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	_FreeData();

	QMutexLocker lock(&m_mutexForRoot);	
	m_pItem_Root = NULL;
	m_pItem_Root = new CItemStockMinTimeMaxTime();
	m_pItemDataHelper = NULL;
	m_pItemDataHelper = new CItemStockMinTimeMaxTimeHelper();

	CSignalSlotManager::getInstance().set_Signal_DataChange_StockMinTimeMaxTime(this);
}

CDataStockMinTimeMaxTime::~CDataStockMinTimeMaxTime()
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



void CDataStockMinTimeMaxTime::_FreeData()
{
	CStockMinTimeMaxTime* pData = NULL;
	QMap<QString, CStockMinTimeMaxTime*>::iterator  iterMap;

	{
		//check in total list
		QMutexLocker lock(&m_mutexForMapData);
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



}//



CStockMinTimeMaxTime* CDataStockMinTimeMaxTime::findNode( const QString& strSymbolUse )
{
	QMutexLocker lock(&m_mutexForMapData);
	QMap<QString, CStockMinTimeMaxTime*>::iterator  iterMap;
	CStockMinTimeMaxTime* pFindData = NULL;

	iterMap = m_MapData.find(strSymbolUse);
	if (iterMap != m_MapData.end())
	{
		pFindData = iterMap.value();
	}
	return pFindData;
}

void CDataStockMinTimeMaxTime::appendOrUpdate( CStockMinTimeMaxTime* pData )
{
	QMutexLocker lock(&m_mutexForMapData);

	QString strSymbolUse;
	QMap<QString, CStockMinTimeMaxTime*>::iterator  iterMap;
	CStockMinTimeMaxTime* pFindData = NULL;

	strSymbolUse = pData->m_strSymbolUse;

	iterMap = m_MapData.find(strSymbolUse);

	if (iterMap != m_MapData.end())
	{
		//update
		pFindData = iterMap.value();
		(*pFindData) = (*pData);
		updateNode(pData);
		delete pData;
		pData = NULL;
	}
	else
	{
		//append
		m_MapData.insert(strSymbolUse, pData);
		addNode(pData);
		pData = NULL;
	}

	CSignalSlotManager::getInstance().emit_DataChange_StockMinTimeMaxTime();
}


CItemStockMinTimeMaxTime* CDataStockMinTimeMaxTime::getRootItem()
{
	QMutexLocker lock(&m_mutexForRoot);
	return m_pItem_Root;
}


void CDataStockMinTimeMaxTime::addNode(const CStockMinTimeMaxTime* pData )
{	
	QString strLog;

	if (NULL == pData)
	{
		return;
	}
	
	{
		QMutexLocker lock(&m_mutexForRoot);
		strLog = "CDataStockMinTimeMaxTime addNode";
		m_pItemDataHelper->setValue(pData);
		m_pItemDataHelper->logInfo(__FILE__, __LINE__, strLog);
		m_pItem_Root->appendChildByData(m_pItemDataHelper);
	}

}


void CDataStockMinTimeMaxTime::updateNode(const CStockMinTimeMaxTime* pData )
{	
	QString strLog;

	if (NULL == pData)
	{
		return;
	}

	{
		QMutexLocker lock(&m_mutexForRoot);
		strLog = "CDataStockMinTimeMaxTime updateNode";
		m_pItemDataHelper->setValue(pData);
		m_pItemDataHelper->logInfo(__FILE__, __LINE__, strLog);
		m_pItem_Root->findAndResetSubNodeData(m_pItemDataHelper);
	}

}

