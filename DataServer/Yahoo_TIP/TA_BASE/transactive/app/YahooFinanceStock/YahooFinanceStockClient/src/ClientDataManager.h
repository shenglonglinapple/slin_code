#ifndef __CLASS_CLIENT_DATA_MAMAGER__HH__
#define __CLASS_CLIENT_DATA_MAMAGER__HH__

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CQtTimeHelper;
class CClientLoginParam;
class CHistoryData;
class CStockMinTimeMaxTime;
class CUserTradeInfo;

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
	void connectedToServer(qint32 nHandle, QString strServerIP, quint16 nServerPort, QString strUserName, QString strPassWord);
	void loginedToServer(qint32 nHandle, QString strUserName, QString strPassWord);
	void downLoadStockFromServer(qint32 nHandle);
public:
	void resetDataHistory( const QString& strSymbolUse, const QList<CHistoryData*>& lstData );
	void resetDataSymbolMinMaxTime(const CStockMinTimeMaxTime* pData );
	void resetDataUserTradeInfo(const CUserTradeInfo* pData);

public:
	void send_req_ReqSynYahoo(qint32 nHandle, const QString& strSymbolUse);
	void send_req_ReqDownLoadStock(qint32 nHandle);
	void send_req_CReqLogin(qint32 nHandle, const QString& strUserName, const QString& strPassWord);
	void send_req_ReqStockMinTimeMaxTime(qint32 nHandle, const QString& strSymbolUse);
	void send_req_ReqStockHistoryData(const QString& strSymbolUse, const QString& strTimeFrom, const QString& strTimeTo);
private:
	QString m_strServerIP;// = "127.0.0.1";
	quint16 m_nServerPort;// = 5000;
	QString m_strUserName;
	QString m_strPassWord;
	qint32 m_nHandle;
private:
	CQtTimeHelper* m_pQtTimeHelper;
};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER__HH__


