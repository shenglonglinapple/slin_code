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

class CInstrumentInfoHelper;
class CItemInstrumentInfo;
class CUserInstrumentInfoHelper;
class CItemUserInstrumentInfo;
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
	static CClientDataManagerWorker& getInstance();
	static void removeInstance();

private:
	static CClientDataManagerWorker* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CClientDataManagerWorker(void);
	~CClientDataManagerWorker(void);

public slots:
	void slotClientLoginParamChanged(CClientLoginParam* pClientLoginParam);
	void slotAddUserInstrument(unsigned int nInstrumentID);
	void slotRemoveUserInstrument(unsigned int nInstrumentID);
	void slotInstrumentViewResetData();
	void slotUserInstrumentViewColumnsChanged();
	void slotNewOrder(CUserOrderInfo* pUserOrderInfo);
	void slotRequestHistoryData( unsigned int nInstrumentID, enum BarType nBarType, unsigned int nTimeFrom, unsigned int nTimeTo);
	void slotRequestHistoryData_Subscribe( unsigned int nInstrumentID, enum BarType nBarType, int nBarCount, bool bSubscribe);

signals:
	void signalLoginToServerResult(int nResult);
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
public:
	void _Test();
private:
	void _InitTraderClient();
	void _UnInitTraderClient();
	void _InitLoginParam();
	void _UnInitLoginParam();
private:
	void _UpdateOrderInfo(const Order &order);
	void _MessageBoxOrderInfo(const Order &order, const std::string& strInfo);
private:
	void _Emit_SignalUserInstrumentInfoChanged();
	void _Emit_SignalOrderInfoChanged();
	void _Emit_SignalInstrumentInfoChanged();
	void _Emit_SignalHistoryDataChanged(unsigned int nInstrumentID);
private:
	CClientLoginParam* m_pClientLoginParam;
	CSmartTraderClient* m_pSmartTraderClient;
private:
	CProjectUtilityFun* m_pProjectUtilityFun;
	CProjectLogHelper* m_pProjectLogHelper;
private:
	int m_nDoTest;
};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER_WORKER__HH__


