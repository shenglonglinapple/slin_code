#include "CreateReqHelper.h"

#include <QtCore/QStringList>
#include <QtCore/QByteArray>

#include "TcpComProtocol.h"

#include "ReqCreateUser.h"
#include "ReqLogin.h"
#include "ReqLogout.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"
#include "ReqStockMinTimeMaxTime.h"
#include "ReqStockHistoryData.h"
#include "ReqTrade.h"
#include "ReqHistoryTrade.h"
#include "ReqAccount.h"
#include "ReqHoldAccount.h"

#include "StockMinTimeMaxTime.h"
#include "UserTradeInfo.h"
#include "UserAccount.h"
#include "HistoryData.h"
#include "Log4cppLogger.h"


CCreateReqHelper::CCreateReqHelper(void)
{


}

CCreateReqHelper::~CCreateReqHelper(void)
{
	
}


QByteArray* CCreateReqHelper::create_req_ReqSynYahoo(qint32 nHandle, const QString& strSymbolUse)
{
	QByteArray* pByteArray = NULL;

	CReqSynYahoo* pReq = NULL;
	pReq = new CReqSynYahoo();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strSymbolUse = strSymbolUse;//"000001.SZ";
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}

	return pByteArray;
}




QByteArray* CCreateReqHelper::create_req_ReqDownLoadStock(qint32 nHandle)
{
	QByteArray* pByteArray = NULL;
	CReqDownLoadStock* pReq = NULL;
	pReq = new CReqDownLoadStock();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}
QByteArray* CCreateReqHelper::create_req_ReqCreateUser( qint32 nHandle, const QString& strUserName, const QString& strPassWord )
{
	QByteArray* pByteArray = NULL;
	CReqCreateUser* pReq = NULL;
	pReq = new CReqCreateUser();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserName = strUserName;
	pReq->m_strPassword = strPassWord;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}

QByteArray* CCreateReqHelper::create_req_ReqLogin(qint32 nHandle, const QString& strUserName, const QString& strPassWord)
{
	QByteArray* pByteArray = NULL;

	CReqLogin* pReq = NULL;
	pReq = new CReqLogin();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserName = strUserName;
	pReq->m_strPassword = strPassWord;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}



QByteArray* CCreateReqHelper::create_req_ReqStockMinTimeMaxTime(qint32 nHandle, const QString& strSymbolUse)
{
	QByteArray* pByteArray = NULL;

	CReqStockMinTimeMaxTime* pReq = NULL;
	pReq = new CReqStockMinTimeMaxTime();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strSymbolUse = strSymbolUse;//"000001.SZ";
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}


QByteArray* CCreateReqHelper::create_req_ReqStockHistoryData(const QString& strSymbolUse, const QString& strTimeFrom, const QString& strTimeTo)
{
	QByteArray* pByteArray = NULL;

	CReqStockHistoryData* pReq = NULL;
	pReq = new CReqStockHistoryData();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strSymbolUse = strSymbolUse;//"000001.SZ";
	pReq->m_strTimeFrom = strTimeFrom;
	pReq->m_strTimeTo = strTimeTo;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}

QByteArray* CCreateReqHelper::create_req_NewOrder( const CUserTradeInfo* pData )
{
	QByteArray* pByteArray = NULL;
	CReqTrade* pReq = NULL;
	pReq = new CReqTrade();
	pReq->setValue(pData);
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}
QByteArray* CCreateReqHelper::create_req_ReqHistoryTrade(const QString& strUserID, const QString& strSymbolUse, CTcpComProtocol::ETradeType nTradeType )
{
	QByteArray* pByteArray = NULL;
	CReqHistoryTrade* pReq = NULL;
	pReq = new CReqHistoryTrade();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserID = strUserID;//set User ID
	pReq->m_nTradeType = (CTcpComProtocol::ETradeType)nTradeType;
	pReq->m_strSymbolUse = strSymbolUse;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}

QByteArray* CCreateReqHelper::create_req_ReqUserAccount(const QString& strUserID, const QString& strTime)
{
	QByteArray* pByteArray = NULL;
	CReqAccount* pReq = NULL;
	pReq = new CReqAccount();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserID = strUserID;//set User ID
	pReq->m_strTime = strTime;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}

QByteArray* CCreateReqHelper::create_req_ReqUserHoldAccount( const QString& strUserID, const QString& strSymbolUse )
{
	QByteArray* pByteArray = NULL;
	CReqHoldAccount* pReq = NULL;
	pReq = new CReqHoldAccount();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserID = strUserID;//set User ID
	pReq->m_strSymbolUse = strSymbolUse;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();
	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
	return pByteArray;
}






