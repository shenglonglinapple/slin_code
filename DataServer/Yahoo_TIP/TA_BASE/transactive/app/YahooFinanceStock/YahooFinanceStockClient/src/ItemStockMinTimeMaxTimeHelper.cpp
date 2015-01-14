#include "ItemStockMinTimeMaxTimeHelper.h"

#include "StockMinTimeMaxTime.h"

#include "Log4cppLogger.h"


static const char* DEFVALUE_String_ColumnName_SymbolUse = "SymbolUse";
static const char* DEFVALUE_String_ColumnName_MinTime = "MinTime";
static const char* DEFVALUE_String_ColumnName_MaxTime = "MaxTime";
static const char* DEFVALUE_String_ColumnName_nCount = "nCount";


CItemStockMinTimeMaxTimeHelper::CItemStockMinTimeMaxTimeHelper()
{
	_ClearData();
}

CItemStockMinTimeMaxTimeHelper::~CItemStockMinTimeMaxTimeHelper()
{
	_ClearData();
}


CItemStockMinTimeMaxTimeHelper& CItemStockMinTimeMaxTimeHelper::operator=( const CItemStockMinTimeMaxTimeHelper& objCopy )
{
	m_strSymbolUse = objCopy.m_strSymbolUse;
	m_strMinTime = objCopy.m_strMinTime;
	m_strMaxTime = objCopy.m_strMaxTime;
	m_nCount = objCopy.m_nCount;

	return *this;
}

void CItemStockMinTimeMaxTimeHelper::_ClearData()
{
	m_strSymbolUse.clear();
	m_strMinTime.clear();
	m_strMaxTime.clear();
	m_nCount = 0;
}

void CItemStockMinTimeMaxTimeHelper::setValue( const CStockMinTimeMaxTime* pData )
{
	_ClearData();
	m_strSymbolUse = pData->m_strSymbolUse;
	m_strMinTime = pData->m_strMinTime;
	m_strMaxTime = pData->m_strMaxTime;
	m_nCount = pData->m_nCount;
}

void CItemStockMinTimeMaxTimeHelper::logInfo(const QString& file, qint32 line, const QString& strLog)
{
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<"strLog="<<strLog
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strMinTime="<<m_strMinTime
		<<" "<<"m_strMaxTime="<<m_strMaxTime
		<<" "<<"m_nCount="<<m_nCount;
}


void CItemStockMinTimeMaxTimeHelper::getLstClumnName( QStringList& lstClumnName )
{
	QString strColumnName;
	lstClumnName.clear();

	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SymbolUse);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_MinTime);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_MaxTime);
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_nCount);
	lstClumnName.append(strColumnName);

}

void CItemStockMinTimeMaxTimeHelper::getLstClumnName( QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	CItemStockMinTimeMaxTimeHelper::getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.append(varColumnName);
	}
}


QVariant CItemStockMinTimeMaxTimeHelper::getColumnValueByName( const QString& strtColumnName )
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
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_MinTime)))
	{
		varValueRes = QVariant(this->m_strMinTime);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_MaxTime)))
	{
		varValueRes = QVariant(this->m_strMaxTime);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_nCount)))
	{
		varValueRes = QVariant(this->m_nCount);
		return varValueRes;
	}

	return varValueRes;
}


void CItemStockMinTimeMaxTimeHelper::getItemNodeData(QList<QVariant>& itemDataTmp)
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





