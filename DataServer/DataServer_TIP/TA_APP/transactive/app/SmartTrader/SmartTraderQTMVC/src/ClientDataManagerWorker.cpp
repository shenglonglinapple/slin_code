#include "ClientDataManagerWorker.h"

#include <QtCore/QStringList>
#include "Bar.h"

#include "ClientLoginParam.h"
#include "SmartTraderClient.h"
#include "ProjectUtilityFun.h"
#include "ConfigInfo.h"

#include "ContractInfo.h"
#include "TreeItemContract.h"

#include "QuotesInfo.h"
#include "TreeItemQuotes.h"

#include "OrderInfo.h"
#include "UserOrderInfo.h"
#include "TreeItemOrder.h"

#include "HistoryDataManager.h"



#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CClientDataManagerWorker::CClientDataManagerWorker(void)
{	
	m_pClientLoginParam = NULL;
	m_pMyTradeClient = NULL;
	m_pTreeItemContract_Root = NULL;
	m_pContractInfo = NULL;
	m_pQuotesInfo = NULL;
	m_pTreeItemQuotes_Root = NULL;
	m_pUtilityFun = NULL;
	m_pOrderInfo = NULL;
	m_pTreeItemOrder_root = NULL;

	m_pUtilityFun = new CProjectUtilityFun();

	_InitMVCDataForContract();
	_InitMVCDataForQuotes();
	_InitMVCDataForOrder();

	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		m_MapInstrumentIDData.clear();
	}


	{
		boost::mutex::scoped_lock lock(m_mutexForMapAccount);
		m_MapAccount.clear();
	}

	{
		boost::mutex::scoped_lock lock(m_mutexForMapOrder);
		m_MapOrder.clear();
	}


	{
		boost::mutex::scoped_lock lock(m_mutexForMapHistoryData);
		m_MapHistoryData.clear();
		m_nDoTest = 0;
	}

	
	//TODO.ForTest
	m_SignalControl_NotWork = 990;
	m_IndexSigalControl = 0;
}

CClientDataManagerWorker::~CClientDataManagerWorker(void)
{	
	//BOOST_LOG_FUNCTION();
	_UnInitLoginParam();

	if (NULL !=  m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}



	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		m_MapInstrumentIDData.clear();
	}

	{
		boost::mutex::scoped_lock lock(m_mutexForMapAccount);
		m_MapAccount.clear();
	}

	{
		boost::mutex::scoped_lock lock(m_mutexForMapOrder);
		m_MapOrder.clear();
	}

	{
		boost::mutex::scoped_lock lock(m_mutexForMapHistoryData);
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
		boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	
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
	boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	

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
	boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);	
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

	LOG_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
		<<" "<<"m_pNodeRootQuotes=ox"<<m_pTreeItemQuotes_Root;

	emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);

}
void CClientDataManagerWorker::_UnInitMVCDataForQuotes()
{
	boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);	

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
	boost::mutex::scoped_lock lock(m_mutexForMapOrder);	
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
		LOG_DEBUG<<" "<<"emit"
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
	boost::mutex::scoped_lock lock(m_mutexForMapOrder);	

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

	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		nGetInstrumentID = instrument.getInstrumentID();
		pGetInstrument = instrument.getInstrument(nGetInstrumentID);
		m_MapInstrumentIDData.insert(nGetInstrumentID, pGetInstrument);
		LOG_DEBUG<<"CClientDataManagerWorker"
			<<" "<<"onInstrumentDownloaded"
			<<" "<<"m_MapInstrumentIDData.size="<<m_MapInstrumentIDData.size();
		strLogInfo = "onInstrumentDownloaded";
		m_pUtilityFun->log_Instrument_info(DefFLInfo, strLogInfo, instrument);
	}


	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	
		m_pContractInfo->setValue(instrument);
		m_pTreeItemContract_Root->appendThreeChild(m_pContractInfo);
		//use slotContractInfoWindowResetData()
