#include "ClientManager.h"
#include "StockTcpClientActor.h"

CClientManager::CClientManager( QObject* parent )
{

}

CClientManager::~CClientManager( void )
{

}

void CClientManager::createClient(int nCount)
{
	CStockTcpClientActor* pActor = NULL;
	pActor = new CStockTcpClientActor(NULL);
	QObject::connect(pActor, SIGNAL(signalDeleteConnection(CStockTcpClientActor*)), 
		this, SLOT(slotDeleteConnection(CStockTcpClientActor*)), Qt::AutoConnection);

	pActor->start();
	//pClient->connectToServer("192.168.253.130", 5000);

}
void CClientManager::slotDeleteConnection( CStockTcpClientActor* pActor )
{
	if (NULL != pActor)
	{
		pActor->terminateAndWait();
		delete pActor;
		pActor = NULL;
	}

}

