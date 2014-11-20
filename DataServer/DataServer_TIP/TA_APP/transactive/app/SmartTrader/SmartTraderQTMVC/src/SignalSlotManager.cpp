#include "SignalSlotManager.h"

//Data
#include "UserOrderInfo.h"
#include "TreeItemContract.h"
#include "TreeItemQuotes.h"
#include "TreeItemOrder.h"
#include "HistoryDataManager.h"
#include "ClientLoginParam.h"
#include "ClientDataManagerWorker.h"


//UI
#include "ClientLoginDialog.h"
#include "MidSubWidget.h"
#include "BottomDockWidget.h"
#include "SmartHotQuotesWindow.h"
#include "QuotesTableView.h"
#include "CreateNewOrderDialog.h"
#include "ContractInfoWindow.h"



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

	QObject::connect(this, SIGNAL(signalHistoryDataChanged(CHistoryDataManager*)),
		this, SLOT(slotHistoryDataChanged(CHistoryDataManager*)));
}

void CSignalSlotManager::emit_signalHistoryDataChanged( CHistoryDataManager* pParam )
{
	emit signalHistoryDataChanged(pParam);
}

void CSignalSlotManager::slotHistoryDataChanged( CHistoryDataManager* pParam )
{
	m_pSlot_HistoryDataChanged->slotHistoryDataChanged(pParam);
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
void CSignalSlotManager::setSignalSlot_QuotesInfoChanged(CClientDataManagerWorker* pSignal, CLeftDockWidget* pSlot)
{
	m_pSignal_QuotesInfoChanged = pSignal;
	m_pSlot_QuotesInfoChanged = pSlot;

	QObject::connect(this, SIGNAL(signalOrderInfoChanged(CTreeItemQuotes*)),
		this, SLOT(slotOrderInfoChanged(CTreeItemQuotes*)));
}

void CSignalSlotManager::emit_signalQuotesInfoChanged(CTreeItemQuotes* pParam)
{
	emit signalQuotesInfoChanged(pParam);
}

void CSignalSlotManager::slotQuotesInfoChanged(CTreeItemQuotes* pParam )
{
	m_pSlot_QuotesInfoChanged->slotQuotesInfoChanged(pParam);
}
//////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_QuotesTableViewColumnsChanged(CQuotesTableView* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_QuotesTableViewColumnsChanged = pSignal;
	m_pSlot_QuotesTableViewColumnsChanged = pSlot;

	QObject::connect(this, SIGNAL(signalQuotesTableViewColumnsChanged()),
		this, SLOT(slotQuotesTableViewColumnsChanged()));
}

void CSignalSlotManager::emit_signalQuotesTableViewColumnsChanged()
{
	emit signalQuotesTableViewColumnsChanged();
}

void CSignalSlotManager::slotQuotesTableViewColumnsChanged()
{
	m_pSlot_QuotesTableViewColumnsChanged->slotQuotesTableViewColumnsChanged();
}
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_RemoveContractFromSmartQuotes(CQuotesTableView* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_RemoveContractFromSmartQuotes = pSignal;
	m_pSlot_RemoveContractFromSmartQuotes = pSlot;

	QObject::connect(this, SIGNAL(signalRemoveContractFromSmartQuotes(unsigned int)),
		this, SLOT(slotRemoveContractFromSmartQuotes(unsigned int)));
}

void CSignalSlotManager::emit_signalRemoveContractFromSmartQuotes(unsigned int nParam)
{
	emit signalRemoveContractFromSmartQuotes(nParam);
}

void CSignalSlotManager::slotRemoveContractFromSmartQuotes(unsigned int nParam)
{
	m_pSlot_RemoveContractFromSmartQuotes->slotRemoveContractFromSmartQuotes(nParam);
}
//////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_ContractInfoWindowResetData(CQuotesTableView* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_ContractInfoWindowResetData = pSignal;
	m_pSlot_ContractInfoWindowResetData = pSlot;

	QObject::connect(this, SIGNAL(signalContractInfoWindowResetData()),
		this, SLOT(slotContractInfoWindowResetData()));
}

void CSignalSlotManager::emit_signalContractInfoWindowResetData()
{
	emit signalContractInfoWindowResetData();
}

void CSignalSlotManager::slotContractInfoWindowResetData()
{
	m_pSlot_ContractInfoWindowResetData->slotContractInfoWindowResetData();
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
void CSignalSlotManager::setSignalSlot_AddContractToSmartQuotes(CContractInfoWindow* pSignal, CClientDataManagerWorker* pSlot)
{
	m_pSignal_AddContractToSmartQuotes = pSignal;
	m_pSlot_AddContractToSmartQuotes = pSlot;

	QObject::connect(this, SIGNAL(signalAddContractToSmartQuotes(unsigned int)),
		this, SLOT(slotAddContractToSmartQuotes(unsigned int)));
}

void CSignalSlotManager::emit_signalAddContractToSmartQuotes(unsigned int nParam)
{
	emit signalAddContractToSmartQuotes(nParam);
}

void CSignalSlotManager::slotAddContractToSmartQuotes(unsigned int nParam)
{
	m_pSlot_AddContractToSmartQuotes->slotAddContractToSmartQuotes(nParam);
}
//////////////////////////////////////////////////////////////////////////











//////////////////////////////////////////////////////////////////////////
void CSignalSlotManager::setSignalSlot_ContractInfoChanged(CClientDataManagerWorker* pSignal, CContractInfoWindow* pSlot)
{
	m_pSignal_ContractInfoChanged = pSignal;
	m_pSlot_ContractInfoChanged = pSlot;

	QObject::connect(this, SIGNAL(signalContractInfoChanged(CTreeItemContract*)),
		this, SLOT(slotContractInfoChanged(CTreeItemContract*)));
}

void CSignalSlotManager::emit_signalContractInfoChanged(CTreeItemContract* pParam)
{
	emit signalContractInfoChanged(pParam);
}

void CSignalSlotManager::slotContractInfoChanged(CTreeItemContract* pParam )
{
	m_pSlot_ContractInfoChanged->slotContractInfoChanged(pParam);
}
//////////////////////////////////////////////////////////////////////////





