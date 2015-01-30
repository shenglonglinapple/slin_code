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
	m_pServerDbOper = new CServerDbOper(QString("%1.db").arg(m_nListenPort));//5001.db

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
qint32 CTcpServerWorker::processUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	CUserHoldAccount* pUserHoldAmount_check = NULL;
	CUserHoldAccount* pUserHoldAmount_current_symbol = NULL;
	CUserHoldAccount* pUserHoldAmount_user = NULL;
	CUserAccount* pUserAccount = NULL;
	double fLeftAccount = 0;
	double fHoldAccount = 0;

	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	if (NULL == pData || pData->m_strUserID.isEmpty())
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->selectUserAccount(pData->m_strUserID, &pUserAccount);
	if (NULL == pUserAccount)
	{
		MYLOG4CPP_ERROR<<"error:select User Amount m_strUserID="<<pData->m_strUserID;
		nFunRes = -1;
		return nFunRes;
	}
	fLeftAccount = pUserAccount->m_fLeftAccount;

	nFunRes = m_pServerDbOper->selectUserHoldAccount(pData->m_strUserID,pData->m_strSymbolUse, &pUserHoldAmount_check);
	//
	if (CTcpComProtocol::ETradeType_Buy == pData->m_nTradeType)
	{
		if (fLeftAccount < pData->m_fUseAccount)
		{
			MYLOG4CPP_ERROR<<"error: money is not enough m_strUserID="<<pData->m_strUserID
				<<" "<<"fLeftAccount="<<fLeftAccount
				<<" "<<"<"
				<<" "<<"m_fUseAccount="<<pData->m_fUseAccount;
			nFunRes = -1;
			return nFunRes;
		}
		if (NULL == pUserHoldAmount_check)
		{
			//first buy insert one
			pUserHoldAmount_check = new CUserHoldAccount();
			pUserHoldAmount_check->setValue_FirstBuy(pData);
			m_pServerDbOper->insertUserHoldAccount(pUserHoldAmount_check);
			delete pUserHoldAmount_check;
			pUserHoldAmount_check = NULL;			
		}
		fLeftAccount -= pData->m_fUseAccount;
	}
	else
	{
		if (NULL == pUserHoldAmount_check)
		{
			MYLOG4CPP_ERROR<<"error: user not have Quote to sell! m_strUserID="<<pData->m_strUserID
				<<" "<<"m_strSymbolUse="<<pData->m_strSymbolUse;
			nFunRes = -1;
			return nFunRes;
		}
		fLeftAccount += pData->m_fUseAccount;
	}

	//select again
	nFunRes = m_pServerDbOper->selectUserHoldAccount(pData->m_strUserID, pData->m_strSymbolUse, &pUserHoldAmount_current_symbol);
	if (NULL == pUserHoldAmount_current_symbol)
	{
		MYLOG4CPP_ERROR<<"error: not find User Hold Amount m_strUserID="<<pData->m_strUserID
			<<" "<<"m_strSymbolUse="<<pData->m_strSymbolUse;
		nFunRes = -1;
		return nFunRes;
	}

	//do
	m_pServerDbOper->startTransaction();
	nFunRes = m_pServerDbOper->insertUserTradeInfo(pData);//trade
	pUserHoldAmount_current_symbol->updateHoldAmountValue(pData);//hold
	nFunRes = m_pServerDbOper->updateUserHoldAccount(pUserHoldAmount_current_symbol);//hold

	fHoldAccount = getUserHoldAmount(pData->m_strUserID, pData->m_strTradeTime);//hold total
	pUserAccount->updateLeftAccount(fLeftAccount, pData->m_strTradeTime);//
	pUserAccount->updateHoldAccount(fHoldAccount, pData->m_strTradeTime);
	nFunRes = m_pServerDbOper->updateUserAccount(pUserAccount);
	m_pServerDbOper->commitTransaction();

	if (NULL == pUserAccount)
	{
		delete pUserAccount;
		pUserAccount = NULL;
	}
	if (NULL != pUserHoldAmount_current_symbol)
	{
		delete pUserHoldAmount_current_symbol;
		pUserHoldAmount_current_symbol = NULL;
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

