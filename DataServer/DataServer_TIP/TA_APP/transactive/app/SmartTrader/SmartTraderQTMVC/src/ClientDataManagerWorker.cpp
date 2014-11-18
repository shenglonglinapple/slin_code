#include "ClientDataManagerWorker.h"

#include <QtCore/QStringList>
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


CClientDataManagerWorker::CClientDataManagerWorker(void)
{	
	m_pClientLoginParam = NULL;
	m_pMyTradeClient = NULL;
	m_pTreeItemContract_Root = NULL;
	m_pContractInfo = NULL;
	m_pQuotesInfo = NULL;
	m_pTreeItemQuotes_Root = NULL;
	m_pUtilityFun = NULL;
	m_pProjectLogHelper = NULL;
	m_pOrderInfo = NULL;
	m_pTreeItemOrder_root = NULL;

	m_pUtilityFun = new CProjectUtilityFun();
	m_pProjectLogHelper = new CProjectLogHelper();

	_InitMVCDataForContract();
	_InitMVCDataForQuotes();
	_InitMVCDataForOrder();

	
	CDataTotalInstrument::getInstance();

	


	{
		QMutexLocker lock(&m_mutexForMapAccount);
		m_MapAccount.clear();
	}

	{
		QMutexLocker lock(&m_mutexForMapOrder);
		m_MapOrder.clear();
	}


	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		m_MapHistoryData.clear();
		m_nDoTest = 0;
	}

	

}

CClientDataManagerWorker::~CClientDataManagerWorker(void)
{	
	_UnInitLoginParam();

	if (NULL !=  m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}

	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
	}

	CDataTotalInstrument::removeInstance();

	{
		QMutexLocker lock(&m_mutexForMapAccount);
		m_MapAccount.clear();
	}

	{
		QMutexLocker lock(&m_mutexForMapOrder);
		m_MapOrder.clear();
	}

	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		QMap<unsigned int, CHistoryDataManager*>::Iterator iterMap;
		CHistoryDataManager* pDataRef = NULL;
		iterMap = m_MapHistoryData.begin();
		while (iterMap != m_MapHistoryData.end())
		{
			pDataRef = iterMap.value();

			delete pDataRef;
			pDataRef = NULL;

			iterMap++;
		}
		m_MapHistoryData.clear();
	}


}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CClientDataManagerWorker::_UnInitLoginParam()
{
	if (NULL != m_pClientLoginParam)
	{
		delete m_pClientLoginParam;
		m_pClientLoginParam = NULL;
	}

}


void CClientDataManagerWorker::_InitMVCDataForContract()
{
	{
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		if (NULL != m_pTreeItemContract_Root)
		{
			delete m_pTreeItemContract_Root;
			m_pTreeItemContract_Root = NULL;
		}

		QList<QVariant> dataColumn;
		QString strMapKey;
		dataColumn.clear();
		dataColumn.push_back("DataType_Root");
		m_pTreeItemContract_Root = new CTreeItemContract(dataColumn, NULL);
		m_pTreeItemContract_Root->setDataType(CTreeItemContract::DataTypeContract_Root);
		m_pTreeItemContract_Root->setInstrumentID(0);
		m_pContractInfo = new CContractInfo();
	}




}
void CClientDataManagerWorker::_UnInitMVCDataForContract()
{
	QMutexLocker lock(&m_mutexForNodeRootContract);	

	if (NULL != m_pTreeItemContract_Root)
	{
		delete m_pTreeItemContract_Root;
		m_pTreeItemContract_Root = NULL;
	}

	if (NULL != m_pContractInfo)
	{
		delete m_pContractInfo;
		m_pContractInfo = NULL;
	}

}



