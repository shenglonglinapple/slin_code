#ifndef __CLASS_CLIENT_COM_MANAGER_H__
#define __CLASS_CLIENT_COM_MANAGER_H__

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "MyBar.h"
#include "MyInstrument.h"
#include "MyMarketData.h"



class CClientComManager
{
public:
	static CClientComManager& getInstance();
	static void removeInstance();

private:
	static CClientComManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CClientComManager();
	virtual ~CClientComManager();
public:
	/// Logon to the remote server
	int logon(const std::string &ip, unsigned int port, bool synchronous,
		const std::string &username, const std::string &password, bool enableDebug );

	/// Logoff from OMS
	void logoff();

	/// Subscribe real-time market data for specific instrument
	void subscribeMarketData(const CMyInstrument &instrument);
	void subscribeMarketData(unsigned int nInstrumentID);

	/// Unsubscribe the market data
	void unsubscribeMarketData(unsigned int nInstrumentID);
	//return req id
	QString downloadHistoryData( const CMyInstrument &instrument, enum EMyBarType interval, unsigned int from, unsigned int to );
public:
	/// Place a buy market order against specific instrument
	//return req id
	QString buyMarket(const CMyInstrument &instrument, int nVolume);

	/// Place a sell market order against specific instrument
	//return req id
	QString sellMarket(const CMyInstrument &instrument, int nVolume);
private:
	std::string m_strUserName;
	std::string m_strPassword;
	bool m_bEnableDebug;
	std::string m_strServerIP;
	int m_nServerPort;
	bool m_bSynchronous;
	int m_nLoginRes;
};


#endif //__CLASS_CLIENT_COM_MANAGER_H__
