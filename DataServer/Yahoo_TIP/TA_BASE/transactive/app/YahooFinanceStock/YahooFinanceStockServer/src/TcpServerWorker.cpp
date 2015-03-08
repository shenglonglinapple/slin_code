#include "TcpServerWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "StockTcpServer.h"
#include "ServerDistributeTaskWorker.h"
#include "ServerDbOper.h"
#include "UserInfo.h"
#include "UserTradeInfo.h"
#include "Log4cppLogger.h"
#include "UserAccount.h"
#include "UserHoldAccount.h"
#include "HistoryData.h"
#include "StockDataManager.h"

CTcpServerWorker::CTcpServerWorker( quint16 nListenPort, QObject* parent/*=0*/ )
{
	m_nListenPort = 0;
	m_pStockTcpServer = NULL;
	m_pServerDistributeTaskWorker = NULL;
	m_pServerDbOper = NULL;

	m_nListenPort = nListenPort;
	m_pServerDbOper = new CServerDbOper(QString("%1").arg(m_nListenPort));//5001.db

}

CTcpServerWorker::~CTcpServerWorker()
{
	if (NULL != m_pServerDbOper)
	{
		delete m_pServerDbOper;
		m_pServerDbOper = NULL;
	}
}

void CTcpServerWorker::run()
{
	MYLOG4CPP_DEBUG<<"CTcpServerWorker::run() begin";

	m_pStockTcpServer = new CStockTcpServer(m_nListenPort, this);
	m_pServerDistributeTaskWorker = new CServerDistributeTaskWorker(this);

	QObject::connect(m_pStockTcpServer, SIGNAL(signalIncomingConnection(qint32)), 
		m_pServerDistributeTaskWorker, SLOT(slotIncomingConnection(qint32)), Qt::AutoConnection);


	try
	{
		m_pStockTcpServer->startListen();
		m_pServerDistributeTaskWorker->start();

		MYLOG4CPP_DEBUG<<"CTcpServerWorker::run() exec() begin";
		exec();
		MYLOG4CPP_DEBUG<<"CTcpServerWorker::run() exec() end";

	}
	catch (CBaseException& e)
	{
		e.logInfo(__FILE__, __LINE__);
	}


	if (NULL != m_pServerDistributeTaskWorker)
	{
		m_pServerDistributeTaskWorker->terminateAndWait();
		delete m_pServerDistributeTaskWorker;
		m_pServerDistributeTaskWorker = NULL;
	}

	if (NULL != m_pStockTcpServer)
	{
		m_pStockTcpServer->stopListen();
		delete m_pStockTcpServer;
		m_pStockTcpServer = NULL;
	}


	MYLOG4CPP_DEBUG<<"CTcpServerWorker::run() end";
}

void CTcpServerWorker::terminate()
{
	MYLOG4CPP_DEBUG<<"CTcpServerWorker::terminate() begin";


	MYLOG4CPP_DEBUG<<"CTcpServerWorker::terminate() end";
}


qint32 CTcpServerWorker::selectUserInfo(quint16 nListenPort,const QString & strUSERNAME, const QString& strPASSWORD, CUserInfo** ppData)
{
	qint32 nFunRes = 0;
	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->selectUserInfo(strUSERNAME, strPASSWORD, ppData);
	return nFunRes;
}
qint32 CTcpServerWorker::updateUserInfo(quint16 nListenPort, const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->updateUserInfo(pData);
	return nFunRes;
}
qint32 CTcpServerWorker::createUserInfo(quint16 nListenPort, const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->insertUserInfo(pData);
	return nFunRes;
}

