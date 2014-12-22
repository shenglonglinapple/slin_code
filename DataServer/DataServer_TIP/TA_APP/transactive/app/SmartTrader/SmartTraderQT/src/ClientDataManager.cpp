#include "ClientDataManager.h"

#include <QtCore/QStringList>
#include <QtGui/QMessageBox>

//
#include "SmartTraderClient.h"
#include "ClientLoginParam.h"
#include "ConfigInfo.h"
//
#include "HistoryDataRequest.h"
//
#include "DataTotalMyInstrument.h"
#include "StaticStockManager.h"
//
#include "DataUserInstrument.h"
#include "DataWaitingInstrument.h"

#include "DataHistoryQuotesManager.h"
#include "SignalSlotManager.h"
//
#include "Log4cppLogger.h"

CClientDataManager* CClientDataManager::m_pInstance = 0;
QMutex CClientDataManager::m_mutexInstance;

CClientDataManager& CClientDataManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientDataManager();
	}
	return (*m_pInstance);
}

void CClientDataManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CClientDataManager::CClientDataManager(void)
{	
	m_pSmartTraderClient = NULL;	
	_InitTraderClient(NULL);

	CConfigInfo::getInstance();
	CStaticStockManager::getInstance();
	CDataTotalMyInstrument::getInstance();
	CDataHistoryQuotesManager::getInstance();
	CDataUserInstrument::getInstance();
	CDataWaitingInstrument::getInstance();

	CSignalSlotManager::getInstance().set_Signal_DataChange_UserInstrument(this);

}

CClientDataManager::~CClientDataManager(void)
{		
	CDataWaitingInstrument::removeInstance();
	CDataUserInstrument::removeInstance();
	CDataHistoryQuotesManager::removeInstance();
	CDataTotalMyInstrument::removeInstance();
	CStaticStockManager::removeInstance();
	CConfigInfo::removeInstance();
	_UnInitTraderClient();
}

void CClientDataManager::_InitTraderClient(CClientLoginParam* pClientLoginParam)
{
	if (NULL == pClientLoginParam)
	{
		return;
	}
	if (NULL == m_pSmartTraderClient)
	{
		m_pSmartTraderClient = new CSmartTraderClient(*pClientLoginParam);
		m_pSmartTraderClient->setProcessRecvDataHandle(this);
	}
}
void CClientDataManager::_UnInitTraderClient()
{
	if (NULL != m_pSmartTraderClient)
	{
		//TODO. debug mode will crash
		m_pSmartTraderClient->logoff();
		m_pSmartTraderClient->setProcessRecvDataHandle(NULL);

		delete m_pSmartTraderClient;
		m_pSmartTraderClient = NULL;
	}
}



int CClientDataManager::loginToServer(CClientLoginParam* pClientLoginParam )
{
	int nloginToServerRes = -1;

	MYLOG4CPP_DEBUG<<"CClientDataManager loginToServer";

	pClientLoginParam->logInfo(__FILE__, __LINE__);

	_InitTraderClient(pClientLoginParam);

	if (NULL != m_pSmartTraderClient)
	{
		nloginToServerRes = m_pSmartTraderClient->loginToServer();
	}

	return nloginToServerRes;
}

void CClientDataManager::onInstrumentDownloaded( const CMyInstrument& instrument )
{	
	if (instrument.getInstrumentID() == 900957)
	{
		MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::onInstrumentDownloaded"
			<<" "<<"getInstrumentID="<<instrument.getInstrumentID();
	}


	CDataTotalMyInstrument::getInstance().onInstrumentDownloaded(instrument);
	CDataWaitingInstrument::getInstance().addInstrument(instrument.getInstrumentID());


	if (CConfigInfo::getInstance().checkUserInstrument(instrument.getInstrumentID()))
	{
		addUserInstrument(instrument.getInstrumentID());
	}
}

void CClientDataManager::onMarketDataUpdate( const CMyMarketData &marketData )
{
	MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::onInstrumentDownloaded"
		<<" "<<"getSecurityID="<<marketData.getSecurityID();

	CDataTotalMyInstrument::getInstance().onMarketDataUpdate(marketData);
	if (CConfigInfo::getInstance().checkUserInstrument(marketData.getSecurityID()))
	{
		CDataUserInstrument::getInstance().updateDataUserInstrument(marketData.getSecurityID());
		//emit
		CSignalSlotManager::getInstance().emit_DataChange_UserInstrument();
	}
}

void CClientDataManager::onHistoryDataDownloaded( QString requestID, pSetMyBarsPtr bars )
{
	MYLOG4CPP_WARNING<<"CSmartTraderClient::onHistoryDataDownloaded"
		<<" "<<"std::auto_ptr<CMyBars> CMyBarsPtr  bars->size="<<bars->size();

	//std::auto_ptr<CMyBars> CMyBarsPtr 
	CDataHistoryQuotesManager::getInstance().onHistoryDataDownloaded(requestID, bars);

}

void CClientDataManager::onBarDataUpdate(const CMyBarSummary &barData)
{
	MYLOG4CPP_WARNING<<"CClientDataManager::onBarDataUpdate"
		<<" "<<"barData.instrumentID="<<barData.instrumentID
		<<" "<<"barData.bars.size()="<<barData.bars.size();

	//std::auto_ptr<CMyBars> CMyBarsPtr 
	CDataHistoryQuotesManager::getInstance().onBarDataUpdate(barData);

}

