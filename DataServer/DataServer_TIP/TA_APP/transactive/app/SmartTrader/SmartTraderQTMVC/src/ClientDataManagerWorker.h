#ifndef __CLASS_CLIENT_DATA_MAMAGER_WORKER__HH__
#define __CLASS_CLIENT_DATA_MAMAGER_WORKER__HH__

#include <boost/thread.hpp>

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include "BoostThread.h"

#include "IProcessRecvData.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CContractInfo;
class CTreeItemContract;
class CQuotesInfo;
class CTreeItemQuotes;
class CClientLoginParam;
class CSmartTraderClient;
class CProjectUtilityFun;
class COrderInfo;
class CTreeItemOrder;
class CHistoryDataManager;


class CClientDataManagerWorker : 
	public QObject,
	public CBoostThread, 
	public IProcessRecvData
{
	Q_OBJECT

private:
	enum EThreadJobState
	{
		JobState_Begin,

		JobState_InitParam,
		JobState_LoginToServer,
		JobState_MonitorExchangeInfo,

		JobState_StopWork,
		JobState_End,
	};
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
	void signalNewOrder(Order::Side nSide, Order::OrderType nOrderType, QString strInstrumentCode, double fPrice, int quantity);
	fun send signals: slotClientLoginParamChanged()

	class: CClientDataManagerWorker
	public slots: 
	void slotNewOrder(Order::Side nSide, Order::OrderType nOrderType, QString strInstrumentCode, double fPrice, int quantity);
	*/
	void slotNewOrder(Order::Side nSide, Order::OrderType nOrderType, QString strInstrumentCode, double fPrice, int quantity);
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
	virtual void run();	//CBoostThread
	virtual void terminate();//CBoostThread
	bool  isFinishWork();//CBoostThread
private:
	void _ThreadJob();
	int	 _ProcessUserTerminate();  
private:
	void _Process_MonitorExchangeInfo();
public:
	void _Process_InitParam();
	void _Process_LoginToServer();
	void _Process_StopWork();
public:
	void _Test();

private:
	void _InitLoginParam();
	void _UnInitLoginParam();
	void _InitTraderClient();
	void _UnInitTraderClient();
	void _InitMVCDataForContract();
	void _UnInitMVCDataForContract();
	void _InitMVCDataForQuotes();
	void _UnInitMVCDataForQuotes();
	void _InitMVCDataForOrder();
	void _UnInitMVCDataForOrder();
private:
	unsigned int _GetInstrumentIDByInstruemntCode(const QString& strInstrumentCode);

private:
	void _UpdateOrderInfo(const Order &order);

private:
	bool	m_toTerminate;
	EThreadJobState  m_nThreadJobState;
private:
	boost::mutex m_mutexForMapInstrumentIDData;
	QMap<unsigned int, Instrument*> m_MapInstrumentIDData;
private:
	boost::mutex m_mutexForNodeRootContract;
	CContractInfo* m_pContractInfo;
	CTreeItemContract* m_pTreeItemContract_Root;//total
	int m_SignalControl_NotWork;
	int m_IndexSigalControl;
private:
	boost::mutex m_mutexForNodeRootQuotes;
	CQuotesInfo* m_pQuotesInfo;
	CTreeItemQuotes* m_pTreeItemQuotes_Root;//submarket

private:
	CClientLoginParam* m_pClientLoginParam;
	CSmartTraderClient* m_pMyTradeClient;
	CProjectUtilityFun* m_pUtilityFun;
private:
	boost::mutex m_mutexForMapAccount;
	QMap<int, Account*> m_MapAccount;//AccountID

private:
	boost::mutex m_mutexForMapOrder;
	QMap<unsigned int, Order*> m_MapOrder;//OrderID
	COrderInfo* m_pOrderInfo;
	CTreeItemOrder* m_pTreeItemOrder_root;
private:
	boost::mutex m_mutexForMapHistoryData;
	QMap<unsigned int, CHistoryDataManager*> m_MapHistoryData;//instrumentID
	int m_nDoTest;
};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER_WORKER__HH__


