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
	void slotFinished(QNetworkReply* reply);

public:
	void test();
	void getData(const QString& strUrl);
private:
	QNetworkAccessManager* m_pNetworkAccessManager;
};


#endif//__CLASS_STOCK_TCP_SERVER_H__
