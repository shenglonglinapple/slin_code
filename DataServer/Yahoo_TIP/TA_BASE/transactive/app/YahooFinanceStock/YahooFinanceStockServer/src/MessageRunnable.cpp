#include "MessageRunnable.h"

#include <QtCore/QDataStream>
#include <QtCore/QList>

#include "TcpComProtocol.h"
#include "ReqLogin.h"
#include "ReqLogout.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"
#include "ReqStockMinTimeMaxTime.h"
#include "ReqStockHistoryData.h"

#include "AckLogin.h"
#include "AckLogout.h"
#include "AckSynYahoo.h"
#include "AckDownLoadStock.h"
#include "AckStockMinTimeMaxTime.h"
#include "AckStockHistoryData.h"

#include "MessageManager.h"

#include "Log4cppLogger.h"

#include "ProjectEnvironment.h"
#include "YahooDataLoader.h"
#include "StockDataManager.h"
#include "StockMinTimeMaxTime.h"
#include "HistoryData.h"

CMessageRunnable::CMessageRunnable(qint32 nHanle, QByteArray* pMessage)
{
	m_nHanle = 0;
	m_pMessage = NULL;
	pMessageManagerRef = NULL;

	m_nHanle = nHanle;
	m_pMessage = pMessage;
}

CMessageRunnable::~CMessageRunnable()
{
	if (NULL != m_pMessage)
	{
		delete m_pMessage;
		m_pMessage = NULL;
	}
	pMessageManagerRef = NULL;
}


void CMessageRunnable::setHanle( CMessageManager* pHanleRef )
{
	pMessageManagerRef = pHanleRef;
}


void CMessageRunnable::run()
{
	MYLOG4CPP_DEBUG<<"CMessageRunnable::run() begin";

	_ProcessMessage();

	MYLOG4CPP_DEBUG<<"CMessageRunnable::run() end";
}

void CMessageRunnable::_ProcessMessage()
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CMessageRunnable"
		<<" "<<"fun:"<<" "<<"_ProcessMessage"
		<<" "<<"param:"<<" "<<"m_nHanle="<<m_nHanle
		<<" "<<"param:"<<" "<<"m_pMessage=0x"<<m_pMessage;

	QDataStream readMessageBuffer(*m_pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;

	if (CTcpComProtocol::MsgType_Req == nMessageType)
	{
		_ProcessMessage_Req(nMessageType, nDataType);
	}
	else if (CTcpComProtocol::MsgType_Ack == nMessageType)
	{
		_ProcessMessage_Ack(nMessageType, nDataType);
	}


}


void CMessageRunnable::_ProcessMessage_Req(qint32 nMessageType, qint32 nDataType )
{

	if (CReqLogin::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqLogin();
	}	
	else if (CReqLogout::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqLogout();		
	}
	else if (CReqSynYahoo::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqSynYahoo();		
	}
	else if (CReqDownLoadStock::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqDownLoadStock();		
	}
	else if (CReqStockMinTimeMaxTime::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqStockMinTimeMaxTime();		
	}
	else if (CReqStockHistoryData::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqStockHistoryData();		
	}
	
}

void CMessageRunnable::_ProcessMessage_ReqLogin()
{
	CReqLogin* pReqLogin = NULL;
	pReqLogin = new CReqLogin();
	pReqLogin->setValue(m_pMessage);
	pReqLogin->logInfo(__FILE__, __LINE__);

	_ProcessReq(pReqLogin);

	if (NULL != pReqLogin)
	{
		delete pReqLogin;
		pReqLogin = NULL;
	}
}
void CMessageRunnable::_ProcessMessage_ReqLogout()
{
	CReqLogout* pReqLogout = NULL;
	pReqLogout = new CReqLogout();
	pReqLogout->setValue(m_pMessage);
	pReqLogout->logInfo(__FILE__, __LINE__);

	_ProcessReq(pReqLogout);

	if (NULL != pReqLogout)
	{
		delete pReqLogout;
		pReqLogout = NULL;
	}

}
void CMessageRunnable::_ProcessMessage_ReqSynYahoo()
{
	CReqSynYahoo* pReq = NULL;
	pReq = new CReqSynYahoo();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	_ProcessReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}
void CMessageRunnable::_ProcessMessage_ReqDownLoadStock()
{
	CReqDownLoadStock* pReq = NULL;
	pReq = new CReqDownLoadStock();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	_ProcessReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}
