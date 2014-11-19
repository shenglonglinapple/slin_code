#ifndef __CLASS_CLIENT_DATA_MAMAGER_WORKER__HH__
#define __CLASS_CLIENT_DATA_MAMAGER_WORKER__HH__


#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "IProcessRecvData.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CContractInfo;
class CTreeItemContract;
class CQuotesInfo;
class CTreeItemQuotes;
class CClientLoginParam;
class CSmartTraderClient;
class COrderInfo;
class CUserOrderInfo;
class CTreeItemOrder;
class CHistoryDataManager;
class CProjectUtilityFun;
class CProjectLogHelper;



class CClientDataManagerWorker : 
	public QObject,
	public IProcessRecvData
{
	Q_OBJECT

public:
	CClientDataManagerWorker(void);
	~CClientDataManagerWorker(void);

public slots:
	/*
	class: CClientLoginDialog
	signals:
	void signalClientLoginParamChanged(CClientLoginParam* pClientLoginParam);
	fun send signals: slotButtonLoginClicked()

	class: CClientDataManagerWorker
	public slots: 
	void slotClientLoginParamChanged(CClientLoginParam* pClientLoginParam);
	*/
	void slotClientLoginParamChanged(CClientLoginParam* pClientLoginParam);


	/*
	class: CContractInfoMainWindow
	signals:
	void signalAddContractToSmartQuotes(unsigned int nInstrumentID);
	fun send signals: slotTreeViewDoubleClick()

	class: CClientDataManagerWorker
	public slots: 
	void slotAddContractToSmartQuotes(unsigned int nInstrumentID);
	*/
	void slotAddContractToSmartQuotes(unsigned int nInstrumentID);

	/*
	class: CSmartHotQuotesWindow
	signals:
	void signalRemoveContractFromSmartQuotes(unsigned int nInstrumentID);
	fun send signals: slotTreeViewDoubleClick()

	class: CClientDataManagerWorker
	public slots: 
	void slotRemoveContractFromSmartQuotes(unsigned int nInstrumentID);
	*/
	void slotRemoveContractFromSmartQuotes(unsigned int nInstrumentID);


	/*
	class: CQuotesTableView
	signals:
	void signalContractInfoWindowResetData();
	fun send signals: CQuotesTableView::contextMenuEvent()
	CQuotesTableView::slotMouseRightClickInHHeaderView()

	class: CClientDataManagerWorker
	public slots: 
	void slotContractInfoWindowResetData();
	*/
	void slotContractInfoWindowResetData();
	
	/*
	class: CQuotesTableView
	signals:
	void signalQuotesTableViewColumnsChanged();
	fun send signals: slotQuotesTableViewColumnsChanged()

	class: CClientDataManagerWorker
	public slots: 
	void slotQuotesTableViewColumnsChanged();
	*/
	void slotQuotesTableViewColumnsChanged();


	/*
	class: CCreateNewOrderDialog
	signals:
	void signalNewOrder(CUserOrderInfo* pUserOrderInfo);
	fun send signals: slotClientLoginParamChanged()

	class: CClientDataManagerWorker
	public slots: 
	void slotNewOrder(CUserOrderInfo* pUserOrderInfo);
	*/
	void slotNewOrder(CUserOrderInfo* pUserOrderInfo);
signals:

	/*
	class: CClientDataManagerWorker
	signals:
	void signalLoginToServerResult(int nLoginResust);
	fun send signals: slotClientLoginParamChanged()

	class: CClientLoginDialog
	public slots: 
	void slotLoginToServerResult(int nLoginResust);
	*/
	void signalLoginToServerResult(int nLoginResust);

	/*
	class: CClientDataManagerWorker
	signals:
	void signalContractInfoChanged(CTreeItemContract* pTreeItem);
	fun send signals: onInstrumentDownloaded()

	class: CContractInfoMainWindow
	public slots: 
	void slotContractInfoChanged(CTreeItemContract* pTreeItem);
	*/
	void signalContractInfoChanged(CTreeItemContract* pTreeItem);

	/*
	class: CClientDataManagerWorker
	signals:
	void signalQuotesInfoChanged(CTreeItemQuotes* pTreeItem);
	fun send signals: slotAddContractToSmartQuotes()

	class: CSmartHotQuotesWindow
	public slots: 
	void slotQuotesInfoChanged(CTreeItemQuotes* pTreeItem);
	*/
	void signalQuotesInfoChanged(CTreeItemQuotes* pTreeItem);


	/*
	class: CClientDataManagerWorker
	signals:
	void signalOrderInfoChanged(CTreeItemOrder* pTreeItem);
	fun send signals: _InitMVCDataForOrder() slotAddContractToSmartQuotes() _UpdateOrderInfo()

	class: CBottomDockWidget
	public slots: 
	void slotOrderInfoChanged(CTreeItemOrder* pTreeItem);
	*/
	void signalOrderInfoChanged(CTreeItemOrder* pTreeItem);


	/*
	class: CClientDataManagerWorker
	signals:
	void signalHistoryDataChanged(CHistoryDataManager* pHistoryDataManager);
	fun send signals: onHistoryDataDownloaded()

	class: CMidSubWidget
	public slots: 
	void slotHistoryDataChanged(CHistoryDataManager* pHistoryDataManager);
	*/
	void signalHistoryDataChanged(CHistoryDataManager* pHistoryDataManager);
public:
	void onInstrumentDownloaded(const Instrument& instrument);//IProcessRecvData
	void onMarketDataUpdate(const Instrument& instrument);
	void onAccountDownloaded(Account& account);
	//order
	void onOrderAccepted(const Order &order);
	void onOrderCanceled(const Order &order);
	void onOrderRejected(const Order &order);
	void onOrderFilled(const Order &order);
	void onCancelReject(const Order &order);
	//history bar
	void onBarDataUpdate(const BarSummary &barData);
	void onHistoryDataDownloaded(unsigned int requestID, BarsPtr bars);
public:
	void _Test();
private:
	void _InitTraderClient();
	void _UnInitTraderClient();
	void _InitLoginParam();
	void _UnInitLoginParam();
private:
	void _UpdateOrderInfo(const Order &order);
	void _SignaleDataChange_DataUserContract();
	void _SignaleDataChange_DataUserOrder();
	void _SignaleDataChange_DataContract();
private:
	CClientLoginParam* m_pClientLoginParam;
	CSmartTraderClient* m_pMyTradeClient;

private:
	int m_nDoTest;
};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER_WORKER__HH__


