#include "DataUserTrade.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"
#include "QtTimeHelper.h"
#include "UserTradeInfo.h"

#include "ItemUserTrade.h"
#include "ItemUserTradeHelper.h"

#include "SignalSlotManager.h"


CDataUserTrade* CDataUserTrade::m_pInstance = 0;
QMutex CDataUserTrade::m_mutexInstance;

CDataUserTrade& CDataUserTrade::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataUserTrade();
	}
	return (*m_pInstance);
}

void CDataUserTrade::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataUserTrade::CDataUserTrade()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	_FreeData();

	QMutexLocker lock(&m_mutexForRoot);	
	m_pItem_Root = NULL;
	m_pItem_Root = new CItemUserTrade();
	m_pItemDataHelper = NULL;
	m_pItemDataHelper = new CItemUserTradeHelper();

	CSignalSlotManager::getInstance().set_Signal_DataChange_UserTrade(this);
}

CDataUserTrade::~CDataUserTrade()
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



void CDataUserTrade::_FreeData()
{
	CUserTradeInfo* pData = NULL;
	QMap<QString, CUserTradeInfo*>::iterator  iterMap;

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



CUserTradeInfo* CDataUserTrade::findNode( const QString& strTradeUUID )
{
	QMutexLocker lock(&m_mutexForMapData);
	QMap<QString, CUserTradeInfo*>::iterator  iterMap;
	CUserTradeInfo* pFindData = NULL;

	iterMap = m_MapData.find(strTradeUUID);
	if (iterMap != m_MapData.end())
	{
		pFindData = iterMap.value();
	}
	return pFindData;
}

void CDataUserTrade::appendOrUpdate( CUserTradeInfo* pData )
{
	QMutexLocker lock(&m_mutexForMapData);

	QString strTradeUUID;
	QMap<QString, CUserTradeInfo*>::iterator  iterMap;
	CUserTradeInfo* pFindData = NULL;

	strTradeUUID = pData->m_strTradeUUID;

	iterMap = m_MapData.find(strTradeUUID);

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
		m_MapData.insert(strTradeUUID, pData);
		addNode(pData);
		pData = NULL;
	}

	CSignalSlotManager::getInstance().emit_DataChange_UserTrade();
}


CItemUserTrade* CDataUserTrade::getRootItem()
{
	QMutexLocker lock(&m_mutexForRoot);
	return m_pItem_Root;
}


void CDataUserTrade::addNode(const CUserTradeInfo* pData )
{	
	QString strLog;

	if (NULL == pData)
	{
		return;
	}
	
	{
		QMutexLocker lock(&m_mutexForRoot);
		strLog = "CDataUserTrade addNode";
		m_pItemDataHelper->setValue(pData);
		m_pItemDataHelper->logInfo(__FILE__, __LINE__, strLog);
		m_pItem_Root->appendChildByData(m_pItemDataHelper);
	}

}


void CDataUserTrade::updateNode(const CUserTradeInfo* pData )
{	
	QString strLog;

	if (NULL == pData)
	{
		return;
	}

	{
		QMutexLocker lock(&m_mutexForRoot);
		strLog = "CDataUserTrade updateNode";
		m_pItemDataHelper->setValue(pData);
		m_pItemDataHelper->logInfo(__FILE__, __LINE__, strLog);
		m_pItem_Root->findAndResetSubNodeData(m_pItemDataHelper);
	}

}