qint32 CTcpServerWorker::createUserAmount( quint16 nListenPort, const CUserAccount* pData )
{
	qint32 nFunRes = 0;
	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->insertUserAccount(pData);
	return nFunRes;
}
double CTcpServerWorker::getUserHoldAmount(const QString& strUserID, const QString& strTime)
{
	qint32 nFunRes = 0;
	QList<CUserHoldAccount*> LstData;
	QList<CUserHoldAccount*>::iterator iterLst;
	QList<CHistoryData*> lstHisData;
	QList<CHistoryData*>::iterator iterlstHis;

	CHistoryData* pHistoryData = NULL;
	CUserHoldAccount* pUserHoldAmount_current_symbol = NULL;
	double fHoldAmount = 0;
	CUserAccount* pUserAmount = NULL;	


	m_pServerDbOper->selectUserHoldAccount(strUserID, LstData);
	iterLst = LstData.begin();
	while (iterLst != LstData.end())
	{
		pUserHoldAmount_current_symbol = (*iterLst);
		CStockDataManager::getInstance().doWork_HistoryData(
			pUserHoldAmount_current_symbol->m_strSymbolUse,
			strTime, strTime, lstHisData);

		iterlstHis = lstHisData.begin();
		if (iterlstHis != lstHisData.end())
		{
			pHistoryData = (*iterlstHis);
			pUserHoldAmount_current_symbol->updatePrice(pHistoryData->m_strClose.toDouble(), strTime);
			m_pServerDbOper->updateUserHoldAccount(pUserHoldAmount_current_symbol);
			fHoldAmount += pUserHoldAmount_current_symbol->m_fHoldAccount;
		}
		else
		{
			pUserHoldAmount_current_symbol->updatePrice(pUserHoldAmount_current_symbol->m_fPrice, strTime);
			m_pServerDbOper->updateUserHoldAccount(pUserHoldAmount_current_symbol);
			fHoldAmount += pUserHoldAmount_current_symbol->m_fHoldAccount;
		}

		iterlstHis = lstHisData.begin();
		while (iterlstHis != lstHisData.end())
		{
			pHistoryData = (*iterlstHis);
			delete pHistoryData;
			pHistoryData = NULL;
			iterlstHis++;
		}
		lstHisData.clear();

		iterLst++;
	}//while

	iterLst = LstData.begin();
	while (iterLst != LstData.end())
	{
		pUserHoldAmount_current_symbol = (*iterLst);
		delete pUserHoldAmount_current_symbol;
		pUserHoldAmount_current_symbol = NULL;
		iterLst++;
	}
	LstData.clear();

	return fHoldAmount;
}

bool CTcpServerWorker::_CheckTrade(const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	CUserAccount* pUserAccount_Data = NULL;
	CUserHoldAccount* pUserHoldAccount_Data = NULL;
	double fLeftAccount = 0;
	double fHoldAccount = 0;
	QString strUserID;
	QString strSymbolUse;
	CTcpComProtocol::ETradeType nTradeType;
	bool bCheckRes = true;

	if (NULL == m_pServerDbOper || NULL == pData || pData->m_strUserID.isEmpty() || pData->m_strSymbolUse.isEmpty())
	{
		MYLOG4CPP_ERROR<<"_CheckTrade error: NULL == m_pServerDbOper || NULL == pData || pData->m_strUserID.isEmpty() || pData->m_strSymbolUse.isEmpty()";
		bCheckRes = false;
		return bCheckRes;
	}
	strUserID = pData->m_strUserID;
	strSymbolUse = pData->m_strSymbolUse;
	nTradeType = pData->m_nTradeType;
	nFunRes = m_pServerDbOper->selectUserAccount(strUserID, &pUserAccount_Data);
	if (NULL == pUserAccount_Data)
	{
		MYLOG4CPP_ERROR<<"_CheckTrade error:select User Account"<<" "<<"strUserID="<<strUserID;
		bCheckRes = false;
		return bCheckRes;
	}
	nFunRes = m_pServerDbOper->selectUserHoldAccount(strUserID, strSymbolUse, &pUserHoldAccount_Data);
	//check and init value
	if (NULL == pUserHoldAccount_Data)
	{
		if (CTcpComProtocol::ETradeType_Buy == nTradeType)
		{
			//first buy insert one
			pUserHoldAccount_Data = new CUserHoldAccount();
			pUserHoldAccount_Data->setValue_FirstBuy(pData);
			m_pServerDbOper->insertUserHoldAccount(pUserHoldAccount_Data);
		}
		else
		{
			//sell but not find 
			MYLOG4CPP_ERROR<<"_CheckTrade error: not find pUserHoldAccount strUserID="<<strUserID
				<<" "<<"strSymbolUse="<<strSymbolUse;
			bCheckRes = false;
			return bCheckRes;
		}
	}//if (NULL == pUserHoldAmount)

	//delete first then select again
	if (NULL != pUserHoldAccount_Data)
	{
		delete pUserHoldAccount_Data;
		pUserHoldAccount_Data = NULL;
	}
	nFunRes = m_pServerDbOper->selectUserHoldAccount(strUserID, strSymbolUse, &pUserHoldAccount_Data);
	if (NULL == pUserHoldAccount_Data || NULL == pUserAccount_Data)
	{
		MYLOG4CPP_ERROR<<"_CheckTrade error again: not find pUserHoldAccount strUserID="<<strUserID
			<<" "<<"strSymbolUse="<<strSymbolUse;
		bCheckRes = false;
		return bCheckRes;
	}

	//check buy
	if (CTcpComProtocol::ETradeType_Buy == nTradeType)
	{
		//check buy, check left Acccount
		if (pUserAccount_Data->m_fLeftAccount < pData->m_fUseAccount)
		{
			MYLOG4CPP_ERROR<<"_CheckTrade buy error: money is not enough strUserID="<<strUserID
				<<" "<<"fLeftAccount="<<fLeftAccount
				<<" "<<"<"<<" "<<"pData->m_fUseAccount="<<pData->m_fUseAccount;
			bCheckRes = false;
		}
	}
	//check sell
	if (CTcpComProtocol::ETradeType_Sell == nTradeType)
	{
		if ((0 >= pUserHoldAccount_Data->m_nVolume) || (pData->m_nTradeVolume > pUserHoldAccount_Data->m_nVolume))
		{
			MYLOG4CPP_ERROR<<"_CheckTrade sell error: Volume is not enough strUserID="<<strUserID
				<<" "<<"strSymbolUse="<<strSymbolUse
				<<" "<<"pUserHoldAccount->m_nVolume="<<pUserHoldAccount_Data->m_nVolume
				<<" "<<"<"<<" "<<"pData->m_nTradeVolume="<<pData->m_nTradeVolume;
			bCheckRes = false;
		}
	}

	if (NULL == pUserAccount_Data)
	{
		delete pUserAccount_Data;
		pUserAccount_Data = NULL;
	}
	if (NULL != pUserHoldAccount_Data)
	{
		delete pUserHoldAccount_Data;
		pUserHoldAccount_Data = NULL;
	}
	return bCheckRes;
}

