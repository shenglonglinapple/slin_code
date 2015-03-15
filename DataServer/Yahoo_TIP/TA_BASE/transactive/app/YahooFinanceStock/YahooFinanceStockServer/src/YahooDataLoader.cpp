#include "YahooDataLoader.h"

#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

#include "YahuoHistoryReqAck.h"
#include "RequestYahuoDataHelper.h"
#include "StockDataManager.h"
#include "Log4cppLogger.h"

CYahooDataLoader::CYahooDataLoader( const QString& strSymbolUse, QObject *parent /*= 0*/ )
{
	m_strSymbolUse = strSymbolUse;


	m_pYahuoHistoryReqAck = NULL;
	m_pRequestYahuoDataHelper = NULL;
	m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_Unknown;

	m_pYahuoHistoryReqAck = new CYahuoHistoryReqAck();
	m_pRequestYahuoDataHelper = new CRequestYahuoDataHelper(strSymbolUse);

	m_pNetworkAccessManager = new QNetworkAccessManager(this);
	m_pNetworkRequest = new QNetworkRequest();

	connect(m_pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotFinished(QNetworkReply*)));
}


CYahooDataLoader::~CYahooDataLoader()
{

	if (NULL != m_pNetworkRequest)
	{
		delete m_pNetworkRequest;
		m_pNetworkRequest = NULL;
	}
	if (NULL != m_pNetworkAccessManager)
	{
		delete m_pNetworkAccessManager;
		m_pNetworkAccessManager = NULL;
	}


	if (NULL != m_pRequestYahuoDataHelper)
	{
		delete m_pRequestYahuoDataHelper;
		m_pRequestYahuoDataHelper = NULL;
	}

	if (NULL != m_pYahuoHistoryReqAck)
	{
		delete m_pYahuoHistoryReqAck;
		m_pYahuoHistoryReqAck = NULL;
	}

}



void CYahooDataLoader::sendRequest(const QString& strUrl)
{
	//http://table.finance.yahoo.com/table.csv?s=000001.sz
	//QString string("http://ichart.finance.yahoo.com/table.csv?s=GOOG&a=00&b=1&c=2014&d=02&e=1&f=2014");

	//http://ichart.finance.yahoo.com/table.csv?s=600155.SS&a=00&b=1&c=2014&d=02&e=1&f=2014
	//QString string = "http://ichart.finance.yahoo.com/table.csv?s=600155.SS&a=00&b=1&c=2014&d=02&e=1&f=2014";

	m_pNetworkRequest->setUrl(QUrl(strUrl));
	m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_SendReqToYahoo;
	MYLOG4CPP_DEBUG<<"m_nSynYahooResult="<<CTcpComProtocol::getStringValue(m_nSynYahooResult)<<" "<<"strUrl="<<strUrl;

	m_pNetworkAccessManager->get(*m_pNetworkRequest);
	m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_WaitAckFromYahoo;

}

void CYahooDataLoader::slotFinished(QNetworkReply* reply) 
{
	m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_RecvAckFromYahoo;
	m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_ProcessAckFromYahoo;

	QByteArray bytes = reply->readAll();
	QString strHistoryData = QString(bytes);
	
	MYLOG4CPP_DEBUG<<"m_nSynYahooResult="<<CTcpComProtocol::getStringValue(m_nSynYahooResult)
		<<" "<<"bytes.size()="<<bytes.size()
		<<" "<<"strHistoryData.size()="<<strHistoryData.size();

	//check res
	if (strHistoryData.isEmpty())
	{
		m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_SynYahooFinished;
	}
	else if (strHistoryData.contains("html"))
	{
		QString strUrl = m_pNetworkRequest->url().toString();
		if (strUrl.isEmpty())
		{
			m_strRequestUrl = strUrl;
		}
		MYLOG4CPP_ERROR<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"Reply contain html, strUrl="<<strUrl;
		MYLOG4CPP_DEBUG<<"m_nSynYahooResult="<<CTcpComProtocol::getStringValue(m_nSynYahooResult)
			<<" "<<"strHistoryData="<<strHistoryData;
		m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_SynYahooFinished;
	}
	else
	{
		CStockDataManager::getInstance().doWork_Save_HistoryData(m_strSymbolUse, strHistoryData);
		m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_SynYahooFinished;
	}

}





void CYahooDataLoader::synDataWithYahoo()
{
	int nFunRes = 0;
	unsigned int startYear = 0;
	unsigned int startMonth = 0;
	unsigned int startDay = 0;
	unsigned int endYear = 0;
	unsigned int endMonth = 0;
	unsigned int endDay = 0;
	QString strRequestUrl;

	if (m_strSymbolUse.isEmpty())
	{
		return;
	}

	m_pRequestYahuoDataHelper->getStartEndTimeValue(
		startYear, startMonth, startDay, 
		endYear, endMonth, endDay);

	strRequestUrl = m_pYahuoHistoryReqAck->getRequestUrl(
		m_strSymbolUse, 
		startYear, startMonth, startDay, 
		endYear, endMonth, endDay, 
		YahuoReqAck::daily);

	this->sendRequest(strRequestUrl);
	m_strRequestUrl = strRequestUrl;
	//MYLOG4CPP_DEBUG<<"m_strRequestUrl="<<m_strRequestUrl;


}


CTcpComProtocol::EDataTypeSynYahooResult CYahooDataLoader::getState_SynDataWithYahoo()
{
	return m_nSynYahooResult;
}






void CYahooDataLoader::test()
{
	//#include "YahooDataLoader.h"
	CYahooDataLoader* loader = new CYahooDataLoader(NULL);
	QString strUrl = "http://ichart.finance.yahoo.com/table.csv?s=600155.SS&a=00&b=1&c=2014&d=02&e=1&f=2014";
	loader->sendRequest(strUrl);

}