// 		m_IndexSigalControl++;
// 		if (m_IndexSigalControl > m_SignalControl_NotWork)
// 		{
// 			LOG_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
// 				<<" "<<"m_pNodeRootContract=0x"<<m_pTreeItemContract_Root;
// 			emit signalContractInfoChanged(m_pTreeItemContract_Root);
// 		}
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

	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);

		if (false == m_MapInstrumentIDData.contains(instrument.getInstrumentID()))
		{
			LOG_ERROR<<"not find nInstrumentID="<<instrument.getInstrumentID()
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			//TODO.
			return;
		}

		iterFind = m_MapInstrumentIDData.find(instrument.getInstrumentID());
		//find ok
		pInstrumentGet = iterFind.value();
		*pInstrumentGet = instrument;
		m_pQuotesInfo->setValue(*pInstrumentGet);
		LOG_DEBUG<<"onMarketDataUpdate reset contract to SmartQuotes"
			<<" "<<"strInstrumentCode="<<instrument.getInstrumentCode()
			<<" "<<"getTickSize="<<instrument.getTickSize();
		strLogInfo = "onMarketDataUpdate reset contract to SmartQuotes";
		m_pUtilityFun->log_Instrument_info(DefFLInfo, strLogInfo, instrument);
	}

	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);	
		m_pTreeItemQuotes_Root->resetChildrenData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
		LOG_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
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

	LOG_DEBUG<<"CClientDataManagerWorker process slotAddContractToSmartQuotes"
		<<" "<<"nInstrumentID="<<nInstrumentID;

	{
		//check in total list
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		if (false == m_MapInstrumentIDData.contains(nInstrumentID))
		{
			LOG_ERROR<<"not find nInstrumentID="<<nInstrumentID
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			//TODO.
			return;
		}
		iterFind = m_MapInstrumentIDData.find(nInstrumentID);

		//find ok
		pInstrumentRef = iterFind.value();
		//save to configfile
		QStringList strLstUserInstruemt;
		strLstUserInstruemt = CConfigInfo::getInstance().getLstUserInstrument();
		if (!strLstUserInstruemt.contains(QVariant(nInstrumentID).toString()))
		{
			strLstUserInstruemt.push_back(QVariant(nInstrumentID).toString());
			CConfigInfo::getInstance().setLstUserInstrument(strLstUserInstruemt);
		}

		//subscribe this instrument
		LOG_DEBUG<<"subscribeMarketData"<<" "<<"InstrumentID="<<nInstrumentID;
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
		boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);	

		strExchangeName = m_pQuotesInfo->m_strExchangeName.toStdString();
		strUnderlyingCode = m_pQuotesInfo->m_strUnderlyingCode.toStdString();
		strInstrumentCode = m_pQuotesInfo->m_strInstrumentCode.toStdString();
		LOG_DEBUG<<"slotAddContractToSmartQuotes add contract to SmartQuotes"
			<<" "<<"InstrumentID="<<nInstrumentID
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;

		m_pTreeItemQuotes_Root->appendChildByData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
		LOG_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
			<<" "<<"m_pTreeItemQuotes_Root=ox"<<m_pTreeItemQuotes_Root;
		emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);
	}
	

	{
		//TODO. TTTTTTTTTTT historydata test
		boost::mutex::scoped_lock lock(m_mutexForMapHistoryData);
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
			pHistoryDataManager->m_pHistoryRequest->setTimeFrom(m_pUtilityFun->getTimeNow() - 60 * 60 * 24 * 10);
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
	Instrument* pInstrument = NULL;
	QMap<unsigned int, Instrument*>::iterator  iterFind;

	LOG_DEBUG<<"CClientDataManagerWorker process singalRemoveContractFromSmartQuotes"
		<<" "<<"nInstrumentID="<<nInstrumentID;


	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		if (false == m_MapInstrumentIDData.contains(nInstrumentID))
		{
			LOG_ERROR<<"not find nInstrumentID="<<nInstrumentID
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			//TODO.
			return;
		}

		iterFind = m_MapInstrumentIDData.find(nInstrumentID);
		//find ok
		pInstrument = iterFind.value();

		//unsubscribe this instrument
		LOG_DEBUG<<"unsubscribeMarketData"
			<<" "<<"InstrumentID="<<pInstrument->getInstrumentID();
		m_pMyTradeClient->unsubscribeMarketData(pInstrument->getInstrumentID());

		m_pContractInfo->setValue(*pInstrument);
		m_pQuotesInfo->setValue(*pInstrument);		
	}


	//remove
	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);
		LOG_DEBUG<<"slotRemoveContractFromSmartQuotes remove hot Quotes"
			<<" "<<"InstrumentID="<<nInstrumentID
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;

		m_pTreeItemQuotes_Root->removeChildByData(m_pQuotesInfo);

		LOG_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"emit"
			<<" "<<"signalQuotesInfoChanged(CTreeItemQuotes*)"
			<<" "<<"param:"
			<<" "<<"m_pTreeItemQuotes_Root=0x"<<m_pTreeItemQuotes_Root;
		emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);
	}
		

	//add
	{		
		boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	
		LOG_DEBUG<<"slotRemoveContractFromSmartQuotes add contract to ContratInfo"
			<<" "<<"InstrumentID="<<nInstrumentID
			<<" "<<"ExchangeName="<<m_pContractInfo->getExchangeName().toStdString()
			<<" "<<"strInstrumentCode="<<m_pContractInfo->getInstrumentCode().toStdString();

		m_pTreeItemContract_Root->appendThreeChild(m_pContractInfo);

		LOG_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
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

	LOG_DEBUG<<"CClientDataManagerWorker process signalClientLoginParamChanged"
		<<" "<<"pClientLoginParam=0x"<<pClientLoginParam;

	_UnInitLoginParam();
	m_pClientLoginParam = new CClientLoginParam();
	m_pClientLoginParam->setDefaultValue();
	*m_pClientLoginParam = *pClientLoginParam;

	_UnInitTraderClient();
	m_pMyTradeClient = new CSmartTraderClient(*m_pClientLoginParam);
	m_pMyTradeClient->setProcessRecvDataHandle(this);
	nloginToServerRes = m_pMyTradeClient->loginToServer();

	LOG_DEBUG<<"CClientDataManagerWorker emit signalLoginToServerResult"
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

	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		nGetInstrumentID = 1;
		pGetInstrument = NULL;
		m_MapInstrumentIDData.insert(nGetInstrumentID, pGetInstrument);
		LOG_DEBUG<<"CClientDataManagerWorker"
			<<" "<<"onInstrumentDownloaded"
			<<" "<<"m_MapInstrumentIDData.size="<<m_MapInstrumentIDData.size();
	}


	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	
		m_pContractInfo->setDefaultValue();
		m_pTreeItemContract_Root->appendThreeChild(m_pContractInfo);

		LOG_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
			<<" "<<"m_pNodeRootContract=0x"<<m_pTreeItemContract_Root;

		emit signalContractInfoChanged(m_pTreeItemContract_Root);
	}


	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);
		m_pQuotesInfo->setDefaultValue();
		m_pTreeItemQuotes_Root->appendChildByData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
		LOG_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
			<<" "<<"m_pNodeRootQuotes=ox"<<m_pTreeItemQuotes_Root;
		emit signalQuotesInfoChanged(m_pTreeItemQuotes_Root);
	}



}



