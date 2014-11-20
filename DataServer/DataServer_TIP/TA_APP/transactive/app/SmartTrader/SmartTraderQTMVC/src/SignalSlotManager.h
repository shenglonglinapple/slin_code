#ifndef __CLASS__SIGNALE_SLOT_MANAGER_H__
#define __CLASS__SIGNALE_SLOT_MANAGER_H__


#include <QtCore/QObject>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QString>



//Data
class CUserOrderInfo;
class CTreeItemContract;
class CTreeItemQuotes;
class CTreeItemOrder;
class CHistoryDataManager;
class CClientLoginParam;
class CClientDataManagerWorker;

//UI
class CClientLoginDialog;
class CMidSubWidget;
class CBottomDockWidget;
class CLeftDockWidget;
class CQuotesTableView;
class CCreateNewOrderDialog;
class CContractInfoWindow;



class CSignalSlotManager : public QObject
{
	Q_OBJECT
public:
	static CSignalSlotManager& getInstance();
	static void removeInstance();
private:
	static CSignalSlotManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CSignalSlotManager(QWidget* parent = 0);
	~CSignalSlotManager();
//////////////////////////////////////////////////////
private:
	CClientLoginDialog* m_pSignal_ClientLoginParamChanged;
	CClientDataManagerWorker* m_pSlot_ClientLoginParamChanged;
public:
	void setSignalSlot_ClientLoginParamChanged(CClientLoginDialog* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	//login in
	void slotClientLoginParamChanged(CClientLoginParam* pParam);
signals:
	//login in
	void signalClientLoginParamChanged(CClientLoginParam* pParam);
public:
	void emit_signalClientLoginParamChanged(CClientLoginParam* pParam);
//////////////////////////////////////////////////////	

	//////////////////////////////////////////////////////
private:
	CClientDataManagerWorker* m_pSignal_HistoryDataChanged;
	CMidSubWidget* m_pSlot_HistoryDataChanged;
public:
	void setSignalSlot_HistoryDataChanged(CClientDataManagerWorker* pSignal, CMidSubWidget* pSlot);
public slots:
	void slotHistoryDataChanged(CHistoryDataManager* pParam);
signals:
	void signalHistoryDataChanged(CHistoryDataManager* pParam);
public:
	void emit_signalHistoryDataChanged(CHistoryDataManager* pParam);
	//////////////////////////////////////////////////////	


	//////////////////////////////////////////////////////
private:
	CClientDataManagerWorker* m_pSignal_OrderInfoChanged;
	CBottomDockWidget* m_pSlot_OrderInfoChanged;
public:
	void setSignalSlot_OrderInfoChanged(CClientDataManagerWorker* pSignal, CBottomDockWidget* pSlot);
public slots:
	void slotOrderInfoChanged(CTreeItemOrder* pParam);
signals:
	void signalOrderInfoChanged(CTreeItemOrder* pParam);
public:
	void emit_signalOrderInfoChanged(CTreeItemOrder* pParam);
	//////////////////////////////////////////////////////	


	//////////////////////////////////////////////////////
private:
	CClientDataManagerWorker* m_pSignal_QuotesInfoChanged;
	CLeftDockWidget* m_pSlot_QuotesInfoChanged;
public:
	void setSignalSlot_QuotesInfoChanged(CClientDataManagerWorker* pSignal, CLeftDockWidget* pSlot);
public slots:
	void slotQuotesInfoChanged(CTreeItemQuotes* pParam);
signals:
	void signalQuotesInfoChanged(CTreeItemQuotes* pParam);
public:
	void emit_signalQuotesInfoChanged(CTreeItemQuotes* pParam);
	//////////////////////////////////////////////////////	


	//////////////////////////////////////////////////////
private:
	CQuotesTableView* m_pSignal_QuotesTableViewColumnsChanged;
	CClientDataManagerWorker* m_pSlot_QuotesTableViewColumnsChanged;
public:
	void setSignalSlot_QuotesTableViewColumnsChanged(CQuotesTableView* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotQuotesTableViewColumnsChanged();
signals:
	void signalQuotesTableViewColumnsChanged();
public:
	void emit_signalQuotesTableViewColumnsChanged();
	//////////////////////////////////////////////////////	


	//////////////////////////////////////////////////////
private:
	CQuotesTableView* m_pSignal_RemoveContractFromSmartQuotes;
	CClientDataManagerWorker* m_pSlot_RemoveContractFromSmartQuotes;
public:
	void setSignalSlot_RemoveContractFromSmartQuotes(CQuotesTableView* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotRemoveContractFromSmartQuotes(unsigned int nParam);
signals:
	void signalRemoveContractFromSmartQuotes(unsigned int nParam);
public:
	void emit_signalRemoveContractFromSmartQuotes(unsigned int nParam);
	//////////////////////////////////////////////////////	



	//////////////////////////////////////////////////////
private:
	CQuotesTableView* m_pSignal_ContractInfoWindowResetData;
	CClientDataManagerWorker* m_pSlot_ContractInfoWindowResetData;
public:
	void setSignalSlot_ContractInfoWindowResetData(CQuotesTableView* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotContractInfoWindowResetData();
signals:
	void signalContractInfoWindowResetData();
public:
	void emit_signalContractInfoWindowResetData();
	//////////////////////////////////////////////////////	



	//////////////////////////////////////////////////////
private:
	CCreateNewOrderDialog* m_pSignal_NewOrder;
	CClientDataManagerWorker* m_pSlot_NewOrder;
public:
	void setSignalSlot_NewOrder(CCreateNewOrderDialog* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotNewOrder(CUserOrderInfo* pParam);
signals:
	void signalNewOrder(CUserOrderInfo* pParam);
public:
	void emit_signalNewOrder(CUserOrderInfo* pParam);
	//////////////////////////////////////////////////////	



	//////////////////////////////////////////////////////
private:
	CContractInfoWindow* m_pSignal_AddContractToSmartQuotes;
	CClientDataManagerWorker* m_pSlot_AddContractToSmartQuotes;
public:
	void setSignalSlot_AddContractToSmartQuotes(CContractInfoWindow* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotAddContractToSmartQuotes(unsigned int nParam);
signals:
	void signalAddContractToSmartQuotes(unsigned int nParam);
public:
	void emit_signalAddContractToSmartQuotes(unsigned int nParam);
	//////////////////////////////////////////////////////	




	//////////////////////////////////////////////////////
private:
	CClientDataManagerWorker* m_pSignal_ContractInfoChanged;
	CContractInfoWindow* m_pSlot_ContractInfoChanged;
public:
	void setSignalSlot_ContractInfoChanged(CClientDataManagerWorker* pSignal, CContractInfoWindow* pSlot);
	public slots:
		void slotContractInfoChanged(CTreeItemContract* pParam);
signals:
		void signalContractInfoChanged(CTreeItemContract* pParam);
public:
	void emit_signalContractInfoChanged(CTreeItemContract* pParam);
	//////////////////////////////////////////////////////	





};

//QT_END_NAMESPACE

#endif//__CLASS__SIGNALE_SLOT_MANAGER_H__
