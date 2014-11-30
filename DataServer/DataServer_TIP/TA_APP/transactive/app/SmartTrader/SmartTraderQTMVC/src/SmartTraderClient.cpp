#include "SmartTraderClient.h"


#include "IProcessRecvData.h"

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CSmartTraderClient::CSmartTraderClient( const CClientLoginParam& clientLoginParam )
:TradeClient(clientLoginParam.m_strUserName,
			 clientLoginParam.m_strPassWord,
			 clientLoginParam.m_bEnableDebug)
{
	m_pClientLoginParam = NULL;
	m_pProcessRecvDataHandle = NULL;

	//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////

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

void CSmartTraderClient::onInstrumentDownloaded( const Instrument &instrument )
{
	/*
	MYLOG4CPP_DEBUG<<"onInstrumentDownloaded"
		<<" "<<"getInstrumentID="<<instrument.getInstrumentID();
	*/


	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onInstrumentDownloaded(instrument);
	}
	//TODO.ForTest
	//this->subscribeMarketData(instrument);
}


void CSmartTraderClient::onMarketDataUpdate( const Instrument &instrument )
{
	MYLOG4CPP_DEBUG<<"onMarketDataUpdate"
		<<" "<<"getInstrumentID="<<instrument.getInstrumentID();

	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onMarketDataUpdate(instrument);
	}
}

void CSmartTraderClient::onAccountDownloaded( Account& account )
{
	MYLOG4CPP_DEBUG<<"onAccountDownloaded"
		<<" "<<"getAccountID="<<account.getAccountID();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onAccountDownloaded(account);
	}

}

void CSmartTraderClient::onOrderAccepted( const Order &order )
{
	MYLOG4CPP_DEBUG<<"onOrderAccepted"
		<<" "<<"getOrderID="<<order.getOrderID();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onOrderAccepted(order);
	}
}

void CSmartTraderClient::onOrderCanceled( const Order &order )
{
	MYLOG4CPP_DEBUG<<"onOrderCanceled"
		<<" "<<"getOrderID="<<order.getOrderID();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onOrderCanceled(order);
	}
}

void CSmartTraderClient::onOrderRejected( const Order &order )
{
	MYLOG4CPP_DEBUG<<"onOrderRejected"
		<<" "<<"getOrderID="<<order.getOrderID();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onOrderRejected(order);
	}
}

void CSmartTraderClient::onOrderFilled( const Order &order )
{
	MYLOG4CPP_DEBUG<<"onOrderFilled"
		<<" "<<"getOrderID="<<order.getOrderID();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onOrderFilled(order);
	}
}

void CSmartTraderClient::onCancelReject( const Order &order )
{
	MYLOG4CPP_DEBUG<<"onCancelReject"
		<<" "<<"getOrderID="<<order.getOrderID();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onCancelReject(order);
	}
}

void CSmartTraderClient::onBarDataUpdate( const BarSummary &barData )
{
	MYLOG4CPP_DEBUG<<"CSmartTraderClient::onBarDataUpdate"
		<<" "<<"barData.instrumentID="<<barData.instrumentID
		<<" "<<"barData.bars.size="<<barData.bars.size();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onBarDataUpdate(barData);
	}
}

void CSmartTraderClient::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	MYLOG4CPP_DEBUG<<"CSmartTraderClient::onHistoryDataDownloaded"
		<<" "<<"requestID="<<requestID
		<<" "<<"bars->size()="<<bars->size();

	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onHistoryDataDownloaded(requestID, bars);
	}
}


//QT_END_NAMESPACE
