void CClientDataManager::downloadHistoryData(const CHistoryDataRequest* pHistoryDataRequest)
{
	CMyInstrument* pInstrument = NULL;
	enum EMyBarType interval;
	unsigned int from;
	unsigned int to ;
	QString requestID = 0;

	pInstrument = CDataTotalMyInstrument::getInstance().findInstrumentByID(pHistoryDataRequest->m_nInstruemntID);
	if (NULL == pInstrument)
	{
		return;
	}

	MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::downloadHistoryData"
		<<" "<<"m_nInstruemntID="<<pHistoryDataRequest->m_nInstruemntID
		<<" "<<"m_strInstrumentCode="<<pHistoryDataRequest->m_strInstrumentCode;

	interval = pHistoryDataRequest->m_nBarType;
	from = pHistoryDataRequest->m_nTimeFrom;
	to = pHistoryDataRequest->m_nTimeTo;

	requestID = m_pSmartTraderClient->downloadHistoryData(*pInstrument, interval, from, to);

	CDataHistoryQuotesManager::getInstance().addReqest(requestID, pHistoryDataRequest);

}

void CClientDataManager::addUserInstrument( unsigned int nInstrumentID )
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	CMyInstrument* pMyInstrumentRef = NULL;

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker addUserInstrument"
		<<" "<<"nInstrumentID="<<nInstrumentID;

	pMyInstrumentRef = NULL;
	pMyInstrumentRef = CDataTotalMyInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pMyInstrumentRef)
	{
		return;
	}

	//save to configfile
	CConfigInfo::getInstance().addInstrument(nInstrumentID);

	{
		//subscribe this instrument
		MYLOG4CPP_DEBUG<<"Client subscribeMarketData"<<" "<<"InstrumentID="<<nInstrumentID;
		m_pSmartTraderClient->subscribeMarketData(nInstrumentID);//subscribe this Instrument market data
	}


	{
		/*	
		add to CDataUserInstrument
		remove from CDataWaitingInstrument
		*/
		CDataWaitingInstrument::getInstance().removeInstrument(nInstrumentID);
		CDataUserInstrument::getInstance().addUserInstrument(nInstrumentID);
		//emit
		CSignalSlotManager::getInstance().emit_DataChange_UserInstrument();
	}


}


void CClientDataManager::removeUserInstrument( unsigned int nInstrumentID )
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	CMyInstrument* pMyInstrumentRef = NULL;

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker removeUserInstrument"
		<<" "<<"nInstrumentID="<<nInstrumentID;

	pMyInstrumentRef = NULL;
	pMyInstrumentRef = CDataTotalMyInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pMyInstrumentRef)
	{
		return;
	}

	//save to configfile
	CConfigInfo::getInstance().removeInstrument(nInstrumentID);

	{
		//subscribe this instrument
		MYLOG4CPP_DEBUG<<"Client unsubscribeMarketData"<<" "<<"InstrumentID="<<nInstrumentID;
		m_pSmartTraderClient->unsubscribeMarketData(nInstrumentID);//subscribe this Instrument market data
	}


	{
		/*	
		add to CDataWaitingInstrument
		remove from CDataUserInstrument
		*/
		CDataUserInstrument::getInstance().removeUserInstrument(nInstrumentID);
		CDataWaitingInstrument::getInstance().addInstrument(nInstrumentID);
		//emit
		CSignalSlotManager::getInstance().emit_DataChange_UserInstrument();
	}


}

void CClientDataManager::newOrder( COrderData newOrderData )
{
	COrderData::EOrderType nOrderType = COrderData::MARKET;
	COrderData::ESide nSide = COrderData::BUY;
	CMyInstrument* pMyInstrumentRef = NULL;
	QString strReqID = 0;
	MYLOG4CPP_DEBUG<<"CClientDataManager newOrder"
		<<" "<<"nInstrumentID="<<newOrderData.m_nInstrumentID;

	pMyInstrumentRef = NULL;
	pMyInstrumentRef = CDataTotalMyInstrument::getInstance().findInstrumentByID(newOrderData.m_nInstrumentID);
	if (NULL == pMyInstrumentRef)
	{
		return;
	}

	nOrderType = newOrderData.m_nOrderType;
	nSide = newOrderData.m_nSide;

	switch (nOrderType)
	{
	case COrderData::MARKET:
		if (COrderData::BUY == nSide)
		{
			MYLOG4CPP_DEBUG<<"Client BUY MARKET"
				<<" "<<"InstrumentCode="<<newOrderData.m_strInstrumentCode.toStdString()
				<<" "<<"nVolume="<<newOrderData.m_nVolume;
			strReqID = m_pSmartTraderClient->buyMarket(*pMyInstrumentRef, newOrderData.m_nVolume);//subscribe this Instrument market data
		}
		if (COrderData::SELL == nSide)
		{
			MYLOG4CPP_DEBUG<<"Client SELL MARKET"
				<<" "<<"InstrumentCode="<<newOrderData.m_strInstrumentCode.toStdString()
				<<" "<<"nVolume="<<newOrderData.m_nVolume;
			strReqID = m_pSmartTraderClient->sellMarket(*pMyInstrumentRef, newOrderData.m_nVolume);//subscribe this Instrument market data
		}
		break;
	default:
		break;
	}



}
