#include "DataRealTimeWorker.h"

#include "MyTradeClient.h"

#include "RealTimeStockManager.h"


//////////////////////////////////////////////////////////////////////////
CDataRealTimeWorker::CDataRealTimeWorker(void)
{	
	m_toTerminate = false;
	m_nDataWorkerState = DataWorkerState_Begin;

	m_pMyTradeClientRef = NULL;
}

CDataRealTimeWorker::~CDataRealTimeWorker(void)
{
	m_pMyTradeClientRef = NULL;
}


void CDataRealTimeWorker::run()
{
	m_nDataWorkerState = DataWorkerState_Begin;

	while (false == m_toTerminate)
	{
		_ThreadJob();
		this->my_msleep(500);
	}

	_ProcessUserTerminate();
}

void CDataRealTimeWorker::terminate()
{
	m_toTerminate = true;
}


int CDataRealTimeWorker::_ProcessUserTerminate()
{
	int nFunRes = 0;
	m_toTerminate = true;
	m_nDataWorkerState = DataWorkerState_End;
	return nFunRes;
}

bool CDataRealTimeWorker::isFinishWork()
{
	bool bFinishWork = false;
	if (DataWorkerState_End == m_nDataWorkerState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CDataRealTimeWorker::_ThreadJob()
{
	switch (m_nDataWorkerState)
	{
	case DataWorkerState_Begin:
		m_nDataWorkerState = DataWorkerState_UpdateStockRealTimeInfo;
		break;
	case DataWorkerState_UpdateStockRealTimeInfo:
		_DoJob_UpdateStockRealTimeInfo();
		break;
	case DataWorkerState_End:
		this->my_msleep(100);
		break;
	default:
		this->my_msleep(100);
		break;
	}//switch (m_nDataWorkerState)

}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CDataRealTimeWorker::setDataProcessHandle( CMyTradeClient* pHandle )
{
	m_pMyTradeClientRef = pHandle;
}

void CDataRealTimeWorker::_DoJob_UpdateStockRealTimeInfo()
{
	std::list<CMyMarketData*> lstMyMarketData;
	std::list<CMyMarketData*>::iterator iterLst;
	CMyMarketData* pMyMarketData = NULL;

	CRealTimeStockManager::getInstance().getRealTimeMarketData(lstMyMarketData);

	iterLst = lstMyMarketData.begin();
	while (iterLst != lstMyMarketData.end())
	{
		pMyMarketData = (*iterLst);

		if (NULL != m_pMyTradeClientRef)
		{
			m_pMyTradeClientRef->onMarketDataUpdate(*pMyMarketData);
		}
		delete pMyMarketData;
		pMyMarketData = NULL;
		(*iterLst) = NULL;
		iterLst++;
	}//while
	lstMyMarketData.clear();

	m_nDataWorkerState = DataWorkerState_UpdateStockRealTimeInfo;
}
