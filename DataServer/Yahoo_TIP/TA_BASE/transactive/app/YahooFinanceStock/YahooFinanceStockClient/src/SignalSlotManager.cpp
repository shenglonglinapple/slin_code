#include "SignalSlotManager.h"

#include "ClientDataManager.h"
#include "ClientMainWindow.h"
#include "StockMinTimeMaxTimeTableView.h"
#include "StockHistoryDataTableView.h"
#include "UserTradeTableView.h"
#include "UserAccountWidget.h"

#include "Log4cppLogger.h"

CSignalSlotManager* CSignalSlotManager::m_pInstance = 0;
QMutex CSignalSlotManager::m_mutexInstance;

CSignalSlotManager& CSignalSlotManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CSignalSlotManager();
	}
	return (*m_pInstance);
}

void CSignalSlotManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CSignalSlotManager::CSignalSlotManager(void)
{	
	m_pRefSignal_ShownMessage = NULL;
	m_pRefSlot_ShownMessage = NULL;
	m_pRefSignal_DataChange_StockMinTimeMaxTime = NULL;
	m_pRefSlot_DataChange_StockMinTimeMaxTime = NULL;
	m_pRefSignal_DataChange_StockHistoryData = NULL;
	m_pRefSlot_DataChange_StockHistoryData = NULL;
	m_pRefSignal_DataChange_UserTrade = NULL;
	m_pRefSlot_DataChange_UserTrade = NULL;
	m_pRefSignal_DataChange_UserAccount = NULL;
	m_pRefSlot_DataChange_UserAccount = NULL;
	
}

CSignalSlotManager::~CSignalSlotManager(void)
{		

}

void CSignalSlotManager::set_Signal_ShownMessage( CClientDataManager* pRefSignal )
{
	m_pRefSignal_ShownMessage = pRefSignal;
}

void CSignalSlotManager::set_Slot_ShownMessage( CClientMainWindow* pRefSlot )
{
	m_pRefSlot_ShownMessage = pRefSlot;

	if (NULL != m_pRefSignal_ShownMessage && NULL != m_pRefSlot_ShownMessage)
	{
		QObject::connect(this, SIGNAL(signal_ShownMessage(QString)), this, SLOT(slot_ShownMessage(QString)));
	}
	else
	{
		QObject::disconnect(this, SIGNAL(signal_ShownMessage(QString)), this, SLOT(slot_ShownMessage(QString)));
	}
}

void CSignalSlotManager::slot_ShownMessage(QString strMessage)
{
	if (NULL != m_pRefSlot_ShownMessage)
	{
		m_pRefSlot_ShownMessage->slotShowMessage(strMessage);
	}
}

