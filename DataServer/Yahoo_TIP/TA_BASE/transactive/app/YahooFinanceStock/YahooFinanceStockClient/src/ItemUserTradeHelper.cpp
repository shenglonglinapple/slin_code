#include "ItemUserTradeHelper.h"

#include "UserTradeInfo.h"
#include "Log4cppLogger.h"


static const char* DEFVALUE_String_ColumnName_UseID = "UseID";
static const char* DEFVALUE_String_ColumnName_TradeUUID = "TradeUUID";
static const char* DEFVALUE_String_ColumnName_TradeTime = "TradeTime";
static const char* DEFVALUE_String_ColumnName_TradeType = "TradeType";
static const char* DEFVALUE_String_ColumnName_SymbolUse = "SymbolUse";
static const char* DEFVALUE_String_ColumnName_TradePrice = "TradePrice";
static const char* DEFVALUE_String_ColumnName_TradeVolume = "TradeVolume";
static const char* DEFVALUE_String_ColumnName_TradeAmount = "TradeAmount";
static const char* DEFVALUE_String_ColumnName_TradeFees = "TradeFees";
static const char* DEFVALUE_String_ColumnName_TotalTradeFee = "TotalTradeFee";
static const char* DEFVALUE_String_ColumnName_TotalTradeAmount = "TotalTradeAmount";



CItemUserTradeHelper::CItemUserTradeHelper()
{
	_ClearData();
}

CItemUserTradeHelper::~CItemUserTradeHelper()
{
	_ClearData();
}


CItemUserTradeHelper& CItemUserTradeHelper::operator=( const CItemUserTradeHelper& objCopy )
{
	m_strUseID = objCopy.m_strUseID;
	m_strTradeUUID = objCopy.m_strTradeUUID;
	m_strTradeTime = objCopy.m_strTradeTime;
	m_nTradeType = objCopy.m_nTradeType;
	m_strSymbolUse = objCopy.m_strSymbolUse;
	m_fTradePrice = objCopy.m_fTradePrice;
	m_nTradeVolume = objCopy.m_nTradeVolume;
	m_fTradeAmount = objCopy.m_fTradeAmount;
	m_fTradeFees = objCopy.m_fTradeFees;
	m_fTotalTradeFee = objCopy.m_fTotalTradeFee;
	m_fTotalTradeAmount = objCopy.m_fTotalTradeAmount;

	return *this;
}

void CItemUserTradeHelper::_ClearData()
{
	m_strUseID.clear();
	m_strTradeTime.clear();
	m_strTradeUUID.clear();
	m_nTradeType = -1;
	m_strSymbolUse.clear();
	m_fTradePrice = 0;
	m_nTradeVolume = 0;
	m_fTradeAmount = 0;
	m_fTradeFees = 0;
	m_fTotalTradeFee = 0;
	m_fTotalTradeAmount = 0;

}

void CItemUserTradeHelper::setValue( const CUserTradeInfo* pData )
{
	_ClearData();

}

void CItemUserTradeHelper::logInfo(const QString& file, qint32 line, const QString& strLog)
{
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<"strLog="<<strLog
		<<" "<<"m_strUseID="<<m_strUseID
		<<" "<<"m_strTradeTime="<<m_strTradeTime
		<<" "<<"m_strTradeUUID="<<m_strTradeUUID
		<<" "<<"m_nTradeType="<<m_nTradeType
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_fTradePrice="<<m_fTradePrice
		<<" "<<"m_nTradeVolume="<<m_nTradeVolume
		<<" "<<"m_fTradeAmount="<<m_fTradeAmount
		<<" "<<"m_fTradeFees="<<m_fTradeFees
		<<" "<<"m_fTotalTradeFee="<<m_fTotalTradeFee
		<<" "<<"m_fTotalTradeAmount="<<m_fTotalTradeAmount;
}


void CItemUserTradeHelper::getLstClumnName( QStringList& lstClumnName )
{
	QString strColumnName;
	lstClumnName.clear();

	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_UseID);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TradeUUID);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TradeTime);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TradeType);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SymbolUse);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TradePrice);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TradeVolume);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TradeAmount);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TradeFees);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TotalTradeFee);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_TotalTradeAmount);
	lstClumnName.append(strColumnName);

}

void CItemUserTradeHelper::getLstClumnName( QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	CItemUserTradeHelper::getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.append(varColumnName);
	}
}


QVariant CItemUserTradeHelper::getColumnValueByName( const QString& strtColumnName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;
	strlstClumnNameShow.push_back(strtColumnName);

	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_UseID)))
	{
		varValueRes = QVariant(this->m_strUseID);
		return varValueRes;
	}

	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TradeUUID)))
	{
		varValueRes = QVariant(this->m_strTradeUUID);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TradeTime)))
	{
		varValueRes = QVariant(this->m_strTradeTime);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TradeType)))
	{
		varValueRes = QVariant(this->m_nTradeType);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SymbolUse)))
	{
		varValueRes = QVariant(this->m_strSymbolUse);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TradePrice)))
	{
		varValueRes = QVariant(this->m_fTradePrice);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TradeVolume)))
	{
		varValueRes = QVariant(this->m_nTradeVolume);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TradeAmount)))
	{
		varValueRes = QVariant(this->m_fTradeAmount);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TradeFees)))
	{
		varValueRes = QVariant(this->m_fTradeFees);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TotalTradeFee)))
	{
		varValueRes = QVariant(this->m_fTotalTradeFee);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_TotalTradeAmount)))
	{
		varValueRes = QVariant(this->m_fTotalTradeAmount);
		return varValueRes;
	}
	return varValueRes;
}


void CItemUserTradeHelper::getItemNodeData(QList<QVariant>& itemDataTmp)
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





