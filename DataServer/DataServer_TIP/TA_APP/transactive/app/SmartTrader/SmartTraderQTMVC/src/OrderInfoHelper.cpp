#include "OrderInfoHelper.h"

#include "Bar.h"
#include "Order.h"
#include "Account.h"
#include "Currency.h"
#include "Instrument.h"
#include "MarketData.h"

#include <QtCore/QStringList>


#include "ProjectCommonData.h"
#include "ProjectUtilityFun.h"

#include "Log4cppLogger.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


static const std::string DEFVALUE_String_ColumnName_Data_Key = "Key";//

//活动订单
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderID = "OrderID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderType = "OrderType";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_TIF = "TIF";//有效时间
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderStatus = "OrderStatus";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Exchange = "Exchange";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_InstrumentCode = "InstrumentCode";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Account = "Account";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_BuyOrSell = "Buy/Sell";//Side
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Lots = "Lots";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price = "Price";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price2 = "Price2";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Filled = "Filled";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_AvgPrice = "AvgPrice";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_TransactTime = "TransactTime";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_RejectReason = "RejectReason";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Column_Fees = "Fees";//手续费
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Column_Margin = "Margin";//保证金
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Column_Currency = "Currency";//货币//"CNY"
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Column_Contract = "Contract";//合约//"SHFE/ag1409"


//////////////////////////////////////////////////////////////////////////

COrderInfo::COrderInfo()
{

	_ClearData();

	

	m_pUtilityFun = NULL;
	m_pUtilityFun = new CProjectUtilityFun();

}

COrderInfo::~COrderInfo()
{
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}

}


COrderInfo& COrderInfo::operator=( const COrderInfo& exchangeParam )
{

	m_nKey = exchangeParam.m_nKey;

	m_orderID = exchangeParam.m_orderID;
	m_orderType = exchangeParam.m_orderType;
	m_str_Column_OrderType = exchangeParam.m_str_Column_OrderType;
	m_str_Column_TIF = exchangeParam.m_str_Column_TIF;

	m_orderStatus = exchangeParam.m_orderStatus;
	m_str_Column_OrderStatus = exchangeParam.m_str_Column_OrderStatus;
	m_strExchangeName = exchangeParam.m_strExchangeName;
	m_strInstrumentCode = exchangeParam.m_strInstrumentCode;
	m_str_Column_Account = exchangeParam.m_str_Column_Account;

	m_side = exchangeParam.m_side;
	m_str_Column_BuyOrSell = exchangeParam.m_str_Column_BuyOrSell;
	m_orderQty = exchangeParam.m_orderQty;

	m_n_Column_Lots = exchangeParam.m_n_Column_Lots;
	m_price = exchangeParam.m_price;
	m_price2 = exchangeParam.m_price2;
	m_n_Column_Filled = exchangeParam.m_n_Column_Filled;


	m_avgPrice = exchangeParam.m_avgPrice;
	m_transactTime = exchangeParam.m_transactTime;
	m_str_Column_Time = exchangeParam.m_str_Column_Time;
	m_rejectReason = exchangeParam.m_rejectReason;

	m_text = exchangeParam.m_text;
	m_fees = exchangeParam.m_fees;
	m_margin = exchangeParam.m_margin;

	m_Column_Contract = exchangeParam.m_Column_Contract;
	m_Column_Currency = exchangeParam.m_Column_Currency;
	m_margin = exchangeParam.m_margin;


	return *this;
}

void COrderInfo::_ClearData()
{
	
	this->m_nKey = 0;

}
Order::OrderType COrderInfo::getEnumOrderType( const QString& strOrderType )
{
	QString strOrderTypeTmp;
	QString strCheckTmp;
	Order::OrderType nOrderType = Order::UNKNOWN;
	strOrderTypeTmp = strOrderType;
	strOrderTypeTmp = strOrderTypeTmp.toUpper();

	strCheckTmp = DEFVALUE_String_OrderType_MARKET.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = Order::MARKET;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_MARKET_FAK.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = Order::MARKET_FAK;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_MARKET_FOK.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = Order::MARKET_FOK;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_LIMIT.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = Order::LIMIT;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_LIMIT_FAK.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = Order::LIMIT_FAK;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_LIMIT_FOK.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = Order::LIMIT_FOK;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_STOP.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = Order::STOP;
		return nOrderType;
	}

	strCheckTmp = DEFVALUE_String_OrderType_UNKNOWN.c_str();
	if (strCheckTmp == strOrderTypeTmp)
	{
		nOrderType = Order::UNKNOWN;
		return nOrderType;
	}

	return nOrderType;
}


