#include "ClientDataManagerWorker.h"

#include <QtCore/QStringList>

#include "ContractInfo.h"
#include "TreeItemContract.h"
#include "QuotesInfo.h"
#include "TreeItemQuotes.h"
#include "ClientLoginParam.h"
#include "SmartTraderClient.h"
#include "ProjectUtilityFun.h"
#include "ConfigInfo.h"


#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CClientDataManagerWorker::CClientDataManagerWorker(void)
{	
	//BOOST_LOG_FUNCTION();

	m_nThreadJobState = JobState_Begin;
	m_toTerminate = false;

	m_pClientLoginParam = NULL;
	m_pMyTradeClient = NULL;
	m_pNodeRootContract = NULL;
	m_pContractInfo = NULL;
	m_pQuotesInfo = NULL;
	m_pNodeRootQuotes = NULL;
	m_pUtilityFun = NULL;

	m_pUtilityFun = new CProjectUtilityFun();

	_InitMVCDataForContract();
	_InitMVCDataForQuotes();

	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		m_MapInstrumentIDData.clear();
	}


	{
		boost::mutex::scoped_lock lock(m_mutexForMapAccount);
		m_MapAccount.clear();
	}
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
}

void CClientDataManagerWorker::run()
{
	m_nThreadJobState = JobState_Begin;

	while (false == m_toTerminate)
	{
		//_ThreadJob();
		CBoostThread::sleep(1000);
	}
	_ProcessUserTerminate();
}

void CClientDataManagerWorker::terminate()
{
	//BOOST_LOG_FUNCTION();

	m_toTerminate = true;
}


