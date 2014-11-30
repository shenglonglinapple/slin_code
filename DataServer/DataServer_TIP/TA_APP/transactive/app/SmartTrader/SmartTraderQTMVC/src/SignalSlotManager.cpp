#include "SignalSlotManager.h"

//Data
#include "UserOrderInfo.h"
#include "ItemInstrumentInfo.h"

#include "ItemUserInstrumentInfo.h"
#include "ItemOrderInfo.h"
#include "HistoryDataManager.h"
#include "ClientLoginParam.h"
#include "ClientDataManagerWorker.h"


//UI
#include "ClientLoginDialog.h"
#include "MidSubWidget.h"
#include "BottomDockWidget.h"
#include "SmartHotQuotesWindow.h"
#include "UserInstrumentInfoView.h"
#include "CreateNewOrderDialog.h"
#include "InstrumentInfoView.h"



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

CSignalSlotManager::CSignalSlotManager( QWidget* parent /*= 0*/ )
{

}

CSignalSlotManager::~CSignalSlotManager()
{

}


//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_ClientLoginParamChanged(CClientLoginDialog* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_ClientLoginParamChanged = pSignal;
	m_pSlot_ClientLoginParamChanged = pSlot;

	QObject::connect(this, SIGNAL(signalClientLoginParamChanged(CClientLoginParam*)),
		this, SLOT(slotClientLoginParamChanged(CClientLoginParam*)));
}

void CSignalSlotManager::emit_signalClientLoginParamChanged( CClientLoginParam* pParam )
{
	emit signalClientLoginParamChanged(pParam);
}

void CSignalSlotManager::slotClientLoginParamChanged( CClientLoginParam* pParam )
{
	m_pSlot_ClientLoginParamChanged->slotClientLoginParamChanged(pParam);
}
//////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_HistoryDataChanged(CClientDataManagerWorker* pSignal, CMidSubWidget* pSlot)
{
	m_pSignal_HistoryDataChanged = pSignal;
	m_pSlot_HistoryDataChanged = pSlot;

	QObject::connect(this, SIGNAL(signalHistoryDataChanged(unsigned int )),
		this, SLOT(slotHistoryDataChanged(unsigned int )));
}

void CSignalSlotManager::emit_signalHistoryDataChanged( unsigned int nInstrumentID)
{
	emit signalHistoryDataChanged(nInstrumentID);
}

void CSignalSlotManager::slotHistoryDataChanged( unsigned int nInstrumentID )
{
	m_pSlot_HistoryDataChanged->slotHistoryDataChanged(nInstrumentID);
}
//////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_OrderInfoChanged(CClientDataManagerWorker* pSignal, CBottomDockWidget* pSlot)
{
	m_pSignal_OrderInfoChanged = pSignal;
	m_pSlot_OrderInfoChanged = pSlot;

	QObject::connect(this, SIGNAL(signalOrderInfoChanged(CTreeItemOrder*)),
		this, SLOT(slotOrderInfoChanged(CTreeItemOrder*)));
}

void CSignalSlotManager::emit_signalOrderInfoChanged(CTreeItemOrder* pParam)
{
	emit signalOrderInfoChanged(pParam);
}

void CSignalSlotManager::slotOrderInfoChanged(CTreeItemOrder* pParam )
{
	m_pSlot_OrderInfoChanged->slotOrderInfoChanged(pParam);
}
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_UserInstrumentInfoChanged(CClientDataManagerWorker* pSignal, CLeftDockWidget* pSlot)
{
	m_pSignal_UserInstrumentInfoChanged = pSignal;
	m_pSlot_UserInstrumentInfoChanged = pSlot;

	QObject::connect(this, SIGNAL(signalUserInstrumentInfoChanged(CItemUserInstrumentInfo*)),
		this, SLOT(slotUserInstrumentInfoChanged(CItemUserInstrumentInfo*)));
}

void CSignalSlotManager::emit_signalUserInstrumentInfoChanged(CItemUserInstrumentInfo* pParam)
{
	emit signalUserInstrumentInfoChanged(pParam);
}