QString COrderInfo::getStrOrderType(Order::OrderType nOrderType)
{
	QString strValue;


	switch (nOrderType)
	{
	case Order::MARKET:
		strValue = DEFVALUE_String_OrderType_MARKET.c_str();
		break;
	case Order::MARKET_FAK:
		strValue = DEFVALUE_String_OrderType_MARKET_FAK.c_str();
		break;
	case Order::MARKET_FOK:
		strValue = DEFVALUE_String_OrderType_MARKET_FOK.c_str();
		break;
	case Order::LIMIT:
		strValue = DEFVALUE_String_OrderType_LIMIT.c_str();
		break;
	case Order::LIMIT_FAK:
		strValue = DEFVALUE_String_OrderType_LIMIT_FAK.c_str();
		break;
	case Order::LIMIT_FOK:
		strValue = DEFVALUE_String_OrderType_LIMIT_FOK.c_str();
		break;
	case Order::STOP:
		strValue = DEFVALUE_String_OrderType_STOP.c_str();
		break;
	case Order::UNKNOWN:
		strValue = DEFVALUE_String_OrderType_UNKNOWN.c_str();
		break;
	default:
		strValue = DEFVALUE_String_OrderType_UNKNOWN.c_str();
		break;
	}

	return strValue;

}



QString COrderInfo::getStrOrderStatus(Order::OrderStatus  nOrderStatus)
{
	QString strValue;

	switch (nOrderStatus)
	{
	case Order::NEW:
		strValue = "NEW";
		break;
	case Order::PARTIALLY_FILLED:
		strValue = "PARTIALLY_FILLED";
		break;
	case Order::FILLED:
		strValue = "FILLED";
		break;
	case Order::DONE_FOR_DAY:
		strValue = "DONE_FOR_DAY";
		break;
	case Order::CANCELED:
		strValue = "CANCELED";
		break;
	case Order::REPLACED:
		strValue = "REPLACED";
		break;
	case Order::PENDING_CANCEL:
		strValue = "PENDING_CANCEL";
		break;
	case Order::STOPPED:
		strValue = "STOPPED";
		break;
	case Order::REJECTED:
		strValue = "REJECTED";
		break;
	case Order::SUSPENDED:
		strValue = "SUSPENDED";
		break;
	case Order::PENDING_NEW:
		strValue = "PENDING_NEW";
		break;
	case Order::CALCULATED:
		strValue = "CALCULATED";
		break;	
	case Order::PENDING_REPLACE:
		strValue = "PENDING_REPLACE";
		break;
	default:
		strValue = "UNKNOWN";
		break;
	}

	return strValue;

}



QString COrderInfo::getStrOrderSide(Order::Side  nSide)
{
	QString strValue;

	switch (nSide)
	{
	case Order::BUY:
		strValue = "BUY";
		break;
	case Order::SELL:
		strValue = "SELL";
		break;
	default:
		strValue = "UNKNOWN";
		break;
	}

	return strValue;

}

int COrderInfo::getColumnValueIsOrderFilled(Order::OrderStatus  nOrderStatus)
{
	int nValue = 0;

	if (Order::FILLED == nOrderStatus)
	{
		nValue = 1;
	}
	else
	{
		nValue = 0;
	}


	return nValue;
}


void COrderInfo::setValue( const Order &newValue )
{
	_ClearData();

	m_nKey = newValue.getOrderID();

	m_orderID = newValue.getOrderID();
	m_orderType = newValue.getOrderType();
	m_str_Column_OrderType = getStrOrderType(m_orderType);
	m_str_Column_TIF = "Day";
	m_orderStatus = newValue.getOrderStatus();
	m_str_Column_OrderStatus = getStrOrderStatus(m_orderStatus);
	m_strExchangeName = newValue.getInstrument().getExchangeName().c_str();
	m_strInstrumentCode = newValue.getInstrument().getInstrumentCode().c_str();
	m_str_Column_Account = newValue.getAccount().getAccountCode();
	m_side = newValue.getSide();
	m_str_Column_BuyOrSell = getStrOrderSide(m_side);
	m_orderQty = newValue.getOrderQty();
	m_n_Column_Lots = m_orderQty;
	m_price = newValue.getPrice();
	m_price2 = newValue.getPrice2();
	m_n_Column_Filled = getColumnValueIsOrderFilled(m_orderStatus);
	m_avgPrice = newValue.getAvgPrice();
	m_transactTime = newValue.getTransactTime();
	//m_str_Column_Time = m_pUtilityFun->dataTimeToStr((time_t)m_transactTime).c_str();
	m_str_Column_Time = m_pUtilityFun->dateTimeToStr_Qt((time_t)m_transactTime).c_str();
	m_rejectReason = newValue.getRejectReason();
	m_text = newValue.getText();
	m_fees = newValue.getFees();
	m_margin = newValue.getMargin();
	m_Column_Contract = m_strExchangeName + "/" + m_strInstrumentCode;
	m_Column_Currency = newValue.getAccount().getCurrency().getCurrencyCode().c_str();


}

