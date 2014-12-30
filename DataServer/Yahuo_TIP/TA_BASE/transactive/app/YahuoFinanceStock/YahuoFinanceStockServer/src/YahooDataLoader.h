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
	void getDataForCompany(QString companyName, QDate startDate, QDate endDate);
	void printNewData(QNetworkReply* reply);
private:
	QNetworkAccessManager* manager;
};


#endif//__CLASS_STOCK_TCP_SERVER_H__
