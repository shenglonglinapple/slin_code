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

#include "ContractInfo.h"
#include "TreeItemContract.h"

#include "QuotesInfo.h"
#include "TreeItemQuotes.h"

#include "OrderInfo.h"
#include "UserOrderInfo.h"
#include "TreeItemOrder.h"

#include "HistoryDataManager.h"
#include "Log4cppLogger.h"

#include "DataTotalInstrument.h"
#include "DataContract.h"
#include "DataUserContract.h"
#include "DataUserAccount.h"
#include "DataUserOrder.h"
#include "DataUserHistoryBar.h"


CClientDataManagerWorker::CClientDataManagerWorker(void)
{	
	m_pClientLoginParam = NULL;
	m_pMyTradeClient = NULL;

	CDataContract::getInstance();
	_SignaleDataChange_DataContract();
	
	CDataUserContract::getInstance();
	_SignaleDataChange_DataUserContract();
	
	CDataUserOrder::getInstance();
	_SignaleDataChange_DataUserOrder();
	
	
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
	CDataUserContract::removeInstance();
	CDataContract::removeInstance();

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
	CDataContract::getInstance().onInstrumentDownloaded(instrument);

	{
		//subscribeMarketData user hot Instrument
		QStringList LstUserInstrument;
		QString strUserInstruemt = QString("%1").arg(nGetInstrumentID);
		LstUserInstrument = CConfigInfo::getInstance().getLstUserInstrument();
		if (LstUserInstrument.contains(strUserInstruemt))
		{
			slotAddContractToSmartQuotes(nGetInstrumentID);
		}
	
	}
}


void CClientDataManagerWorker::onMarketDataUpdate(const Instrument& instrument)
{
	CDataTotalInstrument::getInstance().onMarketDataUpdate(instrument);

	
	{
		CDataUserContract::getInstance().onMarketDataUpdate(instrument);
		_SignaleDataChange_DataUserContract();
	}



}

void CClientDataManagerWorker::slotAddContractToSmartQuotes( unsigned int nInstrumentID )
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
		QStringList strLstUserInstruemt;
		strLstUserInstruemt = CConfigInfo::getInstance().getLstUserInstrument();
		if (!strLstUserInstruemt.contains(QVariant(nInstrumentID).toString()))
		{
			strLstUserInstruemt.push_back(QVariant(nInstrumentID).toString());
			CConfigInfo::getInstance().setLstUserInstrument(strLstUserInstruemt);
		}

		//subscribe this instrument
		MYLOG4CPP_DEBUG<<"subscribeMarketData"<<" "<<"InstrumentID="<<nInstrumentID;
		m_pMyTradeClient->subscribeMarketData(nInstrumentID);//subscribe this Instrument market data

	}

	{
		//remove later
		//remove nInstrumentID from m_pTreeItemContract_Root
		//class: CQuotesTableView signals:	void signalContractInfoWindowResetData();
		//CClientDataManagerWorker::slotContractInfoWindowResetData()
	}


	{
		CDataUserContract::getInstance().addByData(pInstrumentRef);
		_SignaleDataChange_DataUserContract();
	}
	

	{
		//TODO. TTTTTTTTTTT historydata test
		if (0 == m_nDoTest)
		{
			//time_t timeNow = m_pUtilityFun->strToDateTime("2014-08-23 20:06:09");
			m_nDoTest = 1;
			CDataUserHistoryBar::getInstance().createRequest(nInstrumentID, m_pMyTradeClient);
		}
	}
	
}

void CClientDataManagerWorker::slotRemoveContractFromSmartQuotes( unsigned int nInstrumentID )
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
		m_pMyTradeClient->unsubscribeMarketData(pInstrumentRef->getInstrumentID());

	}


	//remove
	{
		CDataUserContract::getInstance().removeByData(pInstrumentRef);
		_SignaleDataChange_DataUserContract();
	}
		

	//add
	{
		CDataContract::getInstance().addByData(pInstrumentRef);
		_SignaleDataChange_DataContract();
	}


	

}