int CClientDataManagerWorker::_ProcessUserTerminate()
{
	//BOOST_LOG_FUNCTION();

	int nFunRes = 0;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CClientDataManagerWorker::isFinishWork()
{
	//BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CClientDataManagerWorker::_ThreadJob()
{
	//BOOST_LOG_FUNCTION();


	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		m_nThreadJobState = JobState_InitParam;
		break;
	case JobState_InitParam:
		_Process_InitParam();
		break;
	case JobState_LoginToServer:
		_Process_LoginToServer();
		break;
	case JobState_MonitorExchangeInfo:
		_Process_MonitorExchangeInfo();
		break;
	case JobState_StopWork:
		_Process_StopWork();
		//TA_App_App::CBoostThread::sleep(1000);
		break;
	case JobState_End:
		//TA_App_App::CBoostThread::sleep(1000);
		break;
	default:
		break;

	}//switch
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CClientDataManagerWorker::_Process_InitParam()
{
	_InitLoginParam();
	_InitTraderClient();
	m_nThreadJobState = JobState_LoginToServer;

}
void CClientDataManagerWorker::_Process_LoginToServer()
{
	m_nThreadJobState = JobState_MonitorExchangeInfo;

	if (NULL != m_pMyTradeClient)
	{
		delete m_pMyTradeClient;
		m_pMyTradeClient = NULL;
	}
	m_pMyTradeClient = new CSmartTraderClient(*m_pClientLoginParam);
	m_pMyTradeClient->setProcessRecvDataHandle(this);
	int nloginToServerRes = m_pMyTradeClient->loginToServer();

	LOG_DEBUG<<"CClientDataManagerWorker emit signalLoginToServerResult"
		<<" "<<"nlogonToServerRes="<<nloginToServerRes;

	emit signalLoginToServerResult(nloginToServerRes);

}

void CClientDataManagerWorker::_Process_MonitorExchangeInfo()
{
	m_nThreadJobState = JobState_MonitorExchangeInfo;
	//TODO.
}

void CClientDataManagerWorker::_Process_StopWork()
{
	_UnInitTraderClient();
	_UnInitLoginParam();
	_UnInitMVCDataForContract();
	_UnInitMVCDataForQuotes();
	m_nThreadJobState = JobState_End;
}


//////////////////////////////////////////////////////////////////////////
void CClientDataManagerWorker::_InitLoginParam()
{
	_UnInitLoginParam();
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

void CClientDataManagerWorker::_InitTraderClient()
{
	_UnInitTraderClient();
	m_pMyTradeClient = new CSmartTraderClient(*m_pClientLoginParam);
	m_pMyTradeClient->setProcessRecvDataHandle(this);
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

void CClientDataManagerWorker::_InitMVCDataForContract()
{
	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	
		if (NULL != m_pNodeRootContract)
		{
			delete m_pNodeRootContract;
			m_pNodeRootContract = NULL;
		}

		QList<QVariant> dataColumn;
		QString strMapKey;
		dataColumn.clear();
		dataColumn.push_back("DataType_Root");
		m_pNodeRootContract = new CTreeItemContract(dataColumn, NULL);
		m_pNodeRootContract->setDataType(CTreeItemContract::DataTypeContract_Root);
		m_pNodeRootContract->setInstrumentID(0);
		m_pContractInfo = new CContractInfo();
	}




}
void CClientDataManagerWorker::_UnInitMVCDataForContract()
{
	boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	

	if (NULL != m_pNodeRootContract)
	{
		delete m_pNodeRootContract;
		m_pNodeRootContract = NULL;
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
	if (NULL != m_pNodeRootQuotes)
	{
		delete m_pNodeRootQuotes;
		m_pNodeRootQuotes = NULL;
	}

	//root node save all column Names
	QList<QVariant> dataTreeItem;
	CTreeItemQuotes::getLstClumnName(dataTreeItem);
	m_pNodeRootQuotes = new CTreeItemQuotes(dataTreeItem, NULL);
	m_pNodeRootQuotes->setDataType(CTreeItemQuotes::DataTypeSmartQuotes_Root);
	m_pNodeRootQuotes->rootNodeRetColumnsName();

	m_pQuotesInfo = new CQuotesInfo();

	LOG_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
		<<" "<<"m_pNodeRootQuotes=ox"<<m_pNodeRootQuotes;

	emit signalQuotesInfoChanged(m_pNodeRootQuotes);

}
void CClientDataManagerWorker::_UnInitMVCDataForQuotes()
{
	boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);	

	if (NULL != m_pNodeRootQuotes)
	{
		delete m_pNodeRootQuotes;
		m_pNodeRootQuotes = NULL;
	}

	if (NULL != m_pQuotesInfo)
	{
		delete m_pQuotesInfo;
		m_pQuotesInfo = NULL;
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
		m_pNodeRootContract->appendThreeChild(m_pContractInfo);

		LOG_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
			<<""<<"m_pNodeRootContract=0x"<<m_pNodeRootContract;

		emit signalContractInfoChanged(m_pNodeRootContract);
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
		m_pNodeRootQuotes->resetChildrenData(m_pQuotesInfo);
		m_pNodeRootQuotes->rootNodeRetColumnsName();
		LOG_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
			<<" "<<"m_pNodeRootQuotes=ox"<<m_pNodeRootQuotes;
		emit signalQuotesInfoChanged(m_pNodeRootQuotes);
	}



}

void CClientDataManagerWorker::slotAddContractToSmartQuotes( unsigned int nInstrumentID )
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	Instrument* pInstrument = NULL;
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
		pInstrument = iterFind.value();

		QStringList strLstUserInstruemt;
		strLstUserInstruemt = CConfigInfo::getInstance().getLstUserInstrument();
		if (!strLstUserInstruemt.contains(QVariant(nInstrumentID).toString()))
		{
			strLstUserInstruemt.push_back(QVariant(nInstrumentID).toString());
			CConfigInfo::getInstance().setLstUserInstrument(strLstUserInstruemt);
		}

		//subscribe this instrument
		LOG_DEBUG<<"subscribeMarketData"
			<<" "<<"InstrumentID="<<nInstrumentID;
		m_pMyTradeClient->subscribeMarketData(nInstrumentID);

		m_pQuotesInfo->setValue(*pInstrument);
		strExchangeName = m_pQuotesInfo->m_strExchangeName.toStdString();
		strUnderlyingCode = m_pQuotesInfo->m_strUnderlyingCode.toStdString();
		strInstrumentCode = m_pQuotesInfo->m_strInstrumentCode.toStdString();
		LOG_DEBUG<<"slotAddContractToSmartQuotes add contract to SmartQuotes"
			<<" "<<"InstrumentID="<<nInstrumentID
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;

	}

	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);	
		m_pNodeRootQuotes->appendChildByData(m_pQuotesInfo);
		m_pNodeRootQuotes->rootNodeRetColumnsName();
		LOG_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
			<<" "<<"m_pNodeRootQuotes=ox"<<m_pNodeRootQuotes;
		emit signalQuotesInfoChanged(m_pNodeRootQuotes);
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
		strExchangeName = m_pContractInfo->getExchangeName().toStdString();
		strUnderlyingCode = m_pContractInfo->getUnderlyingCode().toStdString();
		strInstrumentCode = m_pContractInfo->getInstrumentCode().toStdString();
		LOG_DEBUG<<"slotRemoveContractFromSmartQuotes add contract to ContratInfo"
			<<" "<<"InstrumentID="<<nInstrumentID
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;
	}


		
	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootContract);	
		m_pNodeRootContract->appendThreeChild(m_pContractInfo);
		LOG_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
			<<""<<"m_pNodeRootContract=0x"<<m_pNodeRootContract;
		emit signalContractInfoChanged(m_pNodeRootContract);
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
	_Process_InitParam();
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
		m_pNodeRootContract->appendThreeChild(m_pContractInfo);

		LOG_DEBUG<<"CClientDataManagerWorker emit signalContractInfoChanged"
			<<""<<"m_pNodeRootContract=0x"<<m_pNodeRootContract;

		emit signalContractInfoChanged(m_pNodeRootContract);
	}


	{
		boost::mutex::scoped_lock lock(m_mutexForNodeRootQuotes);
		m_pQuotesInfo->setDefaultValue();
		m_pNodeRootQuotes->appendChildByData(m_pQuotesInfo);
		m_pNodeRootQuotes->rootNodeRetColumnsName();
		LOG_DEBUG<<"CClientDataManagerWorker emit signalQuotesInfoChanged"
			<<" "<<"m_pNodeRootQuotes=ox"<<m_pNodeRootQuotes;
		emit signalQuotesInfoChanged(m_pNodeRootQuotes);
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
		if (NULL != m_pNodeRootQuotes)
		{
			delete m_pNodeRootQuotes;
			m_pNodeRootQuotes = NULL;
		}
		//new root data
		QList<QVariant> dataTreeItem;
		CTreeItemQuotes::getLstClumnName(dataTreeItem);
		m_pNodeRootQuotes = new CTreeItemQuotes(dataTreeItem, NULL);
		m_pNodeRootQuotes->setDataType(CTreeItemQuotes::DataTypeSmartQuotes_Root);
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
				m_pNodeRootQuotes->appendChildByData(m_pQuotesInfo);
			}//if
		}//foreach

		LOG_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"emit"
			<<" "<<"signalQuotesInfoChanged(CTreeItemQuotes*)"
			<<" "<<"param:"
			<<" "<<"m_pNodeRootQuotes=0x"<<m_pNodeRootQuotes;

		emit signalQuotesInfoChanged(m_pNodeRootQuotes);
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

