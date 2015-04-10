#ifndef _CLASS_DB_STATUS_ITEM_LIST_H__
#define _CLASS_DB_STATUS_ITEM_LIST_H__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include "DbStatusItem.h"

class CDbStatusItemList
{
public:
	CDbStatusItemList();
	~CDbStatusItemList();
public:
	CDbStatusItem::EDataTypes m_nDataTypes;
public:
	QMutex m_mutexMapPriorityDbStatusItem;
	QMap<CDbStatusItem::EDBPriority, CDbStatusItem*> m_MapPriorityDbStatusItem;
	
public:
	void addItem(CDbStatusItem::EDBPriority nDbServerPriority, CDbStatusItem* pDbStatusItem);
	CDbStatusItem* getItem();
private:
	void _FreeData();

public:
	void logInfo( const QString& file, qint32 line );

};//class CDbStatusItemList



#endif //_CLASS_DB_STATUS_ITEM_LIST_H__