void CClientDataManagerWorker::_InitMVCDataForQuotes()
{
	QMutexLocker lock(&m_mutexForNodeRootQuotes);	
	if (NULL != m_pTreeItemQuotes_Root)
	{
		delete m_pTreeItemQuotes_Root;
		m_pTreeItemQuotes_Root = NULL;
	}

	//root node save all column Names
	QList<QVariant> dataTreeItem;
	CTreeItemQuotes::getLstClumnName(dataTreeItem);
	m_pTreeItemQuotes_Root = new CTreeItemQuotes(dataTreeItem, NULL);
	m_pTreeItemQuotes_Root->setDataType(CTreeItemQuotes::ItemDataType_ROOT);
	m_pTreeItemQuotes_Root->rootNodeRetColumnsName();

	m_pQuotesInfo = new CQuotesInfo();

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
		<<" "<<"m_pNodeRootQuotes=ox"<<m_pTreeItemQuotes_Root;

	emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);

}
void CClientDataManagerWorker::_UnInitMVCDataForQuotes()
{
	QMutexLocker lock(&m_mutexForNodeRootQuotes);	

	if (NULL != m_pTreeItemQuotes_Root)
	{
		delete m_pTreeItemQuotes_Root;
		m_pTreeItemQuotes_Root = NULL;
	}

	if (NULL != m_pQuotesInfo)
	{
		delete m_pQuotesInfo;
		m_pQuotesInfo = NULL;
	}

}



void CClientDataManagerWorker::_InitMVCDataForOrder()
{
	QMutexLocker lock(&m_mutexForMapOrder);	
	if (NULL != m_pTreeItemOrder_root)
	{
		delete m_pTreeItemOrder_root;
		m_pTreeItemOrder_root = NULL;
	}

	//root node save all column Names
	QList<QVariant> dataTreeItem;
	CTreeItemOrder::getLstClumnName(dataTreeItem);
	m_pTreeItemOrder_root = new CTreeItemOrder(dataTreeItem, NULL);
	m_pTreeItemOrder_root->setDataType(CTreeItemOrder::ItemDataType_ROOT);
	m_pTreeItemOrder_root->rootNodeSetColumnsName();

	m_pOrderInfo = new COrderInfo();

	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"fun:"<<"_UpdateOrderInfo()"
			<<" "<<"emit"
			<<" "<<"signalOrderInfoChanged()"
			<<" "<<"param:"
			<<" "<<"m_pTreeItemOrder_root=0x"<<m_pTreeItemOrder_root;

		emit signalOrderInfoChanged(m_pTreeItemOrder_root);
	}


}
void CClientDataManagerWorker::_UnInitMVCDataForOrder()
{
	QMutexLocker lock(&m_mutexForMapOrder);	

	if (NULL != m_pTreeItemOrder_root)
	{
		delete m_pTreeItemOrder_root;
		m_pTreeItemOrder_root = NULL;
	}

	if (NULL != m_pOrderInfo)
	{
		delete m_pOrderInfo;
		m_pOrderInfo = NULL;
	}

}

