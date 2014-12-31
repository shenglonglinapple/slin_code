#include "NetWorkUtil.h"

#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

CNetWorkUtil::CNetWorkUtil( QObject *parent /*= 0*/ )
:QThread(parent)
{
	m_pNetworkAccessManager = NULL;
	m_strData.clear();
	m_nNetWorkStates = NetWork_STATE_READY;


	m_pNetworkAccessManager = new QNetworkAccessManager(this);
	QObject::connect(m_pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotFinished(QNetworkReply*)));

}

CNetWorkUtil::~CNetWorkUtil()
{

}

void CNetWorkUtil::slotFinished( QNetworkReply* reply )
{
	m_nNetWorkStates = NetWork_STATE_GET_ACK;
	
	m_nNetWorkStates = NetWork_STATE_PROCESS_ACK_START;

	QByteArray bytes = reply->readAll();
	m_strData = QString::fromUtf8(bytes);

	m_nNetWorkStates = NetWork_STATE_PROCESS_ACK_END;

}
/*
	history:
	http://ichart.finance.yahoo.com/table.csv?s=600155.SS&a=00&b=1&c=2014&d=02&e=1&f=2014

	realtime:
	http://finance.yahoo.com/d/quotes.csv?s=600667.SS&f=xsc6p2d1t1obaghml1t8va2n

*/
std::string CNetWorkUtil::getUrlData( const std::string& url )
{
	QNetworkRequest request;

	while (NetWork_STATE_READY != m_nNetWorkStates)
	{
		this->msleep(10);
	}
	
	m_nNetWorkStates = NetWork_STATE_SEND_REQ_START;

	m_strData.clear();

	request.setUrl(QUrl(url.c_str()));
	m_pNetworkAccessManager->get(request);

	m_nNetWorkStates = NetWork_STATE_SEND_REQ_END;

	while (NetWork_STATE_PROCESS_ACK_END != m_nNetWorkStates)
	{
		this->msleep(10);
	}
	m_nNetWorkStates = NetWork_STATE_READY;
	
	return m_strData.toStdString();
}

void CNetWorkUtil::run()
{

}