void CSignalSlotManager::emit_ShownMessage(QString strMessage)
{
	emit signal_ShownMessage(strMessage);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::set_Signal_DataChange_StockMinTimeMaxTime( CClientDataManager* pRefSignal )
{
	m_pRefSignal_DataChange_StockMinTimeMaxTime = pRefSignal;
}

void CSignalSlotManager::set_Slot_DataChange_StockMinTimeMaxTime( CStockMinTimeMaxTimeTableView* pRefSlot )
{
	m_pRefSlot_DataChange_StockMinTimeMaxTime = pRefSlot;

	if (NULL != m_pRefSignal_DataChange_StockMinTimeMaxTime && NULL != m_pRefSlot_DataChange_StockMinTimeMaxTime)
	{
		QObject::connect(this, SIGNAL(signal_DataChange_StockMinTimeMaxTime()), this, SLOT(slot_DataChange_StockMinTimeMaxTime()));
	}
	else
	{
		QObject::disconnect(this, SIGNAL(signal_DataChange_StockMinTimeMaxTime()), this, SLOT(slot_DataChange_StockMinTimeMaxTime()));
	}
}

void CSignalSlotManager::slot_DataChange_StockMinTimeMaxTime()
{
	if (NULL != m_pRefSlot_DataChange_StockMinTimeMaxTime)
	{
		m_pRefSlot_DataChange_StockMinTimeMaxTime->slot_DataChange_StockMinTimeMaxTime();
	}
}

void CSignalSlotManager::emit_DataChange_StockMinTimeMaxTime()
{
	emit signal_DataChange_StockMinTimeMaxTime();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::set_Signal_DataChange_StockHistoryData( CClientDataManager* pRefSignal )
{
	m_pRefSignal_DataChange_StockHistoryData = pRefSignal;
}

void CSignalSlotManager::set_Slot_DataChange_StockHistoryData( CStockHistoryDataTableView* pRefSlot )
{
	m_pRefSlot_DataChange_StockHistoryData = pRefSlot;

	if (NULL != m_pRefSignal_DataChange_StockHistoryData && NULL != m_pRefSlot_DataChange_StockHistoryData)
	{
		QObject::connect(this, SIGNAL(signal_DataChange_StockHistoryData()), this, SLOT(slot_DataChange_StockHistoryData()));
	}
	else
	{
		QObject::disconnect(this, SIGNAL(signal_DataChange_StockHistoryData()), this, SLOT(slot_DataChange_StockHistoryData()));
	}
}
void CSignalSlotManager::slot_DataChange_StockHistoryData()
{
	if (NULL != m_pRefSlot_DataChange_StockHistoryData)
	{
		m_pRefSlot_DataChange_StockHistoryData->slot_DataChange_StockHistoryData();
	}
}

void CSignalSlotManager::emit_DataChange_StockHistoryData()
{
	emit signal_DataChange_StockHistoryData();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::set_Signal_DataChange_UserTrade( CClientDataManager* pRefSignal )
{
	m_pRefSignal_DataChange_UserTrade = pRefSignal;
}

void CSignalSlotManager::set_Slot_DataChange_UserTrade( CUserTradeTableView* pRefSlot )
{
	m_pRefSlot_DataChange_UserTrade = pRefSlot;

	if (NULL != m_pRefSignal_DataChange_UserTrade && NULL != m_pRefSlot_DataChange_UserTrade)
	{
		QObject::connect(this, SIGNAL(signal_DataChange_UserTrade()), this, SLOT(slot_DataChange_UserTrade()));
	}
	else
	{
		QObject::disconnect(this, SIGNAL(signal_DataChange_UserTrade()), this, SLOT(slot_DataChange_UserTrade()));
	}
}

void CSignalSlotManager::slot_DataChange_UserTrade()
{
	if (NULL != m_pRefSlot_DataChange_UserTrade)
	{
		m_pRefSlot_DataChange_UserTrade->slot_DataChange_UserTrade();
	}
}

void CSignalSlotManager::emit_DataChange_UserTrade()
{
	emit signal_DataChange_UserTrade();
}


//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::set_Signal_DataChange_UserAccount( CClientDataManager* pRefSignal)
{
	m_pRefSignal_DataChange_UserAccount = pRefSignal;
}
void CSignalSlotManager::set_Slot_DataChange_UserAccount(CUserAccountWidget* pRefSlot)
{
	m_pRefSlot_DataChange_UserAccount = pRefSlot;

	if (NULL != m_pRefSignal_DataChange_UserAccount && NULL != m_pRefSlot_DataChange_UserAccount)
	{
		QObject::connect(this, SIGNAL(signal_DataChange_UserAccount()), this, SLOT(slot_DataChange_UserAccount()));
	}
	else
	{
		QObject::disconnect(this, SIGNAL(signal_DataChange_UserAccount()), this, SLOT(slot_DataChange_UserAccount()));
	}
}

void CSignalSlotManager::slot_DataChange_UserAccount()
{
	if (NULL != m_pRefSlot_DataChange_UserAccount)
	{
		m_pRefSlot_DataChange_UserAccount->slot_DataChange_UserAccount();
	}
}

void CSignalSlotManager::emit_DataChange_UserAccount()
{
	emit signal_DataChange_UserAccount();
}