void CClientDataManagerWorker::onInstrumentDownloaded( const Instrument& instrument )
{
	Instrument* pGetInstrument = NULL;
	unsigned int nGetInstrumentID = 0;
	std::string strLogInfo;

	nGetInstrumentID = instrument.getInstrumentID();
	pGetInstrument = instrument.getInstrument(nGetInstrumentID);
	
	CDataTotalInstrument::getInstance().onInstrumentDownloaded(instrument);

	{
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		m_pContractInfo->setValue(instrument);
		m_pTreeItemContract_Root->appendThreeChild(m_pContractInfo);
		//use slotContractInfoWindowResetData()
	}


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

	Instrument* pInstrumentGet = NULL;
	QMap<unsigned int, Instrument*>::iterator  iterFind;
	std::string strLogInfo;

	CDataTotalInstrument::getInstance().onMarketDataUpdate(instrument);


	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);	
		m_pQuotesInfo->setValue(*pInstrumentGet);
		m_pTreeItemQuotes_Root->resetChildrenData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
		MYLOG4CPP_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
			<<" "<<"m_pNodeRootQuotes=ox"<<m_pTreeItemQuotes_Root;
		emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);
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

		m_pQuotesInfo->setValue(*pInstrumentRef);
	}

	{
		//remove later
		//remove nInstrumentID from m_pTreeItemContract_Root
		//class: CQuotesTableView signals:	void signalContractInfoWindowResetData();
		//CClientDataManagerWorker::slotContractInfoWindowResetData()
	}


	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);	

		strExchangeName = m_pQuotesInfo->m_strExchangeName.toStdString();
		strUnderlyingCode = m_pQuotesInfo->m_strUnderlyingCode.toStdString();
		strInstrumentCode = m_pQuotesInfo->m_strInstrumentCode.toStdString();
		MYLOG4CPP_DEBUG<<"slotAddContractToSmartQuotes add contract to SmartQuotes"
			<<" "<<"InstrumentID="<<nInstrumentID
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;

		m_pTreeItemQuotes_Root->appendChildByData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
		MYLOG4CPP_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
			<<" "<<"m_pTreeItemQuotes_Root=ox"<<m_pTreeItemQuotes_Root;
		emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);
	}
	

	{
		//TODO. TTTTTTTTTTT historydata test
		QMutexLocker lock(&m_mutexForMapHistoryData);
		if (0 == m_nDoTest)
		{
			//time_t timeNow = m_pUtilityFun->strToDateTime("2014-08-23 20:06:09");
			//m_nDoTest = 1;
			CHistoryDataManager* pHistoryDataManager = NULL;
			pHistoryDataManager = new CHistoryDataManager();

			pHistoryDataManager->m_nInstrumentID = nInstrumentID;
			pHistoryDataManager->m_pHistoryRequest->setRequestType(CHistoryDataRequest::HistoryRequestType_NumberSubscribe);
			pHistoryDataManager->m_pHistoryRequest->setInstrumentHandle(pInstrumentRef);
			pHistoryDataManager->m_pHistoryRequest->setBarType(FIVE_SECOND);
			pHistoryDataManager->m_pHistoryRequest->setTimeFrom(m_pUtilityFun->getTimeNow_Qt() - 60 * 60 * 24 * 10);
			pHistoryDataManager->m_pHistoryRequest->setBarCount(6000);
			pHistoryDataManager->m_pHistoryRequest->setSubscribe(true);
			pHistoryDataManager->m_pHistoryRequest->sentRequest(m_pMyTradeClient);
			pHistoryDataManager->m_pHistoryRequest->logInfo();

			m_MapHistoryData.insert(pHistoryDataManager->m_nInstrumentID, pHistoryDataManager);
			pHistoryDataManager = NULL;

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

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process singalRemoveContractFromSmartQuotes"
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

		m_pContractInfo->setValue(*pInstrumentRef);
		m_pQuotesInfo->setValue(*pInstrumentRef);		
	}


	//remove
	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);
		MYLOG4CPP_DEBUG<<"slotRemoveContractFromSmartQuotes remove hot Quotes"
			<<" "<<"InstrumentID="<<nInstrumentID
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;

		m_pTreeItemQuotes_Root->removeChildByData(m_pQuotesInfo);

		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"emit"
			<<" "<<"signalQuotesInfoChanged(CTreeItemQuotes*)"
			<<" "<<"param:"
			<<" "<<"m_pTreeItemQuotes_Root=0x"<<m_pTreeItemQuotes_Root;
		emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);
	}
		

	//add
	{		
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		MYLOG4CPP_DEBUG<<"slotRemoveContractFromSmartQuotes add contract to ContratInfo"
			<<" "<<"InstrumentID="<<nInstrumentID
			<<" "<<"ExchangeName="<<m_pContractInfo->getExchangeName().toStdString()
			<<" "<<"strInstrumentCode="<<m_pContractInfo->getInstrumentCode().toStdString();

		m_pTreeItemContract_Root->appendThreeChild(m_pContractInfo);

		MYLOG4CPP_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
			<<" "<<"m_pNodeRootContract=0x"<<m_pTreeItemContract_Root;

		emit signalContractInfoChanged(m_pTreeItemContract_Root);
	}


	

}


void CClientDataManagerWorker::_UnInitTraderClient()
{
	if (NULL != m_pMyTradeClient)
	{
		m_pMyTradeClient->logoff();
		m_pMyTradeClient->setProcessRecvDataHandle(NULL);

		delete m_pMyTradeClient;
		m_pMyTradeClient = NULL;
	}
}