QString COrderInfo::getInformativeText()
{
	QString strInformativeText;

	strInformativeText.clear();
	strInformativeText += QString("OrderID:%1\n").arg(m_orderID);
	strInformativeText += QString("OrderType:%1\n").arg(m_str_Column_OrderType);
	strInformativeText += QString("OrderStatus:%1\n").arg(m_str_Column_OrderStatus);
	strInformativeText += QString("ExchangeName:%1\n").arg(m_strExchangeName);
	strInformativeText += QString("InstrumentCode:%1\n").arg(m_strInstrumentCode);
	strInformativeText += QString("AccountCode:%1\n").arg(m_str_Column_Account);
	strInformativeText += QString("Side:%1\n").arg(m_str_Column_BuyOrSell);
	strInformativeText += QString("OrderQty:%1\n").arg(m_n_Column_Lots);
	strInformativeText += QString("Price:%1\n").arg(m_price);
	strInformativeText += QString("TransactTime:%1\n").arg(m_str_Column_Time);
	strInformativeText += QString("RejectReason:%1\n").arg(m_rejectReason);
	strInformativeText += QString("Currency:%1\n").arg(m_Column_Currency);
	

	return strInformativeText;
}



void COrderInfo::logInfo( const QString& strLogInfo )
{
	MYLOG4CPP_DEBUG<<"COrderInfo:"
		<<" "<<"m_nKey="<<m_nKey
		<<" "<<"m_nOrderID="<<m_nKey;
}



void COrderInfo::setDefaultValue()
{
	this->m_nKey = 0;
}
unsigned int COrderInfo::getKey()
{
	return m_nKey;
}


QVariant COrderInfo::getValueByName( const QString& strName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;

	strlstClumnNameShow.push_back(strName);


	//static const std::string DEFVALUE_String_ColumnName_Data_Key = "Key";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Data_Key.c_str())))
	{
		varValueRes = QVariant(this->m_nKey);
		return varValueRes;
	}


	//活动订单
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderID = "OrderID";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderID.c_str())))
	{
		varValueRes = QVariant(this->m_orderID);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderType = "OrderType";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderType.c_str())))
	{
		varValueRes = QVariant(this->m_str_Column_OrderType);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_TIF = "TIF";//有效时间
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_TIF.c_str())))
	{
		varValueRes = QVariant(this->m_str_Column_TIF);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderStatus = "OrderStatus";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderStatus.c_str())))
	{
		varValueRes = QVariant(this->m_str_Column_OrderStatus);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Exchange = "Exchange";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Exchange.c_str())))
	{
		varValueRes = QVariant(this->m_strExchangeName);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_InstrumentCode = "InstrumentCode";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_InstrumentCode.c_str())))
	{
		varValueRes = QVariant(this->m_strInstrumentCode);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Account = "Account";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Account.c_str())))
	{
		varValueRes = QVariant(this->m_str_Column_Account);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_BuyOrSell = "Buy/Sell";//Side
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_BuyOrSell.c_str())))
	{
		varValueRes = QVariant(this->m_str_Column_BuyOrSell);
		return varValueRes;
	}
	
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Lots = "Lots";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Lots.c_str())))
	{
		varValueRes = QVariant(this->m_n_Column_Lots);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price = "Price";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Price.c_str())))
	{
		varValueRes = QVariant(this->m_price);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price2 = "Price2";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Price2.c_str())))
	{
		varValueRes = QVariant(this->m_price2);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Filled = "Filled";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Filled.c_str())))
	{
		varValueRes = QVariant(this->m_n_Column_Filled);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_AvgPrice = "AvgPrice";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_AvgPrice.c_str())))
	{
		varValueRes = QVariant(this->m_avgPrice);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_TransactTime = "TransactTime";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_TransactTime.c_str())))
	{
		varValueRes = QVariant(this->m_str_Column_Time);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_RejectReason = "RejectReason";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_RejectReason.c_str())))
	{
		varValueRes = QVariant(this->m_rejectReason);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Column_Fees = "Fees";//手续费
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Column_Fees.c_str())))
	{
		varValueRes = QVariant(this->m_fees);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Column_Margin = "Margin";//保证金
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Column_Margin.c_str())))
	{
		varValueRes = QVariant(this->m_margin);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Column_Currency = "Currency";//货币//"CNY"
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Column_Currency.c_str())))
	{
		varValueRes = QVariant(this->m_Column_Currency);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Column_Contract = "Contract";//合约//"SHFE/ag1409"
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Column_Contract.c_str())))
	{
		varValueRes = QVariant(this->m_Column_Contract);
		return varValueRes;
	}



	return varValueRes;
}






//QT_END_NAMESPACE





