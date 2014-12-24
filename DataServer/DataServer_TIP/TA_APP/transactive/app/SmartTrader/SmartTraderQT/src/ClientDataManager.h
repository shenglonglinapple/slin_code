#ifndef __CLASS_CLIENT_DATA_MAMAGER__HH__
#define __CLASS_CLIENT_DATA_MAMAGER__HH__

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "OrderData.h"
#include "MyTradeClient.h"

class CClientLoginParam;
class CHistoryDataRequest;


class CClientDataManager : 
	public QObject,
	public CMyTradeClient
{
	Q_OBJECT
public:
	static CClientDataManager& getInstance();
	static void removeInstance();

private:
	static CClientDataManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CClientDataManager(void);
	~CClientDataManager(void);
public slots:

signals:
	

public:
	int req_login(CClientLoginParam* pClientLoginParam);
	void req_logoff();

	void req_downloadHistoryData(const CHistoryDataRequest* pHistoryDataRequest);
public:
	void req_subscribe_Instrument( unsigned int nInstrumentID );
	void req_unsubscribe_Instrument( unsigned int nInstrumentID );
	void req_newOrder(COrderData newOrderData);
public:
	void onInstrumentDownloaded(const CMyInstrument& instrument);//IProcessRecvData
	void onMarketDataUpdate( const CMyMarketData &marketData );
	void onHistoryDataDownloaded( QString requestID, pSetMyBarsPtr bars );
	void onBarDataUpdate(const CMyBarSummary &barData);

};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER__HH__


