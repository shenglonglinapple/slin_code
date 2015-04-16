#include "DbStatusItemList.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)

CDbStatusItemList::CDbStatusItemList()
{
	_FreeData();
}

CDbStatusItemList::~CDbStatusItemList()
{
	_FreeData();
}


void  CDbStatusItemList::logInfo()
{

}



void CDbStatusItemList::_FreeData()
{
	boost::mutex::scoped_lock lock(m_mutexMapPriorityDbStatusItem);	

	BOOST_LOG_FUNCTION();
	MapPriorityDbStatusItemIterT iterMap;
	CDbStatusItem* pItem = NULL;

	iterMap = m_MapPriorityDbStatusItem.begin();
	while (iterMap != m_MapPriorityDbStatusItem.end())
	{
		pItem = (iterMap->second);

		delete pItem;
		pItem = NULL;

		iterMap++;
	}

	m_MapPriorityDbStatusItem.clear();

	return;
}

void CDbStatusItemList::addItem( EDbServerPriority nDbServerPriority, CDbStatusItem* pDbStatusItem )
{
	boost::mutex::scoped_lock lock(m_mutexMapPriorityDbStatusItem);	

	MapPriorityDbStatusItemIterT iterFind;
	CDbStatusItem* pItem = NULL;

	iterFind = m_MapPriorityDbStatusItem.find(nDbServerPriority);

	if (iterFind != m_MapPriorityDbStatusItem.end())
	{
		//find same
		pItem = (iterFind->second);

		delete pItem;
		pItem = NULL;

		m_MapPriorityDbStatusItem.erase(iterFind);
	}


	m_MapPriorityDbStatusItem.insert(MapPriorityDbStatusItemValueTypeT(nDbServerPriority, pDbStatusItem));

}

CDbStatusItem* CDbStatusItemList::getItem()
{
	boost::mutex::scoped_lock lock(m_mutexMapPriorityDbStatusItem);	

	MapPriorityDbStatusItemIterT iterFind;
	CDbStatusItem* pItem = NULL;
	EDbServerPriority nDbServerPriority = DbServerPriority_0;

	iterFind = m_MapPriorityDbStatusItem.find(nDbServerPriority);

	if (iterFind != m_MapPriorityDbStatusItem.end())
	{
		//find same
		pItem = (iterFind->second);
	}
	return pItem;
}


NS_END(TA_Base_Core)



