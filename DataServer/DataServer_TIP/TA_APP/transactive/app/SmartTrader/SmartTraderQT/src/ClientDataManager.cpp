#include "ClientDataManager.h"

#include <QtCore/QStringList>
#include <QtGui/QMessageBox>

//
#include "MyTradeClient.h"
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
#include "DataUserOrder.h"

#include "DataHistoryQuotesManager.h"
#include "SignalSlotManager.h"
//
#include "MyServer.h"
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
	CMyServer::getInstance();

	CConfigInfo::getInstance();
	CStaticStockManager::getInstance();
	CDataTotalMyInstrument::getInstance();
	CDataHistoryQuotesManager::getInstance();
	CDataUserInstrument::getInstance();
	CDataUserOrder::getInstance();
	CDataWaitingInstrument::getInstance();

	CSignalSlotManager::getInstance().set_Signal_DataChange_UserInstrument(this);
	CSignalSlotManager::getInstance().set_Signal_DataChange_UserOrder(this);
}

CClientDataManager::~CClientDataManager(void)
{	
	CSignalSlotManager::getInstance().set_Signal_DataChange_UserInstrument(NULL);
	CSignalSlotManager::getInstance().set_Signal_DataChange_UserOrder(NULL);

	CDataWaitingInstrument::removeInstance();
	CDataUserOrder::removeInstance();
	CDataUserInstrument::removeInstance();
	CDataHistoryQuotesManager::removeInstance();
	CDataTotalMyInstrument::removeInstance();
	CStaticStockManager::removeInstance();
	CConfigInfo::removeInstance();
	CMyServer::removeInstance();

}




int CClientDataManager::req_login(CClientLoginParam* pClientLoginParam )
{
	int nloginToServerRes = -1;

	MYLOG4CPP_DEBUG<<"CClientDataManager req_login";

	pClientLoginParam->logInfo(__FILE__, __LINE__);


	{
		CMyServer::getInstance().setHandle(this);

		nloginToServerRes = this->logon(pClientLoginParam->m_strServerIP,
			pClientLoginParam->m_nServerPort, pClientLoginParam->m_bSynchronous,
			pClientLoginParam->m_strUserName, pClientLoginParam->m_strPassWord,
			pClientLoginParam->m_bEnableDebug);
	}

	return nloginToServerRes;
}
void CClientDataManager::req_logoff()
{
	this->logoff();
}


void CClientDataManager::req_downloadHistoryData(const CHistoryDataRequest* pHistoryDataRequest)
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

	MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::req_downloadHistoryData"
		<<" "<<"m_nInstruemntID="<<pHistoryDataRequest->m_nInstruemntID
		<<" "<<"m_strInstrumentCode="<<pHistoryDataRequest->m_strInstrumentCode;

	interval = pHistoryDataRequest->m_nBarType;
	from = pHistoryDataRequest->m_nTimeFrom;
	to = pHistoryDataRequest->m_nTimeTo;

	requestID = this->downloadHistoryData(*pInstrument, interval, from, to);

	CDataHistoryQuotesManager::getInstance().addReqest(requestID, pHistoryDataRequest);

}

void CClientDataManager::req_subscribe_Instrument( unsigned int nInstrumentID )
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	CMyInstrument* pMyInstrumentRef = NULL;

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker req_subscribe_Instrument"
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
		/*	
		add to CDataUserInstrument
		remove from CDataWaitingInstrument
		*/
		CDataWaitingInstrument::getInstance().removeInstrument(nInstrumentID);
		CDataUserInstrument::getInstance().addUserInstrument(nInstrumentID);
		//emit
		CSignalSlotManager::getInstance().emit_DataChange_UserInstrument();
	}



	{
		//subscribe this instrument
		MYLOG4CPP_DEBUG<<"Client subscribeMarketData"<<" "<<"InstrumentID="<<nInstrumentID;
		this->subscribeMarketData(nInstrumentID);//subscribe this Instrument market data
	}

}


void CClientDataManager::req_unsubscribe_Instrument( unsigned int nInstrumentID )
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	CMyInstrument* pMyInstrumentRef = NULL;

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker req_unsubscribe_Instrument"
		<<" "<<"nInstrumentID="<<nInstrumentID;

	pMyInstrumentRef = NULL;
	pMyInstrumentRef = CDataTotalMyInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pMyInstrumentRef)
	{
		return;
	}

	{
		//subscribe this instrument
		MYLOG4CPP_DEBUG<<"Client unsubscribeMarketData"<<" "<<"InstrumentID="<<nInstrumentID;
		this->unsubscribeMarketData(nInstrumentID);//subscribe this Instrument market data
	}

	//save to configfile
	CConfigInfo::getInstance().removeInstrument(nInstrumentID);

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

void CClientDataManager::req_newOrder( COrderData newOrderData )
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

	MYLOG4CPP_DEBUG<<"Client "
		<<" "<<newOrderData.getESide(nSide).toStdString()
		<<" "<<newOrderData.getEOrderType(nOrderType).toStdString()
		<<" "<<"InstrumentCode="<<newOrderData.m_strInstrumentCode.toStdString()
		<<" "<<"nVolume="<<newOrderData.m_nVolume;

	switch (nOrderType)
	{
	case COrderData::MARKET:
		if (COrderData::BUY == nSide)
		{
			strReqID = this->buyMarket(*pMyInstrumentRef, newOrderData.m_nVolume);//subscribe this Instrument market data
		}
		if (COrderData::SELL == nSide)
		{
			strReqID = this->sellMarket(*pMyInstrumentRef, newOrderData.m_nVolume);//subscribe this Instrument market data
		}
		break;
	default:
		break;
	}


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
		req_subscribe_Instrument(instrument.getInstrumentID());
	}
}

void CClientDataManager::onMarketDataUpdate( const CMyMarketData &marketData )
{
	MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::onMarketDataUpdate"
		<<" "<<"getSecurityID="<<marketData.getInstrumentID();

	CDataTotalMyInstrument::getInstance().onMarketDataUpdate(marketData);
	if (CConfigInfo::getInstance().checkUserInstrument(marketData.getInstrumentID()))
	{
		CDataUserInstrument::getInstance().updateDataUserInstrument(marketData.getInstrumentID());
		//emit
		CSignalSlotManager::getInstance().emit_DataChange_UserInstrument();
	}
}

void CClientDataManager::onHistoryDataDownloaded( QString requestID, pSetMyBarsPtr bars )
{
	MYLOG4CPP_WARNING<<"CClientDataManager::onHistoryDataDownloaded"
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

void CClientDataManager::onOrderFilled( const COrderData& order )
{
	CDataUserOrder::getInstance().addOrUpdate(order);
	CSignalSlotManager::getInstance().emit_DataChange_UserOrder();

}