qint32 CTcpServerWorker::processUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	QString strUserID;
	QString strSymbolUse;
	CTcpComProtocol::ETradeType nTradeType;
	bool bCheckRes = false;
	CUserAccount* pUserAccount_Data = NULL;
	CUserHoldAccount* pUserHoldAccount_Data = NULL;
	double fLeftAccount = 0;
	double fHoldAccount = 0;

	if (NULL == pData)
	{
		nFunRes = -1;
		return nFunRes;
	}
	strUserID = pData->m_strUserID;
	strSymbolUse = pData->m_strSymbolUse;
	nTradeType = pData->m_nTradeType;
	pData->logInfo(__FILE__, __LINE__);
	bCheckRes = _CheckTrade(pData);
	if (false == bCheckRes)
	{
		//check error
		MYLOG4CPP_ERROR<<"_CheckTrade error!"<<" "<<"m_strTradeUUID="<<pData->m_strTradeUUID;
		nFunRes = -1;
		return nFunRes;
	}

	//do trade
	nFunRes = m_pServerDbOper->selectUserAccount(strUserID, &pUserAccount_Data);
	nFunRes = m_pServerDbOper->selectUserHoldAccount(strUserID, strSymbolUse, &pUserHoldAccount_Data);
	fLeftAccount = pUserAccount_Data->m_fLeftAccount;
	MYLOG4CPP_INFO<<"processUserTradeInfo"
		<<" "<<"pUserAccount_Data->m_fLeftAccount="<<pUserAccount_Data->m_fLeftAccount
		<<" "<<"fLeftAccount="<<fLeftAccount;
	if (CTcpComProtocol::ETradeType_Buy == nTradeType)
	{
		fLeftAccount -= pData->m_fUseAccount;
	}
	else //if (CTcpComProtocol::ETradeType_Buy == nTradeType)
	{
		fLeftAccount += pData->m_fUseAccount;
	}
	MYLOG4CPP_INFO<<"processUserTradeInfo"
		<<" "<<"pUserAccount_Data->m_fLeftAccount="<<pUserAccount_Data->m_fLeftAccount
		<<" "<<"fLeftAccount="<<fLeftAccount;
	pData->logInfo(__FILE__, __LINE__);
	//do
	MYLOG4CPP_INFO<<"processUserTradeInfo"<<" "<<"startTransaction";
	m_pServerDbOper->startTransaction();
	nFunRes = m_pServerDbOper->insertUserTradeInfo(pData);//trade
	pUserHoldAccount_Data->updateHoldAmountValue(pData);//hold
	nFunRes = m_pServerDbOper->updateUserHoldAccount(pUserHoldAccount_Data);//hold
	pUserHoldAccount_Data->logInfo(__FILE__, __LINE__);

	fHoldAccount = getUserHoldAmount(pData->m_strUserID, pData->m_strTradeTime);//hold total
	MYLOG4CPP_INFO<<"getUserHoldAmount"<<" "<<"fHoldAccount="<<fHoldAccount;
	pUserAccount_Data->updateLeftAccount(fLeftAccount, pData->m_strTradeTime);//
	pUserAccount_Data->updateHoldAccount(fHoldAccount, pData->m_strTradeTime);
	MYLOG4CPP_INFO<<"updateLeftAccount"<<" "<<"fLeftAccount="<<fLeftAccount
				<<" "<<"pData->m_strTradeTime="<<pData->m_strTradeTime;
	MYLOG4CPP_INFO<<"updateHoldAccount"<<" "<<"fHoldAccount="<<fHoldAccount
				<<" "<<"pData->m_strTradeTime="<<pData->m_strTradeTime;
	nFunRes = m_pServerDbOper->updateUserAccount(pUserAccount_Data);
	pUserAccount_Data->logInfo(__FILE__, __LINE__);
	m_pServerDbOper->commitTransaction();
	MYLOG4CPP_INFO<<"processUserTradeInfo"<<" "<<"commitTransaction";

	if (NULL == pUserAccount_Data)
	{
		delete pUserAccount_Data;
		pUserAccount_Data = NULL;
	}
	if (NULL != pUserHoldAccount_Data)
	{
		delete pUserHoldAccount_Data;
		pUserHoldAccount_Data = NULL;
	}
	return nFunRes;
}