void CClientDataManagerWorker::slotClientLoginParamChanged( CClientLoginParam* pClientLoginParam )
{
	int nloginToServerRes = 0;

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker process signalClientLoginParamChanged"
		<<" "<<"pClientLoginParam=0x"<<pClientLoginParam;

	_UnInitLoginParam();
	m_pClientLoginParam = new CClientLoginParam();
	m_pClientLoginParam->setDefaultValue();
	*m_pClientLoginParam = *pClientLoginParam;

	_UnInitTraderClient();
	m_pMyTradeClient = new CSmartTraderClient(*m_pClientLoginParam);
	m_pMyTradeClient->setProcessRecvDataHandle(this);
	nloginToServerRes = m_pMyTradeClient->loginToServer();

	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker emit signalLoginToServerResult"
		<<" "<<"nlogonToServerRes="<<nloginToServerRes;

	emit signalLoginToServerResult(nloginToServerRes);

}

void CClientDataManagerWorker::_Test()
{
	_UnInitLoginParam();
	m_pClientLoginParam = new CClientLoginParam();
	m_pClientLoginParam->setDefaultValue();

	emit signalLoginToServerResult(0);



	Instrument* pGetInstrument = NULL;
	unsigned int nGetInstrumentID = 0;
	std::string strLogInfo;

	
	CDataTotalInstrument::getInstance()._Test();
	

	{
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		m_pContractInfo->setDefaultValue();
		m_pTreeItemContract_Root->appendThreeChild(m_pContractInfo);

		MYLOG4CPP_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
			<<" "<<"m_pNodeRootContract=0x"<<m_pTreeItemContract_Root;

		emit signalContractInfoChanged(m_pTreeItemContract_Root);
	}


	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);
		m_pQuotesInfo->setDefaultValue();
		m_pTreeItemQuotes_Root->appendChildByData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
		MYLOG4CPP_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
			<<" "<<"m_pNodeRootQuotes=ox"<<m_pTreeItemQuotes_Root;
		emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);
	}



}



void CClientDataManagerWorker::slotQuotesTableViewColumnsChanged()
{

	MYLOG4CPP_DEBUG<<" "<<"slot"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"slot"
		<<" "<<"slotQuotesTableViewColumnsChanged";

	//subscribeMarketData user hot Instrument
	QStringList lstUserInstrument;
	Instrument* pInstrumentRef = NULL;
	unsigned int nInstrumentID = 0;
	QMap<unsigned int, Instrument*>::iterator  iterFind;

	lstUserInstrument = CConfigInfo::getInstance().getLstUserInstrument();
	
	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);
		//delete old data
		if (NULL != m_pTreeItemQuotes_Root)
		{
			delete m_pTreeItemQuotes_Root;
			m_pTreeItemQuotes_Root = NULL;
		}
		//new root data
		QList<QVariant> dataTreeItem;
		CTreeItemQuotes::getLstClumnName(dataTreeItem);
		m_pTreeItemQuotes_Root = new CTreeItemQuotes(dataTreeItem, NULL);
		m_pTreeItemQuotes_Root->setDataType(CTreeItemQuotes::ItemDataType_ROOT);
	}

	{
		QMutexLocker lock_m_mutexForNodeRootQuotes(&m_mutexForNodeRootQuotes);
		
		//reset child data
		foreach (const QString& strInstrument, lstUserInstrument)
		{
			nInstrumentID = strInstrument.toUInt();
			pInstrumentRef = NULL;
			pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
			if (NULL != pInstrumentRef)
			{
				m_pQuotesInfo->setValue(*pInstrumentRef);
				m_pTreeItemQuotes_Root->appendChildByData(m_pQuotesInfo);
			}//if
		}//foreach

		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"emit"
			<<" "<<"signalQuotesInfoChanged(CTreeItemQuotes*)"
			<<" "<<"param:"
			<<" "<<"m_pNodeRootQuotes=0x"<<m_pTreeItemQuotes_Root;

		emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);
	}

	return;
}

void CClientDataManagerWorker::onAccountDownloaded( Account& account )
{
	{
		QMutexLocker lock(&m_mutexForMapAccount);
		m_MapAccount.insert(account.getAccountID(), &account);
	}
}


