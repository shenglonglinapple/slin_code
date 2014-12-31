#ifndef __CLASS_NETWORK_UTIL_H__
#define __CLASS_NETWORK_UTIL_H__

#include <string>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include <QtCore/QObject>
#include <QtCore/QDate>
#include <QtCore/QThread>

class QNetworkAccessManager;
class QNetworkReply;

/*
history:
http://ichart.finance.yahoo.com/table.csv?s=600155.SS&a=00&b=1&c=2014&d=02&e=1&f=2014

realtime:
http://finance.yahoo.com/d/quotes.csv?s=600667.SS&f=xsc6p2d1t1obaghml1t8va2n

*/

class CNetWorkUtil : public QThread
{
	Q_OBJECT
public:
	typedef enum enNetWorkStates
	{
		NetWork_STATE_READY,
		NetWork_STATE_SEND_REQ_START,
		NetWork_STATE_SEND_REQ_END,
		NetWork_STATE_GET_ACK,
		NetWork_STATE_PROCESS_ACK_START,
		NetWork_STATE_PROCESS_ACK_END,

	
		THREAD_STATE_UNKNOWN                                     
	}ENetWorkStates;

public:
	CNetWorkUtil(QObject *parent = 0);
	virtual ~CNetWorkUtil();

signals:

public slots:
	void slotFinished(QNetworkReply* reply);

public:	
	std::string getUrlData(const std::string& url);
protected:
	void run();
private:
	QNetworkAccessManager* m_pNetworkAccessManager;
	QString m_strData;
	ENetWorkStates m_nNetWorkStates;
};



#endif //__CLASS_NETWORK_UTIL_H__
