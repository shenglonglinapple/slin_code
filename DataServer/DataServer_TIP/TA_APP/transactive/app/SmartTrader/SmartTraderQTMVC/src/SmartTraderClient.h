#ifndef __CLASS_SMART_TRADER_CLIENT_HH__
#define __CLASS_SMART_TRADER_CLIENT_HH__

#include <QtCore/QObject>

#include "TradeClient.h"
#include "ClientLoginParam.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class IProcessRecvData;

class CSmartTraderClient : public QObject, public TradeClient
{ 
	Q_OBJECT



public:
	CSmartTraderClient(const CClientLoginParam& clientLoginParam);
	virtual ~CSmartTraderClient();
public:
	int loginToServer();
	void setProcessRecvDataHandle(IProcessRecvData* pHandle);
public:
	/// Hook method when receiving instrument information 
	virtual void onInstrumentDownloaded(const Instrument &instrument);
	virtual void onMarketDataUpdate(const Instrument &instrument);
	/// Hook method when account downloaded
	virtual void onAccountDownloaded(Account& account);


private:
	CClientLoginParam* m_pClientLoginParam;
	IProcessRecvData* m_pProcessRecvDataHandle;
}; 

//QT_END_NAMESPACE




#endif//__CLASS_SMART_TRADER_CLIENT_HH__



