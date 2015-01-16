#include "ItemStockHistoryDataHelper.h"

#include "HistoryData.h"
#include "Log4cppLogger.h"


static const char* DEFVALUE_String_ColumnName_SymbolUse = "SymbolUse";
static const char* DEFVALUE_String_ColumnName_Date = "Date";
static const char* DEFVALUE_String_ColumnName_Open = "Open";
static const char* DEFVALUE_String_ColumnName_High = "High";
static const char* DEFVALUE_String_ColumnName_Low = "Low";
static const char* DEFVALUE_String_ColumnName_Close = "Close";
static const char* DEFVALUE_String_ColumnName_Volume = "Volume";
static const char* DEFVALUE_String_ColumnName_AdjClose = "AdjClose";



CItemStockHistoryDataHelper::CItemStockHistoryDataHelper()
{
	_ClearData();
}

CItemStockHistoryDataHelper::~CItemStockHistoryDataHelper()
{
	_ClearData();
}


CItemStockHistoryDataHelper& CItemStockHistoryDataHelper::operator=( const CItemStockHistoryDataHelper& objCopy )
{
	m_strSymbolUse = objCopy.m_strSymbolUse;
	m_strDate = objCopy.m_strDate;
	m_strOpen = objCopy.m_strOpen;
	m_strHigh = objCopy.m_strHigh;
	m_strLow = objCopy.m_strLow;
	m_strClose = objCopy.m_strClose;
	m_strVolume = objCopy.m_strVolume;
	m_strAdjClose = objCopy.m_strAdjClose;


	return *this;
}

void CItemStockHistoryDataHelper::_ClearData()
{
	m_strSymbolUse.clear();
	m_strDate.clear();
	m_strOpen.clear();
	m_strHigh.clear();
	m_strLow.clear();
	m_strClose.clear();
	m_strVolume.clear();
	m_strAdjClose.clear();
}
void CItemStockHistoryDataHelper::setValue(const CHistoryData* pData)
{
	_ClearData();

	m_strSymbolUse = pData->m_strSymbolUse;
	m_strDate = pData->m_strDate;
	m_strOpen = pData->m_strOpen;
	m_strHigh = pData->m_strHigh;
	m_strLow = pData->m_strLow;
	m_strClose = pData->m_strClose;
	m_strVolume = pData->m_strVolume;
	m_strAdjClose = pData->m_strAdjClose;

}

void CItemStockHistoryDataHelper::logInfo(const QString& file, qint32 line, const QString& strLog)
{
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<"strLog="<<strLog
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strDate="<<m_strDate
		<<" "<<"m_strOpen="<<m_strOpen
		<<" "<<"m_strHigh="<<m_strHigh
		<<" "<<"m_strLow="<<m_strLow
		<<" "<<"m_strClose="<<m_strClose
		<<" "<<"m_strVolume="<<m_strVolume
		<<" "<<"m_strAdjClose="<<m_strAdjClose;
}


void CItemStockHistoryDataHelper::getLstClumnName( QStringList& lstClumnName )
{
	QString strColumnName;
	lstClumnName.clear();

	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SymbolUse);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Date);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Open);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_High);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Low);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Close);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Volume);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_AdjClose);
	lstClumnName.append(strColumnName);
}

void CItemStockHistoryDataHelper::getLstClumnName( QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	CItemStockHistoryDataHelper::getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.append(varColumnName);
	}
}


QVariant CItemStockHistoryDataHelper::getColumnValueByName( const QString& strtColumnName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;
	strlstClumnNameShow.push_back(strtColumnName);

	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SymbolUse)))
	{
		varValueRes = QVariant(this->m_strSymbolUse);
		return varValueRes;
	}

	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Date)))
	{
		varValueRes = QVariant(this->m_strDate);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Open)))
	{
		varValueRes = QVariant(this->m_strOpen);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_High)))
	{
		varValueRes = QVariant(this->m_strHigh);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Low)))
	{
		varValueRes = QVariant(this->m_strLow);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Close)))
	{
		varValueRes = QVariant(this->m_strClose);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Volume)))
	{
		varValueRes = QVariant(this->m_strVolume);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_AdjClose)))
	{
		varValueRes = QVariant(this->m_strAdjClose);
		return varValueRes;
	}

	return varValueRes;
}


void CItemStockHistoryDataHelper::getItemNodeData(QList<QVariant>& itemDataTmp)
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





