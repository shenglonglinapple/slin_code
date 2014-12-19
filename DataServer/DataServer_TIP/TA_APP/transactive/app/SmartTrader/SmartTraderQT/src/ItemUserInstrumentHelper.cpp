#include "ItemUserInstrumentHelper.h"

#include "MyInstrument.h"
#include "QtTimeHelper.h"

#include "Log4cppLogger.h"

static const std::string DEFVALUE_String_ColumnName_InstrumentID = "InstrumentID";
static const std::string DEFVALUE_String_ColumnName_InstrumentCode = "InstrumentCode";
static const std::string DEFVALUE_String_ColumnName_UpdateTime = "UpdateTime";
static const std::string DEFVALUE_String_ColumnName_LastTradePrice = "Last Trade Price";


CItemUserInstrumentHelper::CItemUserInstrumentHelper()
{
	_ClearData();
}

CItemUserInstrumentHelper::~CItemUserInstrumentHelper()
{
	_ClearData();
}


CItemUserInstrumentHelper& CItemUserInstrumentHelper::operator=( const CItemUserInstrumentHelper& objCopy )
{
	m_nInstrumentID = objCopy.m_nInstrumentID;
	m_strInstrumentCode = objCopy.m_strInstrumentCode;
	m_strExchangeName = objCopy.m_strExchangeName;
	m_strUnderlyingCode = objCopy.m_strUnderlyingCode;
	m_fLastTradePrice = objCopy.m_fLastTradePrice;
	m_nUpdateTime = objCopy.m_nUpdateTime;
	m_strUpdateTime = objCopy.m_strUpdateTime;

	return *this;
}

void CItemUserInstrumentHelper::_ClearData()
{
	m_nInstrumentID = 0;
	m_strInstrumentCode.clear();
	m_strExchangeName.clear();

	m_strUnderlyingCode.clear();
	m_fLastTradePrice = 0;
	m_nUpdateTime = 0;

	m_strUpdateTime.clear();
}


void CItemUserInstrumentHelper::setValue( const Instrument &instrument)
{
	CMyInstrument myInstrument;
	
	myInstrument.setValue(instrument);
	setValue(myInstrument);
}

void CItemUserInstrumentHelper::setValue( const CMyInstrument &instrument )
{
	CQtTimeHelper timeHelper;

	_ClearData();

	m_nInstrumentID = instrument.getInstrumentID();
	m_strInstrumentCode = instrument.getInstrumentCode().c_str();
	m_strExchangeName = instrument.getExchangeName().c_str();

	m_strUnderlyingCode = instrument.getUnderlyingCode().c_str();
	m_fLastTradePrice  = instrument.getLastPrice();

	m_nUpdateTime  = instrument.getUpdateTime();
	m_strUpdateTime = timeHelper.dateTimeToStr_Qt(m_nUpdateTime).c_str();

}






unsigned int CItemUserInstrumentHelper::getInstrumentID() const
{
	return m_nInstrumentID;
}


QString CItemUserInstrumentHelper::getInstrumentCode() const
{
	return m_strInstrumentCode;
}

void CItemUserInstrumentHelper::logInfo(const std::string& file, int line, const QString& strLogInfo)
{
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<strLogInfo.toStdString()
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_strExchangeName.toStdString()
		<<" "<<"m_strUnderlyingCode="<<m_strUnderlyingCode.toStdString()
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode.toStdString()
		<<" "<<"m_strUpdateTime="<<m_strUpdateTime.toStdString()
		<<" "<<"m_fLastTradePrice="<<m_fLastTradePrice;
}


void CItemUserInstrumentHelper::getLstClumnName( QStringList& lstClumnName )
{
	QString strColumnName;
	lstClumnName.clear();

	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_InstrumentID.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_InstrumentCode.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_UpdateTime.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_LastTradePrice.c_str());
	lstClumnName.append(strColumnName);



}

void CItemUserInstrumentHelper::getLstClumnName( QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	CItemUserInstrumentHelper::getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.append(varColumnName);
	}
}


QVariant CItemUserInstrumentHelper::getColumnValueByName( const QString& strtColumnName )
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
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_InstrumentCode.c_str())))
	{
		varValueRes = QVariant(this->m_strInstrumentCode);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_UpdateTime.c_str())))
	{
		varValueRes = QVariant(this->m_strUpdateTime);
		return varValueRes;
	}
	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_LastTradePrice.c_str())))
	{
		varValueRes = QVariant(this->m_fLastTradePrice);
		return varValueRes;
	}

	return varValueRes;
}


void CItemUserInstrumentHelper::getItemNodeData(QList<QVariant>& itemDataTmp)
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





