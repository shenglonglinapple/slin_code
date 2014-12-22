#include "ItemWaitingInstrumentHelper.h"

#include "MyInstrument.h"
#include "QtTimeHelper.h"
#include "ItemWaitingInstrument.h"

#include "Log4cppLogger.h"

//tree
static const std::string DEFVALUE_String_ColumnName_InstrumentID = "InstrumentID";
static const std::string DEFVALUE_String_ColumnName_ExchangeName = "ExchangeName";
static const std::string DEFVALUE_String_ColumnName_UnderlyingCode = "UnderlyingCode";
static const std::string DEFVALUE_String_ColumnName_InstrumentCode = "InstrumentCode";


CItemWaitingInstrumentHelper::CItemWaitingInstrumentHelper()
{
	_ClearData();
}

CItemWaitingInstrumentHelper::~CItemWaitingInstrumentHelper()
{
	_ClearData();
}


CItemWaitingInstrumentHelper& CItemWaitingInstrumentHelper::operator=( const CItemWaitingInstrumentHelper& objCopy )
{
	m_nInstrumentID = objCopy.m_nInstrumentID;
	m_strExchangeName = objCopy.m_strExchangeName;
	m_strUnderlyingCode = objCopy.m_strUnderlyingCode;
	m_strInstrumentCode = objCopy.m_strInstrumentCode;

	return *this;
}

void CItemWaitingInstrumentHelper::_ClearData()
{
	m_nInstrumentID = 0;
	m_strExchangeName.clear();
	m_strUnderlyingCode.clear();
	m_strInstrumentCode.clear();

}


void CItemWaitingInstrumentHelper::setValue( const CMyInstrument &instrument )
{
	_ClearData();
	m_nInstrumentID = instrument.getInstrumentID();
	m_strExchangeName = instrument.getExchangeName().c_str();
	m_strUnderlyingCode = instrument.getUnderlyingCode().c_str();
	m_strInstrumentCode = instrument.getInstrumentCode().c_str();
}



void CItemWaitingInstrumentHelper::logInfo(const std::string& file, int line, const QString& strLogInfo)
{
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<strLogInfo.toStdString()
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_strExchangeName.toStdString()
		<<" "<<"m_strUnderlyingCode="<<m_strUnderlyingCode.toStdString()
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode.toStdString();
}

void CItemWaitingInstrumentHelper::getLstClumnName( QStringList& lstClumnName )
{
	QString strColumnName;
	lstClumnName.clear();

	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_InstrumentID.c_str());
	lstClumnName.append(strColumnName);

}

void CItemWaitingInstrumentHelper::getLstClumnName( QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.append(varColumnName);
	}
}

QVariant CItemWaitingInstrumentHelper::getColumnValueByName( const QString& strtColumnName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;

	strlstClumnNameShow.push_back(strtColumnName);

	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_InstrumentID.c_str())))
	{
		varValueRes = QVariant(this->m_nInstrumentID);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_ExchangeName.c_str())))
	{
		varValueRes = QVariant(this->m_strExchangeName);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_UnderlyingCode.c_str())))
	{
		varValueRes = QVariant(this->m_strUnderlyingCode);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_InstrumentCode.c_str())))
	{
		varValueRes = QVariant(this->m_strInstrumentCode);
		return varValueRes;
	}

	return varValueRes;
}


void CItemWaitingInstrumentHelper::getItemNodeData(QList<QVariant>& itemDataTmp, CItemWaitingInstrument::EItemType nDataType)
{
	QVariant varValueGet;
	QString strtColumnName;

	itemDataTmp.clear();

	switch (nDataType)
	{
	case CItemWaitingInstrument::ItemType_ITEM1_ExchangeName:
		strtColumnName = DEFVALUE_String_ColumnName_ExchangeName.c_str();
		break;
	case CItemWaitingInstrument::ItemType_ITEM2_UnderlyingCode:
		strtColumnName = DEFVALUE_String_ColumnName_UnderlyingCode.c_str();
		break;
	case CItemWaitingInstrument::ItemType_ITEM3_InstrumentCode:
		strtColumnName = DEFVALUE_String_ColumnName_InstrumentCode.c_str();
		break;
	default:
		break;
	}
	varValueGet = getColumnValueByName(strtColumnName);
	itemDataTmp.push_back(varValueGet);
	return;
}
//QT_END_NAMESPACE





