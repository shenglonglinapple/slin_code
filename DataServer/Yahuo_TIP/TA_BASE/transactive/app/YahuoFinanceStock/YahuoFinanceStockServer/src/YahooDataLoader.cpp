#include "YahooDataLoader.h"

#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>


CYahooDataLoader::CYahooDataLoader(QObject *parent)
: QObject(parent)
{
	manager = new QNetworkAccessManager(this);

	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(printNewData(QNetworkReply*)));

}


CYahooDataLoader::~CYahooDataLoader()
{

}



void CYahooDataLoader::getDataForCompany(QString companyName, QDate startDate, QDate endDate) 
{
	//http://table.finance.yahoo.com/table.csv?s=000001.sz
	//QString string("http://ichart.finance.yahoo.com/table.csv?s=GOOG&a=00&b=1&c=2014&d=02&e=1&f=2014");
	QString string = "http://table.finance.yahoo.com/table.csv?s=000001.sz";

	QNetworkRequest request;
	request.setUrl(QUrl(string));

	manager->get(request);
}

void CYahooDataLoader::printNewData(QNetworkReply* reply) 
{

	QByteArray bytes = reply->readAll();
	QString string = QString::fromUtf8(bytes);

}