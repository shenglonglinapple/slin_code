#include "ClientDataManagerWorker.h"

#include <QtCore/QStringList>
#include <QtGui/QMessageBox>
#include "Bar.h"
#include "Instrument.h"

#include "ClientLoginParam.h"
#include "SmartTraderClient.h"
#include "ProjectUtilityFun.h"
#include "ProjectLogHelper.h"
#include "ConfigInfo.h"


#include "UserInstrumentInfoHelper.h"
#include "ItemUserInstrumentInfo.h"

#include "OrderInfoHelper.h"
#include "UserOrderInfo.h"
#include "ItemOrderInfo.h"

#include "HistoryDataManager.h"
#include "Log4cppLogger.h"

#include "DataTotalInstrument.h"
#include "DataInstrument.h"
#include "DataUserInstrument.h"
#include "DataUserAccount.h"
#include "DataUserOrder.h"
#include "DataUserHistoryBar.h"

#include "InstrumentInfoHelper.h"
#include "ItemInstrumentInfo.h"

#include "SignalSlotManager.h"


CClientDataManagerWorker* CClientDataManagerWorker::m_pInstance = 0;
QMutex CClientDataManagerWorker::m_mutexInstance;

CClientDataManagerWorker& CClientDataManagerWorker::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientDataManagerWorker();
	}
	return (*m_pInstance);
}

void CClientDataManagerWorker::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CClientDataManagerWorker::CClientDataManagerWorker(void)
{	
	m_pClientLoginParam = NULL;
	m_pSmartTraderClient = NULL;

	CDataInstrument::getInstance();
	CDataUserInstrument::getInstance();
	CDataUserOrder::getInstance();
	CDataUserHistoryBar::getInstance();
	CDataTotalInstrument::getInstance();
	
	_InitLoginParam();
	_InitTraderClient();

	//TODO. for Test
	m_nDoTest = 0;
}

CClientDataManagerWorker::~CClientDataManagerWorker(void)
{		
	_UnInitTraderClient();
	_UnInitLoginParam();

	CDataTotalInstrument::removeInstance();
	CDataUserHistoryBar::removeInstance();
	CDataUserOrder::removeInstance();
	CDataUserInstrument::removeInstance();
	CDataInstrument::removeInstance();

}



void CClientDataManagerWorker::_InitLoginParam()
{
	m_pClientLoginParam = new CClientLoginParam();
	m_pClientLoginParam->setDefaultValue();
}
void CClientDataManagerWorker::_UnInitLoginParam()
{
	if (NULL != m_pClientLoginParam)
	{
		delete m_pClientLoginParam;
		m_pClientLoginParam = NULL;
	}
}



void CClientDataManagerWorker::onInstrumentDownloaded( const Instrument& instrument )
{
	unsigned int nGetInstrumentID = 0;
	std::string strLogInfo;

	nGetInstrumentID = instrument.getInstrumentID();
	
	CDataTotalInstrument::getInstance().onInstrumentDownloaded(instrument);
	CDataInstrument::getInstance().onInstrumentDownloaded(instrument);

	
	//subscribeMarketData user Instrument
	QString strUserInstruemt = QString("%1").arg(nGetInstrumentID);
	if (CConfigInfo::getInstance().checkUserInstrument(strUserInstruemt))
	{
		slotAddUserInstrument(nGetInstrumentID);
	}	
}


void CClientDataManagerWorker::onMarketDataUpdate(const Instrument& instrument)
{
	CDataTotalInstrument::getInstance().onMarketDataUpdate(instrument);

	
	{
		CDataUserInstrument::getInstance().onMarketDataUpdate(instrument);
		_Emit_SignalUserInstrumentInfoChanged();
	}



}

void CClientDataManagerWorker::slotAddUserInstrument( unsigned int nInstrumentID )
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	Instrument* pInstrumentRef = NULL;
	QMap<unsigned int, Instrument*>::iterator  iterFind;

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process slotAddContractToSmartQuotes"
		<<" "<<"nInstrumentID="<<nInstrumentID;

	pInstrumentRef = NULL;
	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);

	if (NULL == pInstrumentRef)
	{
		//TODO.
		return;
	}

	{
		//find ok
		//save to configfile
		QString strUserInstruemt = QString("%1").arg(nInstrumentID);
		CConfigInfo::getInstance().addInstrument(strUserInstruemt);
		//subscribe this instrument
		MYLOG4CPP_DEBUG<<"subscribeMarketData"<<" "<<"InstrumentID="<<nInstrumentID;
		m_pSmartTraderClient->subscribeMarketData(nInstrumentID);//subscribe this Instrument market data

	}


	{
		/*	
		add to CDataUserInstrument
		remove from CDataInstrument will at slotInstrumentViewResetData()
		*/
		CDataUserInstrument::getInstance().addByData(pInstrumentRef);
		_Emit_SignalUserInstrumentInfoChanged();
	}

	{
		//set Current Instrument
		setCurrentInstrument(nInstrumentID);
	}


		
}

void CClientDataManagerWorker::slotRemoveUserInstrument( unsigned int nInstrumentID )
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	Instrument* pInstrumentRef = NULL;
	QMap<unsigned int, Instrument*>::iterator  iterFind;

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process slotRemoveContractFromSmartQuotes"
		<<" "<<"nInstrumentID="<<nInstrumentID;

	pInstrumentRef = NULL;
	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	//check
	if (NULL == pInstrumentRef)
	{
		//TODO.
		return;
	}

	{
		//find ok
		//unsubscribe this instrument
		MYLOG4CPP_DEBUG<<"unsubscribeMarketData"
			<<" "<<"InstrumentID="<<pInstrumentRef->getInstrumentID();
		m_pSmartTraderClient->unsubscribeMarketData(pInstrumentRef->getInstrumentID());

		//save to config file
		QString strInstrumentID = QString("%1").arg(pInstrumentRef->getInstrumentID());
		CConfigInfo::getInstance().removeInstrument(strInstrumentID);
	}


	//remove and add
	{
		/*	
		remove from CDataUserInstrument
		add to CDataInstrument
		*/
		CDataUserInstrument::getInstance().removeByData(pInstrumentRef);
		_Emit_SignalUserInstrumentInfoChanged();

		CDataInstrument::getInstance().addByData(pInstrumentRef);
		_Emit_SignalContractInfoChanged();
	}

}


void CClientDataManagerWorker::_InitTraderClient()
{
	m_pSmartTraderClient = new CSmartTraderClient(*m_pClientLoginParam);
	m_pSmartTraderClient->setProcessRecvDataHandle(this);
}
void CClientDataManagerWorker::_UnInitTraderClient()
{
	if (NULL != m_pSmartTraderClient)
	{
		//TODO. debug mode will crash
		//m_pMyTradeClient->logoff();
		m_pSmartTraderClient->setProcessRecvDataHandle(NULL);

		delete m_pSmartTraderClient;
		m_pSmartTraderClient = NULL;
	}
}


void CClientDataManagerWorker::slotClientLoginParamChanged( CClientLoginParam* pClientLoginParam )
{
	int nloginToServerRes = 0;

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process slotClientLoginParamChanged"
		<<" "<<"pClientLoginParam=0x"<<pClientLoginParam;

	_UnInitLoginParam();
	_InitLoginParam();
	*m_pClientLoginParam = *pClientLoginParam;

	_UnInitTraderClient();
	_InitTraderClient();
	nloginToServerRes = m_pSmartTraderClient->loginToServer();

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"slotClientLoginParamChanged()"
		<<" "<<"emit"
		<<" "<<"signalLoginToServerResult(int)"
		<<" "<<"param:"
		<<" "<<"nloginToServerRes="<<nloginToServerRes;

	emit signalLoginToServerResult(nloginToServerRes);
}

void CClientDataManagerWorker::_Test()
{
	_UnInitLoginParam();
	_InitLoginParam();
	

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"_Test()"
		<<" "<<"emit"
		<<" "<<"signalLoginToServerResult(int)"
		<<" "<<"param:"
		<<" "<<"nloginToServerRes="<<0;
	emit signalLoginToServerResult(0);

	
	CDataTotalInstrument::getInstance()._Test();
	
	CDataInstrument::getInstance()._Test();
	_Emit_SignalContractInfoChanged();


	CDataUserInstrument::getInstance()._Test();
	_Emit_SignalUserInstrumentInfoChanged();

	_Emit_SignalOrderInfoChanged();
}



void CClientDataManagerWorker::slotUserInstrumentViewColumnsChanged()
{
	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process slotQuotesTableViewColumnsChanged";

	//subscribeMarketData user hot Instrument
	QStringList lstUserInstrument;
	Instrument* pInstrumentRef = NULL;
	unsigned int nInstrumentID = 0;
	QMap<unsigned int, Instrument*>::iterator  iterFind;

	lstUserInstrument = CConfigInfo::getInstance().getLstUserInstrument();
	
	{
		CDataUserInstrument::removeInstance();
		CDataUserInstrument::getInstance();
	}

	{
		//reset child data
		foreach (const QString& strInstrument, lstUserInstrument)
		{
			nInstrumentID = strInstrument.toUInt();
			pInstrumentRef = NULL;
			pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
			if (NULL != pInstrumentRef)
			{
				CDataUserInstrument::getInstance().addByData(pInstrumentRef);
			}//if
		}//foreach

		_Emit_SignalUserInstrumentInfoChanged();
	}

	return;
}

void CClientDataManagerWorker::onAccountDownloaded( Account& account )
{
	CDataUserAccount::getInstance().onAccountDownloaded(account);
}


void CClientDataManagerWorker::onOrderAccepted(const Order &order)
{
	std::string strInfo = "OrderAccepted";
	_UpdateOrderInfo(order);
	_MessageBoxOrderInfo(order, strInfo);
}
void CClientDataManagerWorker::onOrderCanceled(const Order &order)
{
	std::string strInfo = "OrderCanceled";
	_UpdateOrderInfo(order);
	_MessageBoxOrderInfo(order, strInfo);
}
void CClientDataManagerWorker::onOrderRejected(const Order &order)
{
	std::string strInfo = "OrderRejected";
	_UpdateOrderInfo(order);
	_MessageBoxOrderInfo(order, strInfo);
}
void CClientDataManagerWorker::onOrderFilled(const Order &order)
{
	std::string strInfo = "OrderFilled";
	_UpdateOrderInfo(order);
	_MessageBoxOrderInfo(order, strInfo);
}
void CClientDataManagerWorker::onCancelReject(const Order &order)
{
	std::string strInfo = "CancelReject";
	_UpdateOrderInfo(order);
	_MessageBoxOrderInfo(order, strInfo);
}

void CClientDataManagerWorker::_MessageBoxOrderInfo(const Order &order, const std::string& strInfo)
{
	QMessageBox msgBox;
	int nMsgBoxRes = 0;
	COrderInfo* pOrderInfo = NULL;
	
	pOrderInfo = new COrderInfo();
	pOrderInfo->setValue(order);
		
	msgBox.setText(strInfo.c_str());
	msgBox.setInformativeText(pOrderInfo->getInformativeText());
	msgBox.setStandardButtons(QMessageBox::Close);
	msgBox.setDefaultButton(QMessageBox::Close);
	nMsgBoxRes = msgBox.exec();

	if (NULL != pOrderInfo)
	{
		delete pOrderInfo;
		pOrderInfo = NULL;
	}
}

void CClientDataManagerWorker::_UpdateOrderInfo(const Order &order)
{
	CDataUserOrder::getInstance().addAndUpdateData(order);
	_Emit_SignalOrderInfoChanged();
}