void CClientDataManagerWorker::slotQuotesTableViewColumnsChanged()
{

	LOG_DEBUG<<" "<<"slot"
		<<" "<<"class:"<<"CClientDataManagerWorker"
		<<" "<<"slot"
		<<" "<<"slotQuotesTableViewColumnsChanged";

	//subscribeMarketData user hot Instrument
	QStringList lstUserInstrument;
	Instrument* pInstrument = NULL;
	unsigned int nInstrumentID = 0;
	QMap<unsigned int, Instrument*>::iterator  iterFind;

	lstUserInstrument = CConfigInfo::getInstance().getLstUserInstrument();
	
	{
		boost::mutex::scoped_lock lockMutexForNodeRootQuotes(m_mutexForNodeRootQuotes);
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
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		boost::mutex::scoped_lock lockMutexForNodeRootQuotes(m_mutexForNodeRootQuotes);
		
		//reset child data
		foreach (const QString& strInstrument, lstUserInstrument)
		{
			nInstrumentID = strInstrument.toUInt();
			if (m_MapInstrumentIDData.contains(nInstrumentID))
			{
				iterFind = m_MapInstrumentIDData.find(nInstrumentID);
				pInstrument = iterFind.value();
				m_pQuotesInfo->setValue(*pInstrument);
				m_pTreeItemQuotes_Root->appendChildByData(m_pQuotesInfo);
			}//if
		}//foreach

		LOG_DEBUG<<" "<<"emit"
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
		boost::mutex::scoped_lock lock(m_mutexForMapAccount);
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
		boost::mutex::scoped_lock lock(m_mutexForMapOrder);

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
		LOG_DEBUG<<" "<<"emit"
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
		boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);	
		nInstruemntID = m_pTreeItemQuotes_Root->getHotInstrumentIDByCode(strInstrumentCode);
		LOG_DEBUG<<"strInstrumentCode="<<strInstrumentCode.toStdString()
			<<" "<<"getHotInstrumentIDByCode"
			<<" "<<"nInstruemntID="<<nInstruemntID;
	}

	return nInstruemntID;
}

