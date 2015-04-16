#include "ClientManager.h"
#include "ClientWorkerForTest.h"
#include "HelpClass.h"
#include "ConfigInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;



using namespace TA_Base_Test;

NS_BEGIN(TA_Base_Test) 




CClientManager::CClientManager( int nClientIndex )
{
	strServerAddress = CConfigInfo::getInstance().getServerAddress();
	m_pClientWorkerForTest = NULL;
	m_pClientWorkerForTest = new CClientWorkerForTest(nClientIndex);
	m_pClientWorkerForTest->setClientManagerHandle(this);
	m_pClientWorkerForTest->start();
}

CClientManager::~CClientManager( void )
{
	if (NULL != m_pClientWorkerForTest)
	{
		m_pClientWorkerForTest->terminateAndWait();
		delete m_pClientWorkerForTest;
		m_pClientWorkerForTest = NULL;
	}

}


void CClientManager::handleConnected( const SessionInfo &stSessionInfo )
{
	m_pClientWorkerForTest->handleConnected(stSessionInfo);
}

void CClientManager::handleDisconnected( const SessionInfo &stSessionInfo )
{
	m_pClientWorkerForTest->handleDisconnected(stSessionInfo);

}

void CClientManager::handleReceivedMessage( Message::Ptr pGetMessage )
{
	m_pClientWorkerForTest->handleReceivedMessage(pGetMessage);

}

void CClientManager::handleDeliverFailure( Message::Ptr pGetMessage )
{
	m_pClientWorkerForTest->handleDeliverFailure(pGetMessage);

}


int CClientManager::initClient()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;


	{
		boost::mutex::scoped_lock lock(m_mutexBrokerClient);
		m_BrokerClient.onConnected = boost::bind(&TA_Base_Test::CClientManager::handleConnected, this, _1);//static boost::arg<1> _1;
		m_BrokerClient.onDisconnected = boost::bind(&TA_Base_Test::CClientManager::handleDisconnected, this, _1);//static boost::arg<1> _1;
		m_BrokerClient.onReceived = boost::bind(&TA_Base_Test::CClientManager::handleReceivedMessage, this, _1);//static boost::arg<1> _1;
		m_BrokerClient.onDeliverFailure = boost::bind(&TA_Base_Test::CClientManager::handleDeliverFailure, this, _1);//static boost::arg<1> _1;

	}

	return nFunRes;
}


int CClientManager::connectToServer()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;

	{
		boost::mutex::scoped_lock lock(m_mutexBrokerClient);

		LOG_INFO<< "begin connect to strServerAddress="<<strServerAddress;
		m_BrokerClient.connect(strServerAddress);
	}

	return nFunRes;
}


int CClientManager::sendData( const cms::SessionID& destSessionID, cms::Message::Ptr pMessage )
{
	int nFunRes = 0;

	{
		boost::mutex::scoped_lock lock(m_mutexBrokerClient);
		m_BrokerClient.sendToSession(destSessionID, pMessage);
	}

	return nFunRes;
}

int CClientManager::disConnectToServer(const cms::SessionID& destSessionID)
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;

	{
		boost::mutex::scoped_lock lock(m_mutexBrokerClient);

		LOG_INFO<< "disConnectToServer to strServerAddress="<<strServerAddress;
		m_BrokerClient.closeSession(destSessionID);
	}

	return nFunRes;
}


bool CClientManager::isFinishWork()
{
	BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	bFinishWork = m_pClientWorkerForTest->isFinishWork();
	return bFinishWork;

}


NS_END(TA_Base_Test) 