void CTcpServerWorker::sendMessage( qint32 handle, QByteArray* pMessage )
{
	if (NULL == m_pServerDistributeTaskWorker)
	{
		return;
	}
	m_pServerDistributeTaskWorker->sendMessage(handle, pMessage);
}



qint32 CTcpServerWorker::selectUserTradeInfo( quint16 nListenPort, QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse )
{
	qint32 nFunRes = 0;
	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->selectUserTradeInfo(lstData, strUserID,strSymbolUse);

	return nFunRes;
}

qint32 CTcpServerWorker::processUserAccount( quint16 nListenPort, const QString& strUserID, 
										   const QString& strTime, CUserAccount** ppData )
{
	qint32 nFunRes = 0;
	CUserAccount* pUserAmount = NULL;
	double fLeftAmount = 0;
	double fHoldAmount = 0;

	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	if (strUserID.isEmpty())
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->selectUserAccount(strUserID, &pUserAmount);
	if (NULL == pUserAmount)
	{
		MYLOG4CPP_ERROR<<"error:select User Amount m_strUserID="<<strUserID;
		nFunRes = -1;
		return nFunRes;
	}


	//do
	if (strTime.isEmpty())
	{	
		(*ppData) = pUserAmount;
		pUserAmount = NULL;
		return nFunRes;
	}

	m_pServerDbOper->startTransaction();
	fHoldAmount = getUserHoldAmount(strUserID, strTime);
	pUserAmount->updateHoldAccount(fHoldAmount, strTime);
	nFunRes = m_pServerDbOper->updateUserAccount(pUserAmount);
	m_pServerDbOper->commitTransaction();
	if (NULL == pUserAmount)
	{
		delete pUserAmount;
		pUserAmount = NULL;
	}

	nFunRes = m_pServerDbOper->selectUserAccount(strUserID, &pUserAmount);
	(*ppData) = pUserAmount;
	pUserAmount = NULL;
	return nFunRes;
}

qint32 CTcpServerWorker::selectUserHoldAccount( 
	quint16 nListenPort, QList<CUserHoldAccount*>& lstData, 
	const QString& strUserID, const QString& strSymbolUse )
{
	qint32 nFunRes = 0;
	CUserHoldAccount* pData = NULL;

	if (strSymbolUse.isEmpty())
	{
		m_pServerDbOper->selectUserHoldAccount(strUserID, lstData);
	} 
	else
	{
		m_pServerDbOper->selectUserHoldAccount(strUserID, strSymbolUse, &pData);
		if (NULL != pData)
		{
			lstData.push_back(pData);
			pData = NULL;
		}
	}//if

	return nFunRes;
}

