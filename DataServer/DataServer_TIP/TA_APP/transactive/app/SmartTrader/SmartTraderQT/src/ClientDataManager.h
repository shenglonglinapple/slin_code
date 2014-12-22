#ifndef __CLASS_CLIENT_DATA_MAMAGER__HH__
#define __CLASS_CLIENT_DATA_MAMAGER__HH__

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "IProcessRecvData.h"
#include "OrderData.h"

class CClientLoginParam;
class CSmartTraderClient;
class CHistoryDataRequest;



class CClientDataManager : 
	public QObject,
	public IProcessRecvData
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
	int loginToServer(CClientLoginParam* pClientLoginParam);
	void downloadHistoryData(const CHistoryDataRequest* pHistoryDataRequest);
public:
	void onInstrumentDownloaded(const CMyInstrument& instrument);//IProcessRecvData
	void onMarketDataUpdate( const CMyMarketData &marketData );
	void onHistoryDataDownloaded( QString requestID, pSetMyBarsPtr bars );
	void onBarDataUpdate(const CMyBarSummary &barData);
public:
	void addUserInstrument( unsigned int nInstrumentID );
	void removeUserInstrument( unsigned int nInstrumentID );
	void newOrder(COrderData newOrderData);
private:
	void _InitTraderClient(CClientLoginParam* pClientLoginParam);
	void _UnInitTraderClient();
private:
	CSmartTraderClient* m_pSmartTraderClient;

};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER__HH__


