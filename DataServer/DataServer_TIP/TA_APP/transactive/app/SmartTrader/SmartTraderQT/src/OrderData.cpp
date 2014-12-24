#include "OrderData.h"

#include <QtCore/QStringList>
#include "ProjectCommonData.h"
#include "ItemUserInstrument.h"
#include "ItemUserInstrumentHelper.h"
#include "MyInstrument.h"
#include "DataTotalMyInstrument.h"

#include "Log4cppLogger.h"


//////////////////////////////////////////////////////////////////////////

COrderData::COrderData()
{
	clearData();
}

COrderData::~COrderData()
{
	clearData();
}


COrderData& COrderData::operator=( const COrderData& cParam )
{
	m_strUUID = cParam.m_strUUID;
	m_nInstrumentID = cParam.m_nInstrumentID;
	m_strInstrumentCode = cParam.m_strInstrumentCode;
	m_nVolume = cParam.m_nVolume;
	m_nSide = cParam.m_nSide;
	m_nOrderType = cParam.m_nOrderType;
	m_nOrderConfirm = cParam.m_nOrderConfirm;

	m_fTransactPrice = cParam.m_fTransactPrice;
	m_fFees = cParam.m_fFees;
	m_fCurrentPrice = cParam.m_fCurrentPrice;
	m_fTotal = cParam.m_fTotal;
	m_nOrderStatus = cParam.m_nOrderStatus;
	m_nTransactTime = cParam.m_nTransactTime;
	m_nCurrentTime = cParam.m_nCurrentTime;


	return *this;
}


void COrderData::clearData()
{
	m_strUUID.clear();
	m_nInstrumentID = 0;
	m_strInstrumentCode.clear();
	m_nVolume = 0;
	m_nSide = BUY;
	m_nOrderType = MARKET;
	m_nOrderConfirm = OrderConfirm_Cancel;

	m_fTransactPrice = 0;
	m_fFees = 0;
	m_fCurrentPrice = 0;
	m_fTotal = 0;
	m_nOrderStatus = NEW;
	m_nTransactTime = 0;
	m_nCurrentTime = 0;

}

void COrderData::setBaseData( CItemUserInstrument* pData )
{
	CItemUserInstrumentHelper* pItemUserInstrumentHelper = NULL;
	CMyInstrument* pMyInstrumentRef = NULL;

	clearData();
	if (NULL == pData)
	{
		return;
	}
	m_strUUID.clear();
	//m_nInstrumentID
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
	m_fCurrentPrice = pItemUserInstrumentHelper->m_fLastTradePrice;
	m_nVolume = 1;

	if (NULL != pItemUserInstrumentHelper)
	{
		delete pItemUserInstrumentHelper;
		pItemUserInstrumentHelper = NULL;
	}

	MYLOG4CPP_DEBUG<<"COrderData::setBaseData"
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode.toStdString()
		<<" "<<"m_fCurrentPrice="<<m_fCurrentPrice
		<<" "<<"m_nVolume="<<m_nVolume;
}


QString COrderData::getESide(COrderData::ESide  nSide)
{
	QString strValue;

	switch (nSide)
	{
	case BUY:
		strValue = "BUY";
		break;
	case SELL:
		strValue = "SELL";
		break;
	default:
		strValue = "UNKNOWN";
		break;
	}

	return strValue;

}

COrderData::EOrderType COrderData::getEOrderType( const QString& strOrderType )
{
	QString strOrderTypeTmp;
	QString strCheckTmp;
	COrderData::EOrderType nOrderType = UNKNOWN;
	strOrderTypeTmp = strOrderType;
	strOrderTypeTmp = strOrderTypeTmp.toUpper();

	strCheckTmp = DEFVALUE_String_OrderType_MARKET.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = COrderData::MARKET;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_MARKET_FAK.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = COrderData::MARKET_FAK;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_MARKET_FOK.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = COrderData::MARKET_FOK;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_LIMIT.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = COrderData::LIMIT;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_LIMIT_FAK.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = COrderData::LIMIT_FAK;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_LIMIT_FOK.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = COrderData::LIMIT_FOK;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_STOP.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = COrderData::STOP;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_UNKNOWN.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = COrderData::UNKNOWN;
		return nOrderType;
	}

	return nOrderType;
}


QString COrderData::getEOrderType(COrderData::EOrderType nOrderType)
{
	QString strValue;

	switch (nOrderType)
	{
	case COrderData::MARKET:
		strValue = DEFVALUE_String_OrderType_MARKET.c_str();
		break;
	case COrderData::MARKET_FAK:
		strValue = DEFVALUE_String_OrderType_MARKET_FAK.c_str();
		break;
	case COrderData::MARKET_FOK:
		strValue = DEFVALUE_String_OrderType_MARKET_FOK.c_str();
		break;
	case COrderData::LIMIT:
		strValue = DEFVALUE_String_OrderType_LIMIT.c_str();
		break;
	case COrderData::LIMIT_FAK:
		strValue = DEFVALUE_String_OrderType_LIMIT_FAK.c_str();
		break;
	case COrderData::LIMIT_FOK:
		strValue = DEFVALUE_String_OrderType_LIMIT_FOK.c_str();
		break;
	case COrderData::STOP:
		strValue = DEFVALUE_String_OrderType_STOP.c_str();
		break;
	case COrderData::UNKNOWN:
		strValue = DEFVALUE_String_OrderType_UNKNOWN.c_str();
		break;
	default:
		strValue = DEFVALUE_String_OrderType_UNKNOWN.c_str();
		break;
	}

	return strValue;

}