void CSignalSlotManager::slotUserInstrumentInfoChanged(CItemUserInstrumentInfo* pParam )
{
	m_pSlot_UserInstrumentInfoChanged->slotUserInstrumentInfoChanged(pParam);
}
//////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_UserInstrumentViewColumnsChanged(CUserInstrumentInfoView* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_UserInstrumentViewColumnsChanged = pSignal;
	m_pSlot_UserInstrumentViewColumnsChanged = pSlot;

	QObject::connect(this, SIGNAL(signalUserInstrumentViewColumnsChanged()),
		this, SLOT(slotUserInstrumentViewColumnsChanged()));
}

void CSignalSlotManager::emit_signalUserInstrumentViewColumnsChanged()
{
	emit signalUserInstrumentViewColumnsChanged();
}

void CSignalSlotManager::slotUserInstrumentViewColumnsChanged()
{
	m_pSlot_UserInstrumentViewColumnsChanged->slotUserInstrumentViewColumnsChanged();
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_RemoveUserInstrument(CUserInstrumentInfoView* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_RemoveUserInstrument = pSignal;
	m_pSlot_RemoveUserInstrument = pSlot;

	QObject::connect(this, SIGNAL(signalRemoveUserInstrument(unsigned int)),
		this, SLOT(slotRemoveUserInstrument(unsigned int)));
}

void CSignalSlotManager::emit_signalRemoveUserInstrument(unsigned int nParam)
{
	emit signalRemoveUserInstrument(nParam);
}

void CSignalSlotManager::slotRemoveUserInstrument(unsigned int nParam)
{
	m_pSlot_RemoveUserInstrument->slotRemoveUserInstrument(nParam);
}
//////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_InstrumentViewResetData(CUserInstrumentInfoView* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_InstrumentViewResetData = pSignal;
	m_pSlot_InstrumentViewResetData = pSlot;

	QObject::connect(this, SIGNAL(signalInstrumentViewResetData()),
		this, SLOT(slotInstrumentViewResetData()));
}

void CSignalSlotManager::emit_signalInstrumentViewResetData()
{
	emit signalInstrumentViewResetData();
}

void CSignalSlotManager::slotInstrumentViewResetData()
{
	m_pSlot_InstrumentViewResetData->slotInstrumentViewResetData();
}
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_NewOrder(CCreateNewOrderDialog* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_NewOrder = pSignal;
	m_pSlot_NewOrder = pSlot;

	QObject::connect(this, SIGNAL(signalNewOrder(CUserOrderInfo*)),
		this, SLOT(slotNewOrder(CUserOrderInfo*)));
}

void CSignalSlotManager::emit_signalNewOrder(CUserOrderInfo* pParam)
{
	emit signalNewOrder(pParam);
}

void CSignalSlotManager::slotNewOrder(CUserOrderInfo* pParam )
{
	m_pSlot_NewOrder->slotNewOrder(pParam);
}
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_AddUserInstrument(CInstrumentInfoView* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_AddUserInstrument = pSignal;
	m_pSlot_AddUserInstrument = pSlot;

	QObject::connect(this, SIGNAL(signalAddUserInstrument(unsigned int)),
		this, SLOT(slotAddUserInstrument(unsigned int)));
}

void CSignalSlotManager::emit_signalAddUserInstrument(unsigned int nParam)
{
	emit signalAddUserInstrument(nParam);
}

void CSignalSlotManager::slotAddUserInstrument(unsigned int nParam)
{
	m_pSlot_AddUserInstrument->slotAddUserInstrument(nParam);
}
//////////////////////////////////////////////////////////////////////////











//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_InstrumentInfoChanged(CClientDataManagerWorker* pSignal, CInstrumentInfoView* pSlot)
{
	m_pSignal_InstrumentInfoChanged = pSignal;
	m_pSlot_InstrumentInfoChanged = pSlot;

	QObject::connect(this, SIGNAL(signalInstrumentInfoChanged(CItemInstrumentInfo*)),
		this, SLOT(slotInstrumentInfoChanged(CItemInstrumentInfo*)));
}

void CSignalSlotManager::emit_signalInstrumentInfoChanged(CItemInstrumentInfo* pParam)
{
	emit signalInstrumentInfoChanged(pParam);
}

void CSignalSlotManager::slotInstrumentInfoChanged(CItemInstrumentInfo* pParam )
{
	m_pSlot_InstrumentInfoChanged->slotInstrumentInfoChanged(pParam);
}
//////////////////////////////////////////////////////////////////////////





