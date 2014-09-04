#include "SmartTraderClient.h"


#include "IProcessRecvData.h"
#include "TreeItemContract.h"
#include "ContractInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


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

	LOG_DEBUG<<"beging logonToServer";

	try
	{
		nFunRes = this->logon(m_pClientLoginParam->m_strServerIP,
			m_pClientLoginParam->m_nServerPort,
			m_pClientLoginParam->m_bSynchronous);
	}
	catch (...)
	{
		nFunRes = -1;
		LOG_ERROR<<"login to server Error!";
	}

	
	LOG_DEBUG<<"end logonToServer, nFunRes="<<nFunRes;

	return nFunRes;
}


//////////////////////////////////////////////////////////////////////////



void CSmartTraderClient::setProcessRecvDataHandle( IProcessRecvData* pHandle )
{
	m_pProcessRecvDataHandle = pHandle;
}

void CSmartTraderClient::onInstrumentDownloaded( const Instrument &instrument )
{
	LOG_DEBUG<<"onInstrumentDownloaded"
		<<" "<<"getInstrumentID="<<instrument.getInstrumentID();


	//BOOST_LOG_FUNCTION();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onInstrumentDownloaded(instrument);
	}
	
}


void CSmartTraderClient::onMarketDataUpdate( const Instrument &instrument )
{
	LOG_DEBUG<<"onMarketDataUpdate"
		<<" "<<"getInstrumentID="<<instrument.getInstrumentID();

	//BOOST_LOG_FUNCTION();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onMarketDataUpdate(instrument);
	}
}

void CSmartTraderClient::onAccountDownloaded( Account& account )
{
	LOG_DEBUG<<"onAccountDownloaded"
		<<" "<<"getAccountID="<<account.getAccountID();
	if (NULL != m_pProcessRecvDataHandle)
	{
		m_pProcessRecvDataHandle->onAccountDownloaded(account);
	}

}


//QT_END_NAMESPACE
















