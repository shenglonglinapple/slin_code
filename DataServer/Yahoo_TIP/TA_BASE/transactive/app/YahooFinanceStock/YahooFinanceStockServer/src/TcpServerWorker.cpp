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
#include "UserAmount.h"

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
	nFunRes = m_pServerDbOper->selectUserInfo(nListenPort, strUSERNAME, strPASSWORD, ppData);
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
	nFunRes = m_pServerDbOper->updateUserInfo(nListenPort, pData);
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
	nFunRes = m_pServerDbOper->insertUserInfo(nListenPort, pData);
	return nFunRes;
}

qint32 CTcpServerWorker::createUserAmount( quint16 nListenPort, const CUserAmount* pData )
{
	qint32 nFunRes = 0;
	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->insertUserAmount(nListenPort, pData);
	return nFunRes;
}
qint32 CTcpServerWorker::_CreateUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->insertUserTradeInfo(nListenPort, pData);
	return nFunRes;
}

qint32 CTcpServerWorker::processUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData )
{
	CUserAmount* pUserAmount = NULL;
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
	nFunRes = m_pServerDbOper->selectUserAmount(nListenPort, pData->m_strUserID, &pUserAmount);
	if (NULL == pUserAmount)
	{
		MYLOG4CPP_ERROR<<"error:select User Amount m_strUserID="<<m_strUserID;
		nFunRes = -1;
		return nFunRes;
	}

	//
	if (CTcpComProtocol::ETradeType_Buy == pData->m_nTradeType)
	{
		//check
		if (pUserAmount->m_fLeftAmount >= pData->m_fTotalTradeAmount)
		{
			//check ok do trade
			pUserAmount->m_fLeftAmount = pUserAmount->m_fLeftAmount - pUserAmount->m_fUseAmount;
			_CreateUserTradeInfo(nListenPort, pData);
		}		
	}
	else //if (CTcpComProtocol::ETradeType_Sell == pData->m_nTradeType)
	{
		pUserAmount->m_fLeftAmount = pUserAmount->m_fLeftAmount + pData->m_fTotalTradeAmount;
		_CreateUserTradeInfo(nListenPort, pData);
	}
}

qint32 CTcpServerWorker::createUserHold( quint16 nListenPort, const CUserHold* pData )
{
	qint32 nFunRes = 0;
	if (NULL == m_pServerDbOper)
	{
		nFunRes = -1;
		return nFunRes;
	}
	nFunRes = m_pServerDbOper->insertUserHold(nListenPort, pData);
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
	nFunRes = m_pServerDbOper->selectUserTradeInfo(nListenPort, lstData, strUserID,strSymbolUse);

	return nFunRes;
}

