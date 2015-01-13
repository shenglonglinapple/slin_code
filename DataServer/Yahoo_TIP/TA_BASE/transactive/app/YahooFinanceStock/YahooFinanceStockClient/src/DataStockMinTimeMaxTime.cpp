#include "DataStockMinTimeMaxTime.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"
#include "QtTimeHelper.h"
#include "StockMinTimeMaxTime.h"


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
}

CDataStockMinTimeMaxTime::~CDataStockMinTimeMaxTime()
{
	_FreeData();
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
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
		pFindData = iterMap.value();
		(*pFindData) = (*pData);

		delete pData;
		pData = NULL;
	}
	else
	{
		m_MapData.insert(strSymbolUse, pData);
		pData = NULL;
	}

}