void CClientDataManagerWorker::slotNewOrder( Order::Side nSide, Order::OrderType nOrderType, QString strInstrumentCode, double fPrice, int quantity )
{
	//emit
	{
		LOG_DEBUG<<" "<<"slot"
			<<" "<<"class:"<<"CClientDataManagerWorker"
			<<" "<<"fun:"<<"slotNewOrder()"
			<<" "<<"slot"
			<<" "<<"slotNewOrder()"
			<<" "<<"param:"
			<<" "<<"nSide="<<nSide
			<<" "<<"nOrderType="<<nOrderType
			<<" "<<"strInstrumentCode="<<strInstrumentCode.toStdString().c_str()
			<<" "<<"fPrice="<<fPrice
			<<" "<<"quantity="<<quantity;
	}


	QMap<unsigned int, Instrument*>::iterator  iterFind;
	std::string strLogInfo;
	Instrument* pInstrumentGet = NULL;
	Account* pAccount = NULL;

	{
		boost::mutex::scoped_lock lock(m_mutexForMapInstrumentIDData);
		if (false == m_MapInstrumentIDData.contains(strInstrumentCode.toUInt()))
		{
			LOG_ERROR<<"not find nInstrumentID="<<strInstrumentCode.toUInt()
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			return;
		}

		iterFind = m_MapInstrumentIDData.find(strInstrumentCode.toUInt());
		//find ok
		pInstrumentGet = iterFind.value();
	}

	{
		boost::mutex::scoped_lock lock(m_mutexForMapAccount);
		if (m_MapAccount.isEmpty())
		{
			LOG_ERROR<<""<<"m_MapAccount is empty";
			return;
		}
		pAccount = m_MapAccount.begin().value();
	}

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


//QT_END_NAMESPACE


