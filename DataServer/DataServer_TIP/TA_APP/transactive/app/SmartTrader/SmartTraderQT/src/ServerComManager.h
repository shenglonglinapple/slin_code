#ifndef __CLASS_SERVER_COM_MANAGER_H__
#define __CLASS_SERVER_COM_MANAGER_H__

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "MyInstrument.h"
#include "MyMarketData.h"
#include "MyBar.h"
#include "OrderData.h"

class CMyTradeClient;

class CServerComManager
{
public:
	static CServerComManager& getInstance();
	static void removeInstance();

private:
	static CServerComManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CServerComManager();
	virtual ~CServerComManager();
public:
	void setDataProcessHandle(const CMyTradeClient* pHandle);
public:
	/// process receiving instrument information 
	void onInstrumentDownloaded(const CMyInstrument& instrument);
	void onMarketDataUpdate( const CMyMarketData &marketData );
	void onHistoryDataDownloaded( QString requestID, pSetMyBarsPtr bars );
	void onBarDataUpdate(const CMyBarSummary &barData);
	void onOrderFilled( const COrderData& order );

public:

private:
	CMyTradeClient* m_pMyTradeClientRef;
};


#endif //__CLASS_SERVER_COM_MANAGER_H__
