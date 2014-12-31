#ifndef __CLASS_YAHOO_DATA_LOADER_H__
#define __CLASS_YAHOO_DATA_LOADER_H__

#include <QtCore/QObject>
#include <QtCore/QDate>

class QNetworkAccessManager;
class QNetworkReply;

class CYahooDataLoader : public QObject
{
    Q_OBJECT

public:
    CYahooDataLoader(QObject *parent = 0);
	virtual ~CYahooDataLoader();
signals:

public slots:
	void printNewData(QNetworkReply* reply);

public:
	void getDataForCompany(QString companyName, QDate startDate, QDate endDate);
private:
	QNetworkAccessManager* m_pNetworkAccessManager;
};


#endif//__CLASS_STOCK_TCP_SERVER_H__
