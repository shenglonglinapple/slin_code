#include "InstrumentInfoHelper.h"

#include "Log4cppLogger.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CInstrumentInfoHelper::CInstrumentInfoHelper()
{
	m_strExchangeName.clear();
	m_strUnderlyingCode.clear();
	m_strInstrumentCode.clear();
	m_nInstrumentID = 0;
}

CInstrumentInfoHelper::~CInstrumentInfoHelper()
{
	m_strExchangeName.clear();
	m_strUnderlyingCode.clear();
	m_strInstrumentCode.clear();
	m_nInstrumentID = 0;
}


CInstrumentInfoHelper& CInstrumentInfoHelper::operator=( const CInstrumentInfoHelper& exchangeParam )
{
	m_strExchangeName = exchangeParam.getExchangeName();
	m_strUnderlyingCode = exchangeParam.getUnderlyingCode();
	m_strInstrumentCode = exchangeParam.getInstrumentCode();
	m_nInstrumentID = exchangeParam.getInstrumentID();
	return *this;
}


void CInstrumentInfoHelper::setValue( const Instrument &instrument)
{
	m_strExchangeName = instrument.getExchangeName().c_str();
	m_strUnderlyingCode = instrument.getUnderlyingCode().c_str();
	m_strInstrumentCode = instrument.getInstrumentCode().c_str();
	m_nInstrumentID = instrument.getInstrumentID();
}



void CInstrumentInfoHelper::setValue( unsigned int nInstrumentID, const std::string& strExchangeName, const std::string& strUnderlyingCode, const std::string& strInstrumentCode )
{
	m_nInstrumentID = nInstrumentID;
	m_strExchangeName = strExchangeName.c_str();
	m_strUnderlyingCode = strUnderlyingCode.c_str();
	m_strInstrumentCode = strInstrumentCode.c_str();

}

QString CInstrumentInfoHelper::getExchangeName() const
{
	return m_strExchangeName;
}

QString CInstrumentInfoHelper::getUnderlyingCode() const
{
	return m_strUnderlyingCode;
}

QString CInstrumentInfoHelper::getInstrumentCode() const
{
	return m_strInstrumentCode;
}

unsigned int CInstrumentInfoHelper::getInstrumentID() const
{
	return m_nInstrumentID;
}
void CInstrumentInfoHelper::logInfo( const QString& strLogInfo ) const
{
	MYLOG4CPP_DEBUG<<strLogInfo.toStdString()
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_strExchangeName.toStdString()
		<<" "<<"m_strUnderlyingCode="<<m_strUnderlyingCode.toStdString()
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode.toStdString();
}

void CInstrumentInfoHelper::setDefaultValue()
{
	m_nInstrumentID = 0;
	m_strExchangeName = "AAAA";
	m_strUnderlyingCode = "BB";
	m_strInstrumentCode = "AAAA_BB_CC";
}



//QT_END_NAMESPACE