void CClientDataManagerWorker::slotNewOrder( CUserOrderInfo* pUserOrderInfo)
{
	//emit
	{
		MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process slotNewOrder"
			<<" "<<"param:"
			<<" "<<"nInstrumentID"<<pUserOrderInfo->m_nInstrumentID
			<<" "<<"nSide="<<pUserOrderInfo->m_nSide
			<<" "<<"nOrderType="<<pUserOrderInfo->m_nOrderType
			<<" "<<"strInstrumentCode="<<pUserOrderInfo->m_strInstrumentCode.toStdString()
			<<" "<<"fPrice="<<pUserOrderInfo->m_fLastPrice
			<<" "<<"quantity="<<pUserOrderInfo->m_nQuantity;
	}


	QMap<unsigned int, Instrument*>::iterator  iterFind;
	std::string strLogInfo;
	Instrument* pInstrumentGet = NULL;
	Account* pAccount = NULL;
	unsigned int nInstrumentID = 0;
	Order::OrderType nOrderType;
	Order::Side nSide;
	int quantity = 0;
	double fPrice = 0;

	nInstrumentID = pUserOrderInfo->m_nInstrumentID;
	
	pInstrumentGet = NULL;
	pInstrumentGet = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pInstrumentGet)
	{
		return;
	}

	pAccount = CDataUserAccount::getInstance().getAccount(0);
	if (NULL == pAccount)
	{
		return;
	}

	nOrderType = pUserOrderInfo->m_nOrderType;
	nSide = pUserOrderInfo->m_nSide;
	quantity = pUserOrderInfo->m_nQuantity;
	fPrice = pUserOrderInfo->m_fLastPrice;

	switch (nOrderType)
	{
	case Order::MARKET:
		if (Order::BUY == nSide)
		{
			m_pSmartTraderClient->buyMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pSmartTraderClient->sellMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		break;
	case Order::MARKET_FAK:
		if (Order::BUY == nSide)
		{
			m_pSmartTraderClient->buyMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pSmartTraderClient->sellMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		break;
	case Order::MARKET_FOK:
		if (Order::BUY == nSide)
		{
			m_pSmartTraderClient->buyMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pSmartTraderClient->sellMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		break;
	case Order::LIMIT:
		if (Order::BUY == nSide)
		{
			m_pSmartTraderClient->buyLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pSmartTraderClient->sellLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		break;
	case Order::LIMIT_FAK:
		if (Order::BUY == nSide)
		{
			m_pSmartTraderClient->buyLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pSmartTraderClient->sellLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		break;
	case Order::LIMIT_FOK:
		if (Order::BUY == nSide)
		{
			m_pSmartTraderClient->buyLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pSmartTraderClient->sellLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		break;
	case Order::STOP:
		if (Order::BUY == nSide)
		{
			m_pSmartTraderClient->buyStop(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pSmartTraderClient->sellStop(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		break;
	case Order::UNKNOWN:
		MYLOG4CPP_ERROR<<"CClientDataManagerWorker::slotNewOrder"<<" Order::UNKNOWN";
		break;
	}//switch (nSide)



}

void CClientDataManagerWorker::onBarDataUpdate( const BarSummary &barData )
{
	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker::onBarDataUpdate"
		<<" "<<"barData.instrumentID="<<barData.instrumentID
		<<" "<<"barData.bars.size="<<barData.bars.size();


	{
		//TODO. historydata test
		CDataUserHistoryBar::getInstance().onBarDataUpdate(barData);
		_Emit_SignalHistoryDataChanged(barData.instrumentID);
		
	}//
}

void CClientDataManagerWorker::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker::onHistoryDataDownloaded"
		<<" "<<"requestID="<<requestID
		<<" "<<"bars->size.size="<<bars->size();

	{
		//TODO. historydata test
		unsigned int nGetInstrumentID = 0;
		CDataUserHistoryBar::getInstance().onHistoryDataDownloaded(requestID, bars, nGetInstrumentID);
		_Emit_SignalHistoryDataChanged(nGetInstrumentID);
	}//

}

void CClientDataManagerWorker::slotInstrumentViewResetData()
{
	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process slotContractInfoWindowResetData";

	Instrument* pInstrumentRef = NULL;
	QMap<unsigned int, Instrument*>::iterator  iterFind;
	unsigned int nUserInstrumentID = 0;

	QStringList strLstUserInstruemt;
	strLstUserInstruemt = CConfigInfo::getInstance().getLstUserInstrument();


	{
		//check in total list
		foreach (const QString& strUserInstrumentID, strLstUserInstruemt)
		{
			nUserInstrumentID = 0;
			nUserInstrumentID = strUserInstrumentID.toUInt();

			pInstrumentRef = NULL;
			pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nUserInstrumentID);

			if (NULL == pInstrumentRef)
			{
				pInstrumentRef = NULL;
			}
			else
			{
				/*	
				instrument have add to CDataUserInstrument
				remove from CDataInstrument
				*/				
				CDataInstrument::getInstance().removeByData(pInstrumentRef);
			}//if

		}//foreach
	}

	{		
		_Emit_SignalContractInfoChanged();
	}
}




void CClientDataManagerWorker::_Emit_SignalUserInstrumentInfoChanged()
{

	CItemUserInstrumentInfo* pItemUserInstrumentInfo = NULL;
	pItemUserInstrumentInfo = CDataUserInstrument::getInstance().getRootHandle();
	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"_Emit_SignalUserInstrumentInfoChanged()"
		<<" "<<"emit"
		<<" "<<"signalUserInstrumentInfoChanged(CItemUserInstrumentInfo*)"
		<<" "<<"param:"
		<<" "<<"pItemUserInstrumentInfo=0x"<<pItemUserInstrumentInfo;

	CSignalSlotManager::getInstance().emit_signalUserInstrumentInfoChanged(pItemUserInstrumentInfo);
	
}
void CClientDataManagerWorker::_Emit_SignalOrderInfoChanged()
{
	CTreeItemOrder* pTreeItemOrder = NULL;
	pTreeItemOrder = CDataUserOrder::getInstance().getRootHandle();
	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"_Emit_SignalOrderInfoChanged()"
		<<" "<<"emit"
		<<" "<<"signalOrderInfoChanged(CTreeItemOrder*)"
		<<" "<<"param:"
		<<" "<<"pTreeItemOrder=0x"<<pTreeItemOrder;

	CSignalSlotManager::getInstance().emit_signalOrderInfoChanged(pTreeItemOrder);
}



void CClientDataManagerWorker::_Emit_SignalContractInfoChanged()
{
	CItemInstrumentInfo* pTreeItemContract_Root = NULL;
	pTreeItemContract_Root = CDataInstrument::getInstance().getRootHandle();

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"_Emit_SignalContractInfoChanged()"
		<<" "<<"emit"
		<<" "<<"signalContractInfoChanged(CTreeItemContract*)"
		<<" "<<"param:"
		<<" "<<"pTreeItemContract_Root=0x"<<pTreeItemContract_Root;
	
	CSignalSlotManager::getInstance().emit_signalInstrumentInfoChanged(pTreeItemContract_Root);
}

void CClientDataManagerWorker::_Emit_SignalHistoryDataChanged(unsigned int nInstrumentID)
{
	CHistoryDataManager* pHistoryDataManager = NULL;
	pHistoryDataManager = CDataUserHistoryBar::getInstance().findByID(nInstrumentID);

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"_Emit_SignalHistoryDataChanged()"
		<<" "<<"emit"
		<<" "<<"signalHistoryDataChanged()"
		<<" "<<"param:"
		<<" "<<"pHistoryDataManager=0x"<<pHistoryDataManager;
	CSignalSlotManager::getInstance().emit_signalHistoryDataChanged(pHistoryDataManager);
}//

void CClientDataManagerWorker::setCurrentInstrument( unsigned int nInstrumentID )
{
	CDataUserHistoryBar::getInstance().createRequest(nInstrumentID, m_pSmartTraderClient);
}
