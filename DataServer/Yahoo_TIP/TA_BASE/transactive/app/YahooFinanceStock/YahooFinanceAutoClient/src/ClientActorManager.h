#ifndef __CLASS_CLIENT_ACTOR_MANAGER_H__
#define __CLASS_CLIENT_ACTOR_MANAGER_H__

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QString>
#include "TcpComProtocol.h"

class QByteArray;
class CClientWorker;
class CStockMinTimeMaxTime;
class CHistoryData;
class CUserTradeInfo;
class CUserAccount;
class CUserHoldAccount;

class CClientActorManager 
{
public:
	static CClientActorManager& getInstance();
	static void removeInstance();

private:
	static CClientActorManager* m_pInstance;
	static QMutex m_mutexInstance;

private:
    CClientActorManager(void);
	~CClientActorManager(void);
public:	
	void createClient(const QString& strServerIP, quint16 nServerPort,
		 const QString& strUserName, const QString& strPassWord);
public:	
	void resetHanleValue( const CClientWorker* pActor, qint32 nHandle);
public:
	void send_req_ReqCreateUser(qint32 nHandle);
	void send_req_ReqLogin(qint32 nHandle);
	void send_req_ReqDownLoadStock(qint32 nHandle);
	void send_req_ReqStockMinTimeMaxTime(qint32 nHandle, const QString& strSymbolUse);
	void send_req_ReqHistoryTrade(qint32 nHandle, const QString& strSymbolUse, CTcpComProtocol::ETradeType nTradeType );
	void send_req_ReqUserAccount(qint32 nHandle, const QString& strTime);
	void send_req_ReqUserHoldAccount(qint32 nHandle, const QString& strSymbolUse);
	void send_req_ReqSynYahoo(qint32 nHandle, const QString& strSymbolUse);

public:
	void resetSymbolUse(qint32 nHandle, const QList<QString>& lstData );
	void getSymbolUseLst(qint32 nHandle, QList<QString>& lstData );
	void resetDataSymbolMinMaxTime(qint32 nHandle, const CStockMinTimeMaxTime* pData );
	void resetHistoryData(qint32 nHandle, const QString& strSymbolUse, const QList<CHistoryData*>& lstData );
    void insertUserTradeInfo(qint32 nHandle, const QList<CUserTradeInfo*>& LstData);
	void insertUserTradeInfo(qint32 nHandle, const CUserTradeInfo* pData);
	void resetUserAccount(qint32 nHandle, const CUserAccount* pData);
	void resetUserHoldAccount(qint32 nHandle, const QList<CUserHoldAccount*>& lstData);

private:
	QMutex m_mutex_MapClientActor;
	QMap<qint32, CClientWorker*> m_MapClientActor;
	qint32 m_nHandleAuto;
};

#endif//__CLASS_CLIENT_ACTOR_MANAGER_H__
