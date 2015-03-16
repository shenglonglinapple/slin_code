#include "YahooDataLoader.h"

#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

#include "YahuoHistoryReqAck.h"
#include "StockDataManager.h"
#include "Log4cppLogger.h"
#include "SymbolUseManager.h"
#include "QtTimeHelper.h"

static const int DEF_INT_ONE_DAY_SECONDS = 60*60*24;


CYahooDataLoader::CYahooDataLoader( const QString& strSymbolUse, QObject *parent /*= 0*/ )
{
	m_strSymbolUse = strSymbolUse;


	m_pYahuoHistoryReqAck = NULL;
	m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_Unknown;

	m_pYahuoHistoryReqAck = new CYahuoHistoryReqAck();

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
		CStockDataManager::getInstance().doWork_UpdateFailedCount(m_strSymbolUse);
		m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_SynYahooFinished;
	}
	else
	{
		CStockDataManager::getInstance().doWork_Save_HistoryData(m_strSymbolUse, strHistoryData);
		m_nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_SynYahooFinished;
	}

}




void CYahooDataLoader::getStartEndTimeValue( 
	unsigned int& startYear, unsigned int& startMonth, unsigned int& startDay, 
	unsigned int& endYear, unsigned int& endMonth, unsigned int& endDay )
{
	//QString strLastUpdateTime_FileDB;
	QString strLastUpdateTime_SQLiteDB;
	//time_t nLastUpdateTime_FileDB = 0;
	time_t nLastUpdateTime_SQLiteDB = 0;
	time_t nTimeLastUpdateDateTime = 0;
	time_t nTimeNow = 0;
	CQtTimeHelper* pQtTimeHelper = NULL;
	pQtTimeHelper = new CQtTimeHelper();

	CStockDataManager::getInstance().doWork_getMaxTime(m_strSymbolUse, strLastUpdateTime_SQLiteDB);

	//strLastUpdateTime_FileDB = m_pFileDBOper->getLastUpdateTime();//"1970-01-01 08:00:00"
	//nLastUpdateTime_FileDB = pQtTimeHelper->getTimeValue(strLastUpdateTime_FileDB);
	nLastUpdateTime_SQLiteDB = pQtTimeHelper->getTimeValue(strLastUpdateTime_SQLiteDB);

	nTimeLastUpdateDateTime = nLastUpdateTime_SQLiteDB;
	nTimeLastUpdateDateTime += DEF_INT_ONE_DAY_SECONDS;//"1970-01-02 08:00:00"
	nTimeNow = pQtTimeHelper->getCurrentTime();

	pQtTimeHelper->getTimeYearMonthDay(nTimeNow, endYear, endMonth, endDay);
	pQtTimeHelper->getTimeYearMonthDay(nTimeLastUpdateDateTime, startYear, startMonth, startDay);

	if (NULL != pQtTimeHelper)
	{
		delete pQtTimeHelper;
		pQtTimeHelper = NULL;
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
	int nFailedCount = 0;
	int nMaxUpdateFailedCount = 0;

	if (m_strSymbolUse.isEmpty())
	{
		return;
	}
	nMaxUpdateFailedCount = CSymbolUseManager::getMaxUpdateFailedCount();
	CStockDataManager::getInstance().doWork_Select_FailedCount(m_strSymbolUse, nFailedCount);
	if (nFailedCount >= nMaxUpdateFailedCount)
	{
		MYLOG4CPP_ERROR<<"error! check not send req again"
			<<" "<<"m_strSymbolUse="<<m_strSymbolUse
			<<" "<<"nFailedCount="<<nFailedCount
			<<" "<<"nMaxUpdateFailedCount="<<nMaxUpdateFailedCount;
		return;
	}
	getStartEndTimeValue(startYear, startMonth, startDay, endYear, endMonth, endDay);


// 	m_pRequestYahuoDataHelper->getStartEndTimeValue(
// 		startYear, startMonth, startDay, 
// 		endYear, endMonth, endDay);

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







