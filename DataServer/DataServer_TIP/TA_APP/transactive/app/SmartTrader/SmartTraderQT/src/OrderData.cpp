#include "OrderData.h"

#include <QtCore/QStringList>
#include "Order.h"
#include "ItemUserInstrument.h"
#include "ItemUserInstrumentHelper.h"
#include "MyInstrument.h"
#include "DataTotalMyInstrument.h"

#include "Log4cppLogger.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////

COrderData::COrderData()
{
	_ClearData();
}

COrderData::~COrderData()
{
	_ClearData();
}


COrderData& COrderData::operator=( const COrderData& cParam )
{
	m_nInstrumentID = cParam.m_nInstrumentID;
	m_strInstrumentCode = cParam.m_strInstrumentCode;
	m_fLastPrice = cParam.m_fLastPrice;
	m_nQuantity = cParam.m_nQuantity;
	m_nSide = cParam.m_nSide;
	m_nOrderType = cParam.m_nOrderType;
	m_nCheckRes = cParam.m_nCheckRes;

	return *this;
}

void COrderData::_ClearData()
{
	m_nInstrumentID = 0;
	m_strInstrumentCode.clear();
	m_fLastPrice = 0;
	m_nQuantity = 0;
	m_nSide = CMyOrder::BUY;
	m_nOrderType = CMyOrder::MARKET;
	m_nCheckRes = OrderCheckRes_Cancel;

}

void COrderData::setDataByItem( CItemUserInstrument* pData )
{
	CItemUserInstrumentHelper* pItemUserInstrumentHelper = NULL;
	CMyInstrument* pMyInstrumentRef = NULL;

	_ClearData();
	if (NULL == pData)
	{
		return;
	}

	m_nInstrumentID = pData->getNodeKey();

	pMyInstrumentRef = NULL;
	pMyInstrumentRef = CDataTotalMyInstrument::getInstance().findInstrumentByID(m_nInstrumentID);

	if (NULL == pMyInstrumentRef)
	{
		return;
	}
	
	pItemUserInstrumentHelper = new CItemUserInstrumentHelper();
	pItemUserInstrumentHelper->setValue(*pMyInstrumentRef);
	
	//m_nInstrumentID = pItemUserInstrumentHelper->getInstrumentID();
	m_strInstrumentCode = pItemUserInstrumentHelper->getInstrumentCode();
	m_fLastPrice = pItemUserInstrumentHelper->m_fLastTradePrice;
	m_nQuantity = 1;

	if (NULL != pItemUserInstrumentHelper)
	{
		delete pItemUserInstrumentHelper;
		pItemUserInstrumentHelper = NULL;
	}

}






