#include "DataProcessOrderWorker.h"

#include <list>
#include "ServerComManager.h"
#include "OrderData.h"
#include "DataOrderManager.h"
#include "QtTimeHelper.h"
#include "RealTimeStockManager.h"

#include "Log4cppLogger.h"


CDataProcessOrderWorker::CDataProcessOrderWorker(void)
{	
	m_toTerminate = false;
	m_WorkerState = WORK_STATE_BEGIN;
	m_nDataWorkerState = DataWorkerState_Begin;

	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
}

CDataProcessOrderWorker::~CDataProcessOrderWorker(void)
{
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}
}


void CDataProcessOrderWorker::run()
{
	m_WorkerState = WORK_STATE_BEGIN;
	m_nDataWorkerState = DataWorkerState_Begin;
	
	m_WorkerState = WORK_STATE_WORKING;
	while (false == m_toTerminate)
	{
		_ThreadJob();
		this->my_msleep(5000);
	}

	_ProcessUserTerminate();
	m_WorkerState = WORK_STATE_END;

}

void CDataProcessOrderWorker::terminate()
{
	m_toTerminate = true;

	while (WORK_STATE_END != m_WorkerState)
	{
		this->msleep(10);
	}
}


int CDataProcessOrderWorker::_ProcessUserTerminate()
{
	int nFunRes = 0;
	m_toTerminate = true;
	m_nDataWorkerState = DataWorkerState_End;
	return nFunRes;
}

bool CDataProcessOrderWorker::isFinishWork()
{
	bool bFinishWork = false;
	if (DataWorkerState_End == m_nDataWorkerState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CDataProcessOrderWorker::_ThreadJob()
{
	switch (m_nDataWorkerState)
	{
	case DataWorkerState_Begin:
		m_nDataWorkerState = DataWorkerState_ProcessOrder;
		break;
	case DataWorkerState_ProcessOrder:
		_DoJob_ProcessOrder();
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
void CDataProcessOrderWorker::_FreeData_ListOrderData(std::list<COrderData*>& lstMyOrderData)
{
	std::list<COrderData*>::iterator iterLst;
	COrderData* pData = NULL;

	iterLst = lstMyOrderData.begin();
	while (iterLst != lstMyOrderData.end())
	{
		pData = *iterLst;

		delete pData;
		pData = NULL;
		
		iterLst++;
	}
	lstMyOrderData.clear();
}

void CDataProcessOrderWorker::_DoJob_ProcessOrder()
{
	std::list<COrderData*> lstMyOrderData; 
	std::list<COrderData*>::iterator iterLst;
	COrderData* pData = NULL;

	CDataOrderManager::getInstance().getNotifyOrder(lstMyOrderData);


	iterLst = lstMyOrderData.begin();
	while (iterLst != lstMyOrderData.end())
	{
		pData = *iterLst;

		_ProcessOrder(pData);
		CServerComManager::getInstance().onOrderFilled(*pData);

		CDataOrderManager::getInstance().updateOrder(pData);
		iterLst++;
	}

	_FreeData_ListOrderData(lstMyOrderData);
	m_nDataWorkerState = DataWorkerState_ProcessOrder;
}
void CDataProcessOrderWorker::_ProcessOrder(COrderData* pData)
{
	if (NULL == pData)
	{
		return;
	}

	switch (pData->m_nOrderType)
	{
	case COrderData::MARKET:
		_ProcessOrder_MARKET(pData);
		break;
	default:
		break;
	}//switch

}
void CDataProcessOrderWorker::_ProcessOrder_MARKET(COrderData* pData)
{
	switch (pData->m_nSide)
	{
	case COrderData::BUY:
		_ProcessOrder_MARKET_BUY(pData);
		break;
	case COrderData::SELL:
		_ProcessOrder_MARKET_SELL(pData);
		break;
	default:
		break;
	}//switch
}
void CDataProcessOrderWorker::_ProcessOrder_MARKET_BUY(COrderData* pData)
{
	CMyInstrument* pMyInstrument = NULL;

	CRealTimeStockManager::getInstance().getRealTimeMyInstrument(pData->m_strInstrumentCode.toStdString(), &pMyInstrument);

	if (COrderData::NEW == pData->m_nOrderStatus)
	{
		pData->m_nOrderStatus = COrderData::FILLED;
		pData->m_nTransactTime = m_pQtTimeHelper->getTimeNow_Qt();
		pData->m_fTransactPrice = pMyInstrument->getLastPrice();
		pData->m_fFees = (pData->m_fTransactPrice * pData->m_nVolume) * 0.007;
		pData->m_fCurrentPrice = pData->m_fTransactPrice;
	}
	else if (COrderData::FILLED == pData->m_nOrderStatus)
	{
		pData->m_nOrderStatus = COrderData::FILLED;
		pData->m_nCurrentTime = m_pQtTimeHelper->getTimeNow_Qt();
		pData->m_fCurrentPrice = pMyInstrument->getLastPrice();
		pData->m_fTotal = ((pData->m_fCurrentPrice - pData->m_fTransactPrice) * pData->m_nVolume) - pData->m_fFees;
	}

	if (NULL != pMyInstrument)
	{
		delete pMyInstrument;
		pMyInstrument = NULL;
	}
}
void CDataProcessOrderWorker::_ProcessOrder_MARKET_SELL(COrderData* pData)
{
	CMyInstrument* pMyInstrument = NULL;

	CRealTimeStockManager::getInstance().getRealTimeMyInstrument(pData->m_strInstrumentCode.toStdString(), &pMyInstrument);

	if (COrderData::NEW == pData->m_nOrderStatus)
	{
		pData->m_nOrderStatus = COrderData::FILLED;
		pData->m_nTransactTime = m_pQtTimeHelper->getTimeNow_Qt();
		pData->m_fTransactPrice = pMyInstrument->getLastPrice();
		pData->m_fFees = (pData->m_fTransactPrice * pData->m_nVolume) * 0.007;
		pData->m_fCurrentPrice = pData->m_fTransactPrice;
	}
	else if (COrderData::FILLED == pData->m_nOrderStatus)
	{
		pData->m_nOrderStatus = COrderData::FILLED;
		pData->m_nCurrentTime = m_pQtTimeHelper->getTimeNow_Qt();
		pData->m_fCurrentPrice = pMyInstrument->getLastPrice();
		pData->m_fTotal = ((pData->m_fCurrentPrice - pData->m_fTransactPrice) * pData->m_nVolume) - pData->m_fFees;
	}


	if (NULL != pMyInstrument)
	{
		delete pMyInstrument;
		pMyInstrument = NULL;
	}
}