void CMessageRunnable::_ProcessMessage_ReqStockMinTimeMaxTime()
{
	CReqStockMinTimeMaxTime* pReq = NULL;
	pReq = new CReqStockMinTimeMaxTime();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	_ProcessReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_ReqStockHistoryData()
{
	CReqStockHistoryData* pReq = NULL;
	pReq = new CReqStockHistoryData();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	_ProcessReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CMessageRunnable::_ProcessMessage_Ack(qint32 nMessageType, qint32 nDataType )
{
	if (CAckLogin::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckLogin();
	}	
	else if (CAckLogout::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckLogout();
	}
	else if (CAckSynYahoo::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckSynYahoo();
	}
	else if (CAckDownLoadStock::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckDownLoadStock();		
	}
	else if (CAckStockMinTimeMaxTime::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckStockMinTimeMaxTime();		
	}
	else if (CAckStockHistoryData::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckStockHistoryData();		
	}
}

void CMessageRunnable::_ProcessMessage_AckLogin()
{
	CAckLogin* pAck = NULL;
	pAck = new CAckLogin();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	this->_ProcessAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckLogout()
{
	CAckLogout* pAck = NULL;
	pAck = new CAckLogout();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	this->_ProcessAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}
void CMessageRunnable::_ProcessMessage_AckSynYahoo()
{
	CAckSynYahoo* pAck = NULL;
	pAck = new CAckSynYahoo();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	this->_ProcessAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}


void CMessageRunnable::_ProcessMessage_AckDownLoadStock()
{
	CAckDownLoadStock* pAck = NULL;
	pAck = new CAckDownLoadStock();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	this->_ProcessAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckStockMinTimeMaxTime()
{
	CAckStockMinTimeMaxTime* pAck = NULL;
	pAck = new CAckStockMinTimeMaxTime();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	this->_ProcessAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}


void CMessageRunnable::_ProcessMessage_AckStockHistoryData()
{
	CAckStockHistoryData* pAck = NULL;
	pAck = new CAckStockHistoryData();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	this->_ProcessAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void CMessageRunnable::_ProcessReq(const CReqLogin* pReq )
{
	CAckLogin* pAckLogin = NULL;
	QByteArray* pByteArray = NULL;


	pAckLogin = new CAckLogin();

	pAckLogin->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAckLogin->m_nDataType = CTcpComProtocol::DataType_Login;
	pAckLogin->m_strACKUUID = CTcpComProtocol::getUUID();
	pAckLogin->m_strReqUUID = pReq->m_strReqUUID;
	pAckLogin->m_strUserName = pReq->m_strUserName;
	pAckLogin->m_strPassword = pReq->m_strPassword;
	pAckLogin->m_nLoginResult = CTcpComProtocol::DataType_LoginResult_OK;
	pByteArray = pAckLogin->getMessage();
	pAckLogin->logInfo(__FILE__, __LINE__);

	pMessageManagerRef->sendMessage(m_nHanle, pByteArray);


	pByteArray = NULL;
	if (NULL != pAckLogin)
	{
		delete pAckLogin;
		pAckLogin = NULL;
	}
	
}

void CMessageRunnable::_ProcessReq( const CReqLogout* pReq )
{
	CAckLogout* pAckLogout = NULL;
	QByteArray* pByteArray = NULL;

	pAckLogout = new CAckLogout();

	pAckLogout->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAckLogout->m_nDataType = CTcpComProtocol::DataType_LogOut;
	pAckLogout->m_strACKUUID = CTcpComProtocol::getUUID();
	pAckLogout->m_strReqUUID = pReq->m_strReqUUID;
	pAckLogout->m_strUserName = pReq->m_strUserName;
	pAckLogout->m_strPassword = pReq->m_strPassword;
	pAckLogout->m_nLogoutResult = CTcpComProtocol::DataType_LogoutResult_OK;

	pByteArray = pAckLogout->getMessage();
	pAckLogout->logInfo(__FILE__, __LINE__);

	pMessageManagerRef->sendMessage(m_nHanle, pByteArray);


	pByteArray = NULL;
	if (NULL != pAckLogout)
	{
		delete pAckLogout;
		pAckLogout = NULL;
	}
}

void CMessageRunnable::_ProcessReq( const CReqSynYahoo* pReq )
{
	CAckSynYahoo* pAck = NULL;
	QByteArray* pByteArray = NULL;
	CYahooDataLoader* pYahooDataLoader = NULL;
	CTcpComProtocol::EDataTypeSynYahooResult nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_SynYahooStart;

	pYahooDataLoader = new CYahooDataLoader(pReq->m_strSymbolUse);

	pAck = new CAckSynYahoo();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_SynYahoo;
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	pAck->m_nResult = nSynYahooResult;
	pAck->logInfo(__FILE__, __LINE__);
	pByteArray = pAck->getMessage();
	pMessageManagerRef->sendMessage(m_nHanle, pByteArray);
	pYahooDataLoader->synDataWithYahoo();

	while (1)
	{
		CProjectEnviroment::getInstance().qtWaitTime(300);
		nSynYahooResult = pYahooDataLoader->getState_SynDataWithYahoo();
		pAck->m_strACKUUID = CTcpComProtocol::getUUID();
		pAck->m_nResult = nSynYahooResult;
		pAck->logInfo(__FILE__, __LINE__);
		pByteArray = pAck->getMessage();
		pMessageManagerRef->sendMessage(m_nHanle, pByteArray);
		pByteArray = NULL;

		if (CTcpComProtocol::DataType_SynYahooResult_SynYahooFinished == nSynYahooResult
			|| CTcpComProtocol::DataType_SynYahooResult_ERROR == nSynYahooResult)
		{
			break;//while
		}
	}//while

	if (NULL != pYahooDataLoader)
	{
		delete pYahooDataLoader;
		pYahooDataLoader = NULL;
	}
	
	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}


}

void CMessageRunnable::_ProcessReq(const CReqDownLoadStock* pReq)
{
	CAckDownLoadStock* pAck = NULL;
	QByteArray* pByteArray = NULL;

	pAck = new CAckDownLoadStock();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_DownLoadStock;
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	CStockDataManager::getInstance().doWork_getStockSymbolUse(pAck->m_LstStock);
	pAck->m_nStockCount = pAck->m_LstStock.size();
	pAck->logInfo(__FILE__, __LINE__);
	pByteArray = pAck->getMessage();
	pMessageManagerRef->sendMessage(m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}

}

void CMessageRunnable::_ProcessReq( const CReqStockMinTimeMaxTime* pReq )
{
	CAckStockMinTimeMaxTime* pAck = NULL;
	QByteArray* pByteArray = NULL;
	CStockMinTimeMaxTime* pValueGet = NULL;
	
	CStockDataManager::getInstance().doWork_getStockMinTimeMaxTime(pReq->m_strSymbolUse, &pValueGet);

	if (NULL == pValueGet)
	{
		//not get data
		MYLOG4CPP_ERROR<<"_ProcessReq CReqStockMinTimeMaxTime"
			<<" "<<"not get data for pReq->m_strSymbolUse="<<pReq->m_strSymbolUse;
		return;
	}
	else
	{

	}

	pAck = new CAckStockMinTimeMaxTime();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_StockMinTimeMaxTime;
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	pAck->m_strSymbolUse = pValueGet->m_strSymbolUse;
	pAck->m_strMinTime = pValueGet->m_strMinTime;
	pAck->m_strMaxTime = pValueGet->m_strMaxTime;
	pAck->m_nCount = pValueGet->m_nCount;

	if (NULL == pValueGet)
	{
		delete pValueGet;
		pValueGet = NULL;
	}

	pAck->logInfo(__FILE__, __LINE__);
	pByteArray = pAck->getMessage();
	pMessageManagerRef->sendMessage(m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}

}

void CMessageRunnable::_ProcessReq( const CReqStockHistoryData* pReq )
{
	CAckStockHistoryData* pAck = NULL;
	QByteArray* pByteArray = NULL;
	QList<CHistoryData*> lstData;
	
	CStockDataManager::getInstance().doWork_HistoryData(pReq->m_strSymbolUse, pReq->m_strTimeFrom, pReq->m_strTimeTo, lstData);

	pAck = new CAckStockHistoryData();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_HistoryData;
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	pAck->m_strSymbolUse = pReq->m_strSymbolUse;
	pAck->m_nDataCount = lstData.size();
	pAck->m_LstHistoryData.append(lstData);
	lstData.clear();

	pAck->logInfo(__FILE__, __LINE__);
	pByteArray = pAck->getMessage();
	pMessageManagerRef->sendMessage(m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
void CMessageRunnable::_ProcessAck( const CAckLogin* pAck )
{
	return;
}

void CMessageRunnable::_ProcessAck( const CAckLogout* pAck )
{
	return;
}

void CMessageRunnable::_ProcessAck( const CAckSynYahoo* pAck )
{
	return;
}

void CMessageRunnable::_ProcessAck(const CAckDownLoadStock* pAck)
{
	return;
}

void CMessageRunnable::_ProcessAck( const CAckStockMinTimeMaxTime* pAck )
{
	return;
}

void CMessageRunnable::_ProcessAck( const CAckStockHistoryData* pAck )
{

}
