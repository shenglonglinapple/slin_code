#ifndef __CLASS_CLIENT_DATA_MAMAGER__HH__
#define __CLASS_CLIENT_DATA_MAMAGER__HH__

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "TcpComProtocol.h"

class CQtTimeHelper;
class CClientLoginParam;
class CHistoryData;
class CStockMinTimeMaxTime;
class CUserTradeInfo;
class CUserAccount;
class CUserHoldAccount;
class CStockInfo;

class CClientDataManager
{
public:
	static CClientDataManager& getInstance();
	static void removeInstance();

private:
	static CClientDataManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CClientDataManager(void);
	~CClientDataManager(void);
public:
	void setValue(const QString& strServerIP, quint16 nServerPort, const QString& strUserName, const QString& strPassWord);
public:
	void connectToServer_OK( qint32 nHandle, const QString& strServerIP, quint16 nServerPort);
	void createUser_OK(qint32 nHandle, const QString& strUserName, const QString& strPassWord);

	void loginToServer_OK(qint32 nHandle, const QString& strUserID);
	void dowork_downLoadUserAccountInfo(qint32 nHandle);
	void dowork_ReqSynYahoo( qint32 nHandle );

public:
	void resetDataHistory( const QString& strSymbolUse, const QList<CHistoryData*>& lstData );
	void resetNewOrderData( const QString& strSymbolUse, const CHistoryData* pData );
	void resetDataSymbolMinMaxTime(const CStockMinTimeMaxTime* pData );
	void insertUserTradeInfo(const CUserTradeInfo* pData);
	void resetUserAccount(const CUserAccount* pData);
	void resetUserHoldAccount(const QList<CUserHoldAccount*>& lstData);
	void resetAllStockInfo(const QList<CStockInfo*>& lstData);
public:
	void send_req_ReqCreateUser(qint32 nHandle, const QString& strUserName, const QString& strPassWord);
	void send_req_ReqLogin(qint32 nHandle, const QString& strUserName, const QString& strPassWord);
	void send_req_ReqDownLoadStock(qint32 nHandle);
	void send_req_ReqStockMinTimeMaxTime(qint32 nHandle, const QString& strSymbolUse);
	void send_req_ReqHistoryTrade( const QString& strSymbolUse, CTcpComProtocol::ETradeType nTradeType );
	void send_req_ReqUserAccount(const QString& strTime);
	void send_req_ReqUserHoldAccount(const QString& strSymbolUse);

	void send_req_ReqSynYahoo(qint32 nHandle, const QString& strSymbolUse);
	void send_req_ReqStockHistoryData(const QString& strSymbolUse, const QString& strTimeFrom, const QString& strTimeTo);
	void send_req_NewOrder(const CUserTradeInfo* pData);

private:
	QString m_strServerIP;// = "127.0.0.1";
	quint16 m_nServerPort;// = 5000;
	QString m_strUserID;
	QString m_strUserName;
	QString m_strPassWord;
	qint32 m_nHandle;
private:
	CQtTimeHelper* m_pQtTimeHelper;
};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER__HH__


