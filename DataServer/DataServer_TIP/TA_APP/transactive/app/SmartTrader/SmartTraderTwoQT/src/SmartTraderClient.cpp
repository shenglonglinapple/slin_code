#include "SmartTraderClient.h"

#include "IProcessRecvData.h"

#include "Log4cppLogger.h"

#include "DataTotalInstrument.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

#ifdef USING_YAHUO_DATA

CSmartTraderClient::CSmartTraderClient( const CClientLoginParam& clientLoginParam )
:CMyTradeClient(clientLoginParam.m_strUserName,
			 clientLoginParam.m_strPassWord,
			 clientLoginParam.m_bEnableDebug)
{
	m_pClientLoginParam = NULL;
	m_pProcessRecvDataHandle = NULL;

	m_pClientLoginParam = new CClientLoginParam();
	*m_pClientLoginParam = clientLoginParam;
}

CSmartTraderClient::~CSmartTraderClient()
{

	if (NULL != m_pClientLoginParam)
	{
		delete m_pClientLoginParam;
		m_pClientLoginParam = NULL;
	}
}


int CSmartTraderClient::loginToServer()
{
	int nFunRes = 0;

	MYLOG4CPP_DEBUG<<"beging logonToServer";

	try
	{
		nFunRes = this->logon(m_pClientLoginParam->m_strServerIP,
			m_pClientLoginParam->m_nServerPort,
			m_pClientLoginParam->m_bSynchronous);
	}
	catch (...)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR<<"login to server Error!";
	}

	
	MYLOG4CPP_DEBUG<<"end logonToServer, nFunRes="<<nFunRes;

	return nFunRes;
}


//////////////////////////////////////////////////////////////////////////



void CSmartTraderClient::setProcessRecvDataHandle( IProcessRecvData* pHandle )
{
	m_pProcessRecvDataHandle = pHandle;
}

void CSmartTraderClient::onInstrumentDownloaded( const CMyInstrument &instrument )
{	
	//MYLOG4CPP_DEBUG<<"CSmartTraderClient onInstrumentDownloaded"
	//	<<" "<<"getInstrumentID="<<instrument.getInstrumentID();
	
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onInstrumentDownloaded(instrument);
	}
	
}

void CSmartTraderClient::onMarketDataUpdate( const CMyMarketData &marketData )
{
	MYLOG4CPP_DEBUG<<"CSmartTraderClient onMarketDataUpdate"
		<<" "<<"getSecurityID="<<marketData.getSecurityID();

	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onMarketDataUpdate(marketData);

	}
}

void CSmartTraderClient::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	MYLOG4CPP_WARNING<<"CSmartTraderClient::onHistoryDataDownloaded"
		<<" "<<"std::auto_ptr<CMyBars> CMyBarsPtr bars->size="<<bars->size();

	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onHistoryDataDownloaded(requestID, bars);

	}

}


void CSmartTraderClient::onBarDataUpdate(const BarSummary &barData)
{
	MYLOG4CPP_WARNING<<"CSmartTraderClient::onBarDataUpdate"
		<<" "<<"barData.instrumentID="<<barData.instrumentID
		<<" "<<"barData.bars.size()="<<barData.bars.size();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onBarDataUpdate(barData);

	}

}

unsigned int CSmartTraderClient::my_downloadHistoryData( const CMyInstrument &instrument, enum BarType interval, unsigned int from, unsigned int to )
{
	unsigned int nReqID = 0;

	nReqID = this->downloadHistoryData(instrument, interval, from, to);
	return nReqID;
}


#else

CSmartTraderClient::CSmartTraderClient( const CClientLoginParam& clientLoginParam )
:TradeClient(clientLoginParam.m_strUserName,
				clientLoginParam.m_strPassWord,
				clientLoginParam.m_bEnableDebug)
{
	m_pClientLoginParam = NULL;
	m_pProcessRecvDataHandle = NULL;

	m_pClientLoginParam = new CClientLoginParam();
	*m_pClientLoginParam = clientLoginParam;
}

CSmartTraderClient::~CSmartTraderClient()
{

	if (NULL != m_pClientLoginParam)
	{
		delete m_pClientLoginParam;
		m_pClientLoginParam = NULL;
	}
}


int CSmartTraderClient::loginToServer()
{
	int nFunRes = 0;

	MYLOG4CPP_DEBUG<<"beging logonToServer";

	try
	{
		nFunRes = this->logon(m_pClientLoginParam->m_strServerIP,
			m_pClientLoginParam->m_nServerPort,
			m_pClientLoginParam->m_bSynchronous);
	}
	catch (...)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR<<"login to server Error!";
	}


	MYLOG4CPP_DEBUG<<"end logonToServer, nFunRes="<<nFunRes;

	return nFunRes;
}

void CSmartTraderClient::setProcessRecvDataHandle( IProcessRecvData* pHandle )
{
	m_pProcessRecvDataHandle = pHandle;
}

void CSmartTraderClient::onInstrumentDownloaded( const Instrument &instrument )
{	
	MYLOG4CPP_DEBUG<<"CSmartTraderClient onInstrumentDownloaded"
		<<" "<<"getInstrumentID="<<instrument.getInstrumentID();

	CDataTotalInstrument::getInstance().onInstrumentDownloaded(instrument);

	CMyInstrument myInstrument;
	myInstrument.setValue(&instrument);

	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onInstrumentDownloaded(myInstrument);
	}

}

void CSmartTraderClient::onMarketDataUpdate( const MarketData &marketData )
{
	MYLOG4CPP_DEBUG<<"CSmartTraderClient onMarketDataUpdate"
		<<" "<<"getSecurityID="<<marketData.getSecurityID();

	CMyMarketData myMarketData;
	myMarketData.setValue(marketData);

	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onMarketDataUpdate(myMarketData);

	}
}

void CSmartTraderClient::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	MYLOG4CPP_WARNING<<"CSmartTraderClient::onHistoryDataDownloaded"
		<<" "<<"std::auto_ptr<CMyBars> CMyBarsPtr bars->size="<<bars->size();

	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onHistoryDataDownloaded(requestID, bars);

	}

}


void CSmartTraderClient::onBarDataUpdate(const BarSummary &barData)
{
	MYLOG4CPP_WARNING<<"CSmartTraderClient::onBarDataUpdate"
		<<" "<<"barData.instrumentID="<<barData.instrumentID
		<<" "<<"barData.bars.size()="<<barData.bars.size();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onBarDataUpdate(barData);

	}

}

unsigned int CSmartTraderClient::my_downloadHistoryData( const CMyInstrument &instrument, enum BarType interval, unsigned int from, unsigned int to )
{
	Instrument* pInstrumentRef = NULL;
	unsigned int nReqID = 0;

	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(instrument.getInstrumentID());
	if (NULL == pInstrumentRef)
	{
		return nReqID;
	}

	nReqID = this->downloadHistoryData(*pInstrumentRef, interval, from, to);

	return nReqID;
}



#endif
















