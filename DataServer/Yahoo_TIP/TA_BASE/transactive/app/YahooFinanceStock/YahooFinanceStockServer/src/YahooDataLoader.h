#ifndef __CLASS_YAHOO_DATA_LOADER_H__
#define __CLASS_YAHOO_DATA_LOADER_H__

#include <QtCore/QObject>
#include <QtCore/QDate>
#include "TcpComProtocol.h"

class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;


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
	void getStartEndTimeValue( unsigned int& startYear, unsigned int& startMonth, unsigned int& startDay, unsigned int& endYear, unsigned int& endMonth, unsigned int& endDay );
private:
	QString m_strSymbolUse;
	CTcpComProtocol::EDataTypeSynYahooResult m_nSynYahooResult;
	QNetworkAccessManager* m_pNetworkAccessManager;
	QNetworkRequest* m_pNetworkRequest;
private:
	CYahuoHistoryReqAck* m_pYahuoHistoryReqAck;
	
private:
	QString m_strRequestUrl;
};


#endif//__CLASS_STOCK_TCP_SERVER_H__