void CClientDataManagerWorker::slotNewOrder( CUserOrderInfo* pUserOrderInfo)
{
	//emit
	{
		LOG_DEBUG<<" "<<"slot"
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

	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		if (false == m_MapInstrumentIDData.contains(nInstrumentID))
		{
			LOG_ERROR<<"not find nInstrumentID="<<nInstrumentID
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			return;
		}

		iterFind = m_MapInstrumentIDData.find(nInstrumentID);
		//find ok
		pInstrumentGet = iterFind.value();
	}

	{
		boost::mutex::scoped_lock lock(m_mutexForMapAccount);
		if (m_MapAccount.isEmpty())
		{
			LOG_ERROR<<" "<<"m_MapAccount is empty";
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
		LOG_ERROR<<"CClientDataManagerWorker::slotNewOrder"<<" Order::UNKNOWN";
		break;
	}//switch (nSide)



}

void CClientDataManagerWorker::onBarDataUpdate( const BarSummary &barData )
{
	LOG_DEBUG<<"CClientDataManagerWorker::onBarDataUpdate"
		<<" "<<"barData.instrumentID="<<barData.instrumentID
		<<" "<<"barData.bars.size="<<barData.bars.size();

	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;

	{
		//TODO. historydata test
		boost::mutex::scoped_lock lock(m_mutexForMapHistoryData);

		if (!m_MapHistoryData.contains(barData.instrumentID))
		{
			//find error
			LOG_ERROR<<" "<<"find error instrumentID="<<barData.instrumentID;
			return;
		}
		iterMap = m_MapHistoryData.find(barData.instrumentID);

		pHistoryDataManager = iterMap.value();
		pHistoryDataManager->m_pHistoryACK->onBarDataUpdate(barData);
		pHistoryDataManager->m_pHistoryACK->logInfo();


		{
			LOG_DEBUG<<" "<<"emit"
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
	LOG_DEBUG<<"CClientDataManagerWorker::onHistoryDataDownloaded"
		<<" "<<"requestID="<<requestID
		<<" "<<"bars->size.size="<<bars->size();

	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;

	{
		//TODO. historydata test
		boost::mutex::scoped_lock lock(m_mutexForMapHistoryData);
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
			LOG_ERROR<<" "<<"not find requestID="<<requestID;
			return;
		}

		pHistoryDataManager = iterMap.value();
		pHistoryDataManager->m_pHistoryACK->onHistoryDataDownloaded(bars);
		pHistoryDataManager->m_pHistoryACK->logInfo();


		{
			LOG_DEBUG<<" "<<"emit"
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

	LOG_DEBUG<<" "<<"slot"
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
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);

		foreach (const QString& strUserInstrumentID, strLstUserInstruemt)
		{
			nUserInstrumentID = 0;
			nUserInstrumentID = strUserInstrumentID.toUInt();

			if (false == m_MapInstrumentIDData.contains(nUserInstrumentID))
			{
				LOG_ERROR<<"not find nInstrumentID="<<nUserInstrumentID
					<<" "<<"in m_MapInstrumentIDData"
					<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
				pInstrumentRef = NULL;
			}
			else
			{
				//find ok
				iterFind = m_MapInstrumentIDData.find(nUserInstrumentID);
				pInstrumentRef = iterFind.value();

				m_pContractInfo->setValue(*pInstrumentRef);
				strExchangeName = m_pContractInfo->getExchangeName().toStdString();
				strUnderlyingCode = m_pContractInfo->getUnderlyingCode().toStdString();
				strInstrumentCode = m_pContractInfo->getInstrumentCode().toStdString();
				LOG_DEBUG<<"ContractInfo Window Reset Data"
					<<" "<<"InstrumentID="<<m_pContractInfo->getInstrumentID()
					<<" "<<"ExchangeName="<<strExchangeName
					<<" "<<"strInstrumentCode="<<strInstrumentCode;

				//remove nInstrumentID from m_pTreeItemContract_Root
				boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	
				m_pTreeItemContract_Root->removeChildrenByData(m_pContractInfo);
			}//if

		}//foreach
	}

	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	
		LOG_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
			<<" "<<"m_pTreeItemContract_Root=0x"<<m_pTreeItemContract_Root;
		emit signalContractInfoChanged(m_pTreeItemContract_Root);
	}
}


//QT_END_NAMESPACE


