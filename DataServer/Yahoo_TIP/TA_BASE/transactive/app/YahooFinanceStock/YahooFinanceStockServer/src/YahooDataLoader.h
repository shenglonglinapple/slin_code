#ifndef __CLASS_YAHOO_DATA_LOADER_H__
#define __CLASS_YAHOO_DATA_LOADER_H__

#include <QtCore/QObject>
#include <QtCore/QDate>
#include "TcpComProtocol.h"

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class CRequestYahuoDataHelper;
class CYahuoHistoryReqAck;

class CYahooDataLoader : public QObject
{
    Q_OBJECT

public:
    CYahooDataLoader(const QString& strSymbolUse, QObject *parent = 0);
	virtual ~CYahooDataLoader();
signals:

public slots:
	void slotFinished(QNetworkReply* reply);

public:
	void sendRequest(const QString& strUrl);
public:
	void synDataWithYahoo();
	CTcpComProtocol::EDataTypeSynYahooResult getState_SynDataWithYahoo();

public:
	void test();

private:
	QString m_strSymbolUse;
	CTcpComProtocol::EDataTypeSynYahooResult m_nSynYahooResult;
	QNetworkAccessManager* m_pNetworkAccessManager;
	QNetworkRequest* m_pNetworkRequest;
private:
	CYahuoHistoryReqAck* m_pYahuoHistoryReqAck;
	CRequestYahuoDataHelper* m_pRequestYahuoDataHelper;
};


#endif//__CLASS_STOCK_TCP_SERVER_H__
