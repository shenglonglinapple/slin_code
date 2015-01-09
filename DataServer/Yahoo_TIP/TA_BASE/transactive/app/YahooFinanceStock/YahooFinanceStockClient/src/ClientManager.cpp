#include "ClientManager.h"
#include "DistributeTaskWorker.h"

CClientManager::CClientManager( QObject* parent )
{

}

CClientManager::~CClientManager( void )
{

}

void CClientManager::createClient(int nCount)
{
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		CDistributeTaskWorker* pActor = NULL;
		pActor = new CDistributeTaskWorker("UserName","PassWord","127.0.0.1", 5000, NULL);
		QObject::connect(pActor, SIGNAL(signalDeleteConnection(CDistributeTaskWorker*)), this, SLOT(slotDeleteConnection(CDistributeTaskWorker*)), Qt::AutoConnection);
		pActor->start();
	}

}
void CClientManager::slotDeleteConnection( CDistributeTaskWorker* pActor )
{
	if (NULL != pActor)
	{
		pActor->terminateAndWait();
		delete pActor;
		pActor = NULL;
	}

}

