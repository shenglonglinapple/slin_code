#include "OrderInfo.h"

#include "ProjectUtilityFun.h"
#include <QtCore/QStringList>

#include "BoostLogger.h"
USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE




static const std::string DEFVALUE_String_ColumnName_Data_Key = "Key";//

static const std::string DEFVALUE_String_ColumnName_OrderInfo_CumQty = "CumQty";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_LastQty = "LastQty";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderQty = "OrderQty";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_LeavesQty = "LeavesQty";//

static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price = "Price";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price2 = "Price2";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_LastPx = "LastPx";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_AvgPrice = "AvgPrice";//

static const std::string DEFVALUE_String_ColumnName_OrderInfo_Side = "Side";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderType = "OrderType";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderStatus = "OrderStatus";//


static const std::string DEFVALUE_String_ColumnName_OrderInfo_RejectReason = "RejectReason";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Text = "Text";//

static const std::string DEFVALUE_String_ColumnName_OrderInfo_UserID = "UserID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_ClOrdID = "ClOrdID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderID = "OrderID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_AccountID = "AccountID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_StrategyID = "StrategyID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_InstrumentID = "InstrumentID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_TransactTime = "TransactTime";//


static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderInfoMasks = "OrderInfoMasks";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Fees = "Fees";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Margin = "Margin";//



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

	m_side = exchangeParam.m_side;
	m_cumQty = exchangeParam.m_cumQty;
	m_lastQty = exchangeParam.m_lastQty;
	m_orderQty = exchangeParam.m_orderQty;
	m_leavesQty = exchangeParam.m_leavesQty;
	m_rejectReason = exchangeParam.m_rejectReason;

	m_price = exchangeParam.m_price;
	m_price2 = exchangeParam.m_price2;
	m_lastPx = exchangeParam.m_lastPx;
	m_avgPrice = exchangeParam.m_avgPrice;
	m_orderType = exchangeParam.m_orderType;
	m_orderStatus = exchangeParam.m_orderStatus;


	m_userID = exchangeParam.m_userID;
	m_orderID = exchangeParam.m_orderID;
	m_clOrdID = exchangeParam.m_clOrdID;
	m_strategyID = exchangeParam.m_strategyID;
	m_transactTime = exchangeParam.m_transactTime;
	m_orderInfoMasks = exchangeParam.m_orderInfoMasks;

	m_nAccountID = exchangeParam.m_nAccountID;
	m_nInstrumentID = exchangeParam.m_nInstrumentID;

	m_fees = exchangeParam.m_fees;
	m_margin = exchangeParam.m_margin;
	m_text = exchangeParam.m_text;



	return *this;
}

void COrderInfo::_ClearData()
{
	
	this->m_nKey = 0;

}




void COrderInfo::setValue( const Order &newValue )
{
	_ClearData();
	m_nKey = newValue.getOrderID();
	m_side = newValue.getSide();
	m_cumQty = newValue.getCumQty();
	m_lastQty = newValue.getLastQty();
	m_orderQty = newValue.getOrderQty();
	m_leavesQty = newValue.getLeavesQty();
	m_rejectReason = newValue.getRejectReason();

	m_price = newValue.getPrice();
	m_price2 = newValue.getPrice2();
	m_lastPx = newValue.getLastPx();
	m_avgPrice = newValue.getAvgPrice();
	m_orderType = newValue.getOrderType();
	m_orderStatus = newValue.getOrderStatus();


	m_userID = newValue.getUserID();
	m_orderID = newValue.getOrderID();
	m_clOrdID = newValue.getClOrdID();
	m_strategyID = newValue.getStrategyID();
	m_transactTime = newValue.getTransactTime();
	m_orderInfoMasks = newValue.getOrderInfoMasks();

	m_nAccountID = newValue.getAccountID();
	m_nInstrumentID = newValue.getInstrumentID();


	m_fees = newValue.getFees();
	m_margin = newValue.getMargin();
	m_text = newValue.getText();

}





void COrderInfo::logInfo( const QString& strLogInfo ) const
{
	LOG_DEBUG<<"COrderInfo:"
		<<" "<<"m_nKey="<<m_nKey
		<<" "<<"m_nOrderID="<<m_nKey;
}



void COrderInfo::setDefaultValue()
{
	this->m_nKey = 0;
}

QVariant COrderInfo::getValueByName( const QString& strName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;

	strlstClumnNameShow.push_back(strName);


	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Data_Key.c_str())))
	{
		varValueRes = QVariant(this->m_nKey);
		return varValueRes;
	}



	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_CumQty = "CumQty";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_CumQty.c_str())))
	{
		varValueRes = QVariant(this->m_cumQty);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_LastQty = "LastQty";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_LastQty.c_str())))
	{
		varValueRes = QVariant(this->m_lastQty);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderQty = "OrderQty";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderQty.c_str())))
	{
		varValueRes = QVariant(this->m_orderQty);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_LeavesQty = "LeavesQty";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_LeavesQty.c_str())))
	{
		varValueRes = QVariant(this->m_leavesQty);
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
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_LastPx = "LastPx";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_LastPx.c_str())))
	{
		varValueRes = QVariant(this->m_lastPx);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_AvgPrice = "AvgPrice";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_AvgPrice.c_str())))
	{
		varValueRes = QVariant(this->m_avgPrice);
		return varValueRes;
	}

	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Side = "Side";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Side.c_str())))
	{
		varValueRes = QVariant(this->m_side);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderType = "OrderType";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderType.c_str())))
	{
		varValueRes = QVariant(this->m_orderType);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderStatus = "OrderStatus";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderStatus.c_str())))
	{
		varValueRes = QVariant(this->m_orderStatus);
		return varValueRes;
	}


	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_RejectReason = "RejectReason";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_RejectReason.c_str())))
	{
		varValueRes = QVariant(this->m_rejectReason);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Text = "Text";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Text.c_str())))
	{
		varValueRes = QVariant(this->m_text.c_str());
		return varValueRes;
	}

	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_UserID = "UserID";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_UserID.c_str())))
	{
		varValueRes = QVariant(this->m_userID);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_ClOrdID = "ClOrdID";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_ClOrdID.c_str())))
	{
		varValueRes = QVariant(this->m_clOrdID);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderID = "OrderID";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderID.c_str())))
	{
		varValueRes = QVariant(this->m_orderID);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_AccountID = "AccountID";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_AccountID.c_str())))
	{
		varValueRes = QVariant(this->m_nAccountID);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_StrategyID = "StrategyID";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_StrategyID.c_str())))
	{
		varValueRes = QVariant(this->m_strategyID);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_InstrumentID = "InstrumentID";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_InstrumentID.c_str())))
	{
		varValueRes = QVariant(this->m_nInstrumentID);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_TransactTime = "TransactTime";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_TransactTime.c_str())))
	{
		varValueRes = QVariant(this->m_transactTime);
		return varValueRes;
	}


	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderInfoMasks = "OrderInfoMasks";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderInfoMasks.c_str())))
	{
		varValueRes = QVariant(this->m_orderInfoMasks);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Fees = "Fees";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Fees.c_str())))
	{
		varValueRes = QVariant(this->m_fees);
		return varValueRes;
	}
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Margin = "Margin";//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_Margin.c_str())))
	{
		varValueRes = QVariant(this->m_margin);
		return varValueRes;
	}


	return varValueRes;
}

unsigned int COrderInfo::getKey()
{
	return m_nKey;
}


//QT_END_NAMESPACE





