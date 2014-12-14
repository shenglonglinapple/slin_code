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
	void slotClientLoginParamChanged(CClientLoginParam* pClientLoginParam);

signals:
	void signalLoginToServerResult(int nResult);
public:
	void onInstrumentDownloaded(const CMyInstrument& instrument);//IProcessRecvData
	void onMarketDataUpdate( const CMyMarketData &marketData );
	void onHistoryDataDownloaded( unsigned int requestID, CMyBarsPtr bars );
	void onBarDataUpdate(const CMyBarSummary &barData);

public:
	void downloadHistoryData(const CHistoryDataRequest* pHistoryDataRequest);

private:
	void _InitLoginParam();
	void _UnInitLoginParam();
	void _InitTraderClient();
	void _UnInitTraderClient();
private:
	CClientLoginParam* m_pClientLoginParam;
	CSmartTraderClient* m_pSmartTraderClient;

};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER__HH__