void CClientDataManagerWorker::onOrderAccepted(const Order &order)
{
	_UpdateOrderInfo(order);


}
void CClientDataManagerWorker::onOrderCanceled(const Order &order)
{

	_UpdateOrderInfo(order);


}
void CClientDataManagerWorker::onOrderRejected(const Order &order)
{
	_UpdateOrderInfo(order);


}
void CClientDataManagerWorker::onOrderFilled(const Order &order)
{
	_UpdateOrderInfo(order);


}
void CClientDataManagerWorker::onCancelReject(const Order &order)
{
	_UpdateOrderInfo(order);
	
}
void CClientDataManagerWorker::_UpdateOrderInfo(const Order &order)
{
	QMap<unsigned int, Order*>::iterator iterMap;
	Order* pOrder = NULL;

	{
		QMutexLocker lock(&m_mutexForMapOrder);

		m_pOrderInfo->setValue(order);

		if (m_MapOrder.contains(order.getOrderID()))
		{
			iterMap = m_MapOrder.find(order.getOrderID());
			pOrder = iterMap.value();
			*pOrder = order;
			m_pTreeItemOrder_root->resetChildrenData(m_pOrderInfo);
		}
		else
		{
			pOrder = (Order*)&order;
			m_MapOrder.insert(order.getOrderID(), pOrder);
			m_pTreeItemOrder_root->appendChildByData(m_pOrderInfo);
		}
	}


	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"fun:"<<"_UpdateOrderInfo()"
			<<" "<<"emit"
			<<" "<<"signalOrderInfoChanged()"
			<<" "<<"param:"
			<<" "<<"m_pTreeItemOrder_root=0x"<<m_pTreeItemOrder_root;

		emit signalOrderInfoChanged(m_pTreeItemOrder_root);
	}
}

unsigned int CClientDataManagerWorker::_GetInstrumentIDByInstruemntCode(const QString& strInstrumentCode)
{
	unsigned int nInstruemntID = -1;

	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);	
		nInstruemntID = m_pTreeItemQuotes_Root->getHotInstrumentIDByCode(strInstrumentCode);
		MYLOG4CPP_DEBUG<<"strInstrumentCode="<<strInstrumentCode.toStdString()
			<<" "<<"getHotInstrumentIDByCode"
			<<" "<<"nInstruemntID="<<nInstruemntID;
	}

	return nInstruemntID;
}

void CClientDataManagerWorker::slotNewOrder( CUserOrderInfo* pUserOrderInfo)
{
	//emit
	{
		MYLOG4CPP_DEBUG<<" "<<"slot"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"fun:"<<"slotNewOrder()"
			<<" "<<"slot"
			<<" "<<"slotNewOrder()"
			<<" "<<"param:"
			<<" "<<"nInstrumentID"<<pUserOrderInfo->m_nInstrumentID
			<<" "<<"nSide="<<pUserOrderInfo->m_nSide
			<<" "<<"nOrderType="<<pUserOrderInfo->m_nOrderType
			<<" "<<"strInstrumentCode="<<pUserOrderInfo->m_strInstrumentCode.toStdString().c_str()
			<<" "<<"fPrice="<<pUserOrderInfo->m_fLastPrice
			<<" "<<"quantity="<<pUserOrderInfo->m_nQuantity;
	}


	QMap<unsigned int, Instrument*>::iterator  iterFind;
	std::string strLogInfo;
	Instrument* pInstrumentGet = NULL;
	Account* pAccount = NULL;
	unsigned int nInstrumentID = 0;
	//nInstrumentID = _GetInstrumentIDByInstruemntCode(strInstrumentCode);//"IF1402"
	nInstrumentID = pUserOrderInfo->m_nInstrumentID;

	
	pInstrumentGet = NULL;
	pInstrumentGet = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pInstrumentGet)
	{
		return;
	}
	//find ok


	{
		QMutexLocker lock(&m_mutexForMapAccount);
		if (m_MapAccount.isEmpty())
		{
			MYLOG4CPP_ERROR<<" "<<"m_MapAccount is empty";
			return;
		}
		pAccount = m_MapAccount.begin().value();
	}

	Order::OrderType nOrderType = pUserOrderInfo->m_nOrderType;
	Order::Side nSide = pUserOrderInfo->m_nSide;
	int quantity = pUserOrderInfo->m_nQuantity;
	double fPrice = pUserOrderInfo->m_fLastPrice;

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

	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;

	{
		//TODO. historydata test
		QMutexLocker lock(&m_mutexForMapHistoryData);

		if (!m_MapHistoryData.contains(barData.instrumentID))
		{
			//find error
			MYLOG4CPP_ERROR<<" "<<"find error instrumentID="<<barData.instrumentID;
			return;
		}
		iterMap = m_MapHistoryData.find(barData.instrumentID);

		pHistoryDataManager = iterMap.value();
		pHistoryDataManager->m_pHistoryACK->onBarDataUpdate(barData);
		pHistoryDataManager->m_pHistoryACK->logInfo();


		{
			MYLOG4CPP_DEBUG<<" "<<"emit"
				<<" "<<"class:"<<"CClientDataManagerWorker"
				<<" "<<"fun:"<<"onBarDataUpdate()"
				<<" "<<"emit"
				<<" "<<"signalHistoryDataChanged()"
				<<" "<<"param:"
				<<" "<<"pHistoryDataManager=0x"<<pHistoryDataManager;

			emit signalHistoryDataChanged(pHistoryDataManager);
		}

	}//scoped_lock
}

