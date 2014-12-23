#include "ItemUserOrderHelper.h"

#include "QtTimeHelper.h"

#include "Log4cppLogger.h"

static const std::string DEFVALUE_String_ColumnName_InstrumentID = "InstrumentID";
static const std::string DEFVALUE_String_ColumnName_InstrumentCode = "InstrumentCode";
static const std::string DEFVALUE_String_ColumnName_BuyOrSell = "Buy/Sell";//Side
static const std::string DEFVALUE_String_ColumnName_OrderType = "OrderType";//Market
static const std::string DEFVALUE_String_ColumnName_OrderStatus = "OrderStatus";//
static const std::string DEFVALUE_String_ColumnName_TransactTime = "TransactTime";
static const std::string DEFVALUE_String_ColumnName_TransactPrice = "TransactPrice";//办理价格
static const std::string DEFVALUE_String_ColumnName_Fees = "Fees";
static const std::string DEFVALUE_String_ColumnName_CurrentTime = "CurrentTime";
static const std::string DEFVALUE_String_ColumnName_CurrentPrice = "CurrentPrice";
static const std::string DEFVALUE_String_ColumnName_Total = "Total";


CItemUserOrderHelper::CItemUserOrderHelper()
{
	_ClearData();
}

CItemUserOrderHelper::~CItemUserOrderHelper()
{
	_ClearData();
}


CItemUserOrderHelper& CItemUserOrderHelper::operator=( const CItemUserOrderHelper& objCopy )
{
	m_Column_InstrumentID = objCopy.m_Column_InstrumentID;
	m_Column_InstrumentCode = objCopy.m_Column_InstrumentCode;
	m_Column_Side = objCopy.m_Column_Side;
	m_Column_OrderType = objCopy.m_Column_OrderType;
	m_Column_OrderStatus = objCopy.m_Column_OrderStatus;
	m_Column_TransactTime = objCopy.m_Column_TransactTime;
	m_Column_TransactPrice = objCopy.m_Column_TransactPrice;
	m_Column_Fees = objCopy.m_Column_Fees;
	m_Column_CurrentTime = objCopy.m_Column_CurrentTime;
	m_Column_CurrentPrice = objCopy.m_Column_CurrentPrice;
	m_Column_Total = objCopy.m_Column_Total;

	m_nSide = objCopy.m_nSide;
	m_strExchangeName = objCopy.m_strExchangeName;
	m_orderType  = objCopy.m_orderType;
	m_nOrderStatus = objCopy.m_nOrderStatus;
	m_nTransactTime  = objCopy.m_nTransactTime;
	m_nCurrentTime = objCopy.m_nCurrentTime;

	return *this;
}

void CItemUserOrderHelper::_ClearData()
{
	m_Column_InstrumentID = 0;
	m_Column_InstrumentCode.clear();
	m_Column_Side.clear();
	m_Column_OrderType.clear();
	m_Column_OrderStatus.clear();
	m_Column_TransactTime.clear();
	m_Column_TransactPrice = 0;
	m_Column_Fees = 0;
	m_Column_CurrentTime.clear();
	m_Column_CurrentPrice = 0;
	m_Column_Total = 0;

	m_nSide = COrderData::BUY;
	m_strExchangeName.clear();
	m_orderType = COrderData::MARKET;
	m_nOrderStatus = COrderData::FILLED;
	m_nTransactTime = 0;
	m_nCurrentTime = 0;

}









unsigned int CItemUserOrderHelper::getInstrumentID() const
{
	return m_Column_InstrumentID;
}


QString CItemUserOrderHelper::getInstrumentCode() const
{
	return m_Column_InstrumentCode;
}

void CItemUserOrderHelper::logInfo(const std::string& file, int line, const QString& strLogInfo)
{
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<strLogInfo.toStdString()
		<<" "<<"m_Column_InstrumentID="<<m_Column_InstrumentID
		<<" "<<"m_Column_InstrumentCode="<<m_Column_InstrumentCode.toStdString();

}


void CItemUserOrderHelper::getLstClumnName( QStringList& lstClumnName )
{
	QString strColumnName;
	lstClumnName.clear();

	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_InstrumentID.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_InstrumentCode.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_BuyOrSell.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_OrderType.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_OrderStatus.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TransactTime.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TransactPrice.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Fees.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_CurrentTime.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_CurrentPrice.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Total.c_str());
	lstClumnName.append(strColumnName);

}

void CItemUserOrderHelper::getLstClumnName( QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	CItemUserOrderHelper::getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.append(varColumnName);
	}
}


QVariant CItemUserOrderHelper::getColumnValueByName( const QString& strtColumnName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;

	strlstClumnNameShow.push_back(strtColumnName);

	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_InstrumentID.c_str())))
	{
		varValueRes = QVariant(this->m_Column_InstrumentID);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_InstrumentCode.c_str())))
	{
		varValueRes = QVariant(this->m_Column_InstrumentCode);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_BuyOrSell.c_str())))
	{
		varValueRes = QVariant(this->m_Column_Side);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderType.c_str())))
	{
		varValueRes = QVariant(this->m_Column_OrderType);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderStatus.c_str())))
	{
		varValueRes = QVariant(this->m_Column_OrderStatus);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TransactTime.c_str())))
	{
		varValueRes = QVariant(this->m_Column_TransactTime);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TransactPrice.c_str())))
	{
		varValueRes = QVariant(this->m_Column_TransactPrice);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Fees.c_str())))
	{
		varValueRes = QVariant(this->m_Column_Fees);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_CurrentTime.c_str())))
	{
		varValueRes = QVariant(this->m_Column_CurrentTime);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_CurrentPrice.c_str())))
	{
		varValueRes = QVariant(this->m_Column_CurrentPrice);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Total.c_str())))
	{
		varValueRes = QVariant(this->m_Column_Total);
		return varValueRes;
	}
	return varValueRes;
}


void CItemUserOrderHelper::getItemNodeData(QList<QVariant>& itemDataTmp)
{
	QVariant varValueGet;
	QStringList strlstClumnNameShow;
	getLstClumnName(strlstClumnNameShow);

	itemDataTmp.clear();

	foreach (const QString& strColumnName, strlstClumnNameShow)
	{
		varValueGet = getColumnValueByName(strColumnName);
		itemDataTmp.push_back(varValueGet);
	}

	return;
}
//QT_END_NAMESPACE





