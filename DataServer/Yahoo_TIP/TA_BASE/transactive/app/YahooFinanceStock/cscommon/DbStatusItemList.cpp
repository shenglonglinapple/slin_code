#include "DbStatusItemList.h"

#include "Log4cppLogger.h"


CDbStatusItemList::CDbStatusItemList()
{
	_FreeData();
}

CDbStatusItemList::~CDbStatusItemList()
{
	_FreeData();
}

void CDbStatusItemList::logInfo( const QString& file, qint32 line )
{

}



void CDbStatusItemList::_FreeData()
{
	QMutexLocker lock(&m_mutexMapPriorityDbStatusItem);	

	QMap<CDbStatusItem::EDBPriority, CDbStatusItem*>::Iterator  iterMap;
	CDbStatusItem* pItem = NULL;

	iterMap = m_MapPriorityDbStatusItem.begin();
	while (iterMap != m_MapPriorityDbStatusItem.end())
	{
		pItem = (iterMap.value());

		delete pItem;
		pItem = NULL;

		iterMap++;
	}

	m_MapPriorityDbStatusItem.clear();

	return;
}

void CDbStatusItemList::addItem( CDbStatusItem::EDBPriority nDbServerPriority, CDbStatusItem* pDbStatusItem )
{
	QMutexLocker lock(&m_mutexMapPriorityDbStatusItem);	
	QMap<CDbStatusItem::EDBPriority, CDbStatusItem*>::Iterator  iterFind;

	CDbStatusItem* pItem = NULL;

	iterFind = m_MapPriorityDbStatusItem.find(nDbServerPriority);

	if (iterFind != m_MapPriorityDbStatusItem.end())
	{
		//find same
		pItem = (iterFind.value());

		delete pItem;
		pItem = NULL;

		m_MapPriorityDbStatusItem.erase(iterFind);
	}

	m_MapPriorityDbStatusItem.insert(nDbServerPriority, pDbStatusItem);

}

CDbStatusItem* CDbStatusItemList::getItem()
{
	QMutexLocker lock(&m_mutexMapPriorityDbStatusItem);	

	QMap<CDbStatusItem::EDBPriority, CDbStatusItem*>::Iterator  iterFind;
	CDbStatusItem* pItem = NULL;
	CDbStatusItem::EDBPriority nDbServerPriority = CDbStatusItem::DBPriority_0;

	iterFind = m_MapPriorityDbStatusItem.find(nDbServerPriority);

	if (iterFind != m_MapPriorityDbStatusItem.end())
	{
		//find same
		pItem = (iterFind.value());
	}
	return pItem;
}



