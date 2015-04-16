#ifndef _CLASS_DB_STATUS_ITEM_LIST_H__
#define _CLASS_DB_STATUS_ITEM_LIST_H__

#include <iostream>
#include <map>
#include <list>

#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include "core/DataAccess/src/DataAccessCommonData.h"

#include "core/DataAccess/src/DbStatusItem.h"

NS_BEGIN(TA_Base_Core)

class CDbStatusItemList
{
private:
	typedef std::map<EDbServerPriority, CDbStatusItem*>                      MapPriorityDbStatusItemT;
	typedef std::map<EDbServerPriority, CDbStatusItem*>::iterator            MapPriorityDbStatusItemIterT;
	typedef std::map<EDbServerPriority, CDbStatusItem*>::value_type          MapPriorityDbStatusItemValueTypeT;

public:
	CDbStatusItemList();
	~CDbStatusItemList();
public:
	EDataTypes m_nDataTypes;
public:
	boost::mutex m_mutexMapPriorityDbStatusItem;
	MapPriorityDbStatusItemT m_MapPriorityDbStatusItem;
	
public:
	void addItem(EDbServerPriority nDbServerPriority, CDbStatusItem* pDbStatusItem);
	CDbStatusItem* getItem();
private:
	void _FreeData();

public:
	void logInfo();


};//class CDbStatusItemList

NS_END(TA_Base_Core)

#endif //_CLASS_DB_STATUS_ITEM_LIST_H__



