#include "UserOrderInfo.h"

#include <QtCore/QStringList>
#include "Order.h"
#include "Instrument.h"
#include "Account.h"
#include "OrderInfo.h"
#include "TreeItemQuotes.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////

CUserOrderInfo::CUserOrderInfo()
{
	m_pOrderInfo = NULL;
	m_pOrderInfo = new COrderInfo();
	_ClearData();

	

}

CUserOrderInfo::~CUserOrderInfo()
{
	if (NULL != m_pOrderInfo)
	{
		delete m_pOrderInfo;
		m_pOrderInfo = NULL;
	}
}


CUserOrderInfo& CUserOrderInfo::operator=( const CUserOrderInfo& cParam )
{




	return *this;
}

void CUserOrderInfo::_ClearData()
{
	

}

void CUserOrderInfo::setDataByItem( CTreeItemQuotes* pData )
{
	m_nInstrumentID = pData->getInstrumentID();
	m_strExchangeName = pData->getExchangeName();
	m_strInstrumentCode = pData->getInstrumentCode();
	m_fLastPrice = pData->getLastPrice();
	m_nVolume = 1;

}