void CClientDataManagerWorker::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	MYLOG4CPP_DEBUG<<"CClientDataManagerWorker::onHistoryDataDownloaded"
		<<" "<<"requestID="<<requestID
		<<" "<<"bars->size.size="<<bars->size();

	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;

	{
		//TODO. historydata test
		QMutexLocker lock(&m_mutexForMapHistoryData);
		iterMap = m_MapHistoryData.begin();
		while (iterMap != m_MapHistoryData.end())
		{
			pHistoryDataManager = iterMap.value();
			if (pHistoryDataManager->m_pHistoryRequest->m_nRequestID == requestID)
			{
				break;
			}
			pHistoryDataManager = NULL;

			iterMap++;
		}

		if (iterMap == m_MapHistoryData.end())
		{
			//find error
			//TODO.
			MYLOG4CPP_ERROR<<" "<<"not find requestID="<<requestID;
			return;
		}

		pHistoryDataManager = iterMap.value();
		pHistoryDataManager->m_pHistoryACK->onHistoryDataDownloaded(bars);
		pHistoryDataManager->m_pHistoryACK->logInfo();


		{
			MYLOG4CPP_DEBUG<<" "<<"emit"
				<<" "<<"class:"<<"CClientDataManagerWorker"
				<<" "<<"fun:"<<"onHistoryDataDownloaded()"
				<<" "<<"emit"
				<<" "<<"signalHistoryDataChanged()"
				<<" "<<"param:"
				<<" "<<"pHistoryDataManager=0x"<<pHistoryDataManager;

			emit signalHistoryDataChanged(pHistoryDataManager);
		}

	}//scoped_lock

}

void CClientDataManagerWorker::slotContractInfoWindowResetData()
{

	MYLOG4CPP_DEBUG<<" "<<"slot"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"fun:"<<"slotContractInfoWindowResetData";


	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
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
				m_pContractInfo->setValue(*pInstrumentRef);
				strExchangeName = m_pContractInfo->getExchangeName().toStdString();
				strUnderlyingCode = m_pContractInfo->getUnderlyingCode().toStdString();
				strInstrumentCode = m_pContractInfo->getInstrumentCode().toStdString();
				MYLOG4CPP_DEBUG<<"ContractInfo Window Reset Data"
					<<" "<<"InstrumentID="<<m_pContractInfo->getInstrumentID()
					<<" "<<"ExchangeName="<<strExchangeName
					<<" "<<"strInstrumentCode="<<strInstrumentCode;

				//remove nInstrumentID from m_pTreeItemContract_Root
				QMutexLocker lock(&m_mutexForNodeRootContract);	
				m_pTreeItemContract_Root->removeChildrenByData(m_pContractInfo);
			}//if

		}//foreach
	}

	{
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		MYLOG4CPP_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
			<<" "<<"m_pTreeItemContract_Root=0x"<<m_pTreeItemContract_Root;
		emit signalContractInfoChanged(m_pTreeItemContract_Root);
	}
}


//QT_END_NAMESPACE