void CClientDataManagerWorker::_InitTraderClient()
{
	m_pMyTradeClient = new CSmartTraderClient(*m_pClientLoginParam);
	m_pMyTradeClient->setProcessRecvDataHandle(this);
}
void CClientDataManagerWorker::_UnInitTraderClient()
{
	if (NULL != m_pMyTradeClient)
	{
		//TODO. debug mode will crash
		//m_pMyTradeClient->logoff();
		m_pMyTradeClient->setProcessRecvDataHandle(NULL);

		delete m_pMyTradeClient;
		m_pMyTradeClient = NULL;
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
	nloginToServerRes = m_pMyTradeClient->loginToServer();

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
	
	CDataContract::getInstance()._Test();
	_SignaleDataChange_DataContract();


	CDataUserContract::getInstance()._Test();
	_SignaleDataChange_DataUserContract();

}



void CClientDataManagerWorker::slotQuotesTableViewColumnsChanged()
{
	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process slotQuotesTableViewColumnsChanged";

	//subscribeMarketData user hot Instrument
	QStringList lstUserInstrument;
	Instrument* pInstrumentRef = NULL;
	unsigned int nInstrumentID = 0;
	QMap<unsigned int, Instrument*>::iterator  iterFind;

	lstUserInstrument = CConfigInfo::getInstance().getLstUserInstrument();
	
	{
		CDataUserContract::removeInstance();
		CDataUserContract::getInstance();
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
				CDataUserContract::getInstance().addByData(pInstrumentRef);
			}//if
		}//foreach

		_SignaleDataChange_DataUserContract();
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
	_SignaleDataChange_DataUserOrder();
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
			m_pMyTradeClient->buyMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pMyTradeClient->sellMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		break;
	case Order::MARKET_FAK:
		if (Order::BUY == nSide)
		{
			m_pMyTradeClient->buyMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pMyTradeClient->sellMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		break;
	case Order::MARKET_FOK:
		if (Order::BUY == nSide)
		{
			m_pMyTradeClient->buyMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pMyTradeClient->sellMarket(*pAccount, *pInstrumentGet, quantity, 0, 0);
		}
		break;
	case Order::LIMIT:
		if (Order::BUY == nSide)
		{
			m_pMyTradeClient->buyLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pMyTradeClient->sellLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		break;
	case Order::LIMIT_FAK:
		if (Order::BUY == nSide)
		{
			m_pMyTradeClient->buyLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pMyTradeClient->sellLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		break;
	case Order::LIMIT_FOK:
		if (Order::BUY == nSide)
		{
			m_pMyTradeClient->buyLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pMyTradeClient->sellLimit(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		break;
	case Order::STOP:
		if (Order::BUY == nSide)
		{
			m_pMyTradeClient->buyStop(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
		}
		else if (Order::SELL == nSide)
		{
			m_pMyTradeClient->sellStop(*pAccount, *pInstrumentGet, fPrice, quantity, 0, 0);
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
		CHistoryDataManager* pHistoryDataManager = NULL;

		pHistoryDataManager = CDataUserHistoryBar::getInstance().findByID(barData.instrumentID);

		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"fun:"<<"onBarDataUpdate()"
			<<" "<<"emit"
			<<" "<<"signalHistoryDataChanged()"
			<<" "<<"param:"
			<<" "<<"pHistoryDataManager=0x"<<pHistoryDataManager;
        emit signalHistoryDataChanged(pHistoryDataManager);
	}//
}

void CClientDataManagerWorker::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker::onHistoryDataDownloaded"
		<<" "<<"requestID="<<requestID
		<<" "<<"bars->size.size="<<bars->size();

	{
		//TODO. historydata test
		CDataUserHistoryBar::getInstance().onHistoryDataDownloaded(requestID, bars);
		CHistoryDataManager* pHistoryDataManager = NULL;
		pHistoryDataManager = CDataUserHistoryBar::getInstance().findByID(requestID);

		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"fun:"<<"onHistoryDataDownloaded()"
			<<" "<<"emit"
			<<" "<<"signalHistoryDataChanged()"
			<<" "<<"param:"
			<<" "<<"pHistoryDataManager"<<pHistoryDataManager;

		emit signalHistoryDataChanged(pHistoryDataManager);

	}//

}

void CClientDataManagerWorker::slotContractInfoWindowResetData()
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
				//find ok
				CDataContract::getInstance().removeByData(pInstrumentRef);
			}//if

		}//foreach
	}

	{		
		_SignaleDataChange_DataContract();
	}
}




void CClientDataManagerWorker::_SignaleDataChange_DataUserContract()
{

	CTreeItemQuotes* pTreeItemQuotes = NULL;
	pTreeItemQuotes = CDataUserContract::getInstance().getRootHandle();
	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"_SignaleDataChange_DataUserContract()"
		<<" "<<"emit"
		<<" "<<"signalQuotesInfoChanged(CTreeItemQuotes*)"
		<<" "<<"param:"
		<<" "<<"pTreeItemQuotes=0x"<<pTreeItemQuotes;
	emit signalQuotesInfoChanged(pTreeItemQuotes);

	return;
}
void CClientDataManagerWorker::_SignaleDataChange_DataUserOrder()
{
	CDataUserOrder::getInstance();
	CTreeItemOrder* pTreeItemOrder = NULL;
	pTreeItemOrder = CDataUserOrder::getInstance().getRootHandle();
	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"_SignaleDataChange_DataUserOrder()"
		<<" "<<"emit"
		<<" "<<"signalOrderInfoChanged(CTreeItemOrder*)"
		<<" "<<"param:"
		<<" "<<"pTreeItemOrder=0x"<<pTreeItemOrder;

	emit signalOrderInfoChanged(pTreeItemOrder);
}



void CClientDataManagerWorker::_SignaleDataChange_DataContract()
{
	CTreeItemContract* pTreeItemContract_Root = NULL;
	pTreeItemContract_Root = CDataContract::getInstance().getRootHandle();

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"_SignaleDataChange_DataContract()"
		<<" "<<"emit"
		<<" "<<"signalContractInfoChanged(CTreeItemContract*)"
		<<" "<<"param:"
		<<" "<<"pTreeItemContract_Root=0x"<<pTreeItemContract_Root;
	emit signalContractInfoChanged(pTreeItemContract_Root);
}


