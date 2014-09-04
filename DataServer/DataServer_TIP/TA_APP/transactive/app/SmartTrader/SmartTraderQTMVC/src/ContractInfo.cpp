#include "ContractInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CContractInfo::CContractInfo()
{
	m_strExchangeName.clear();
	m_strUnderlyingCode.clear();
	m_strInstrumentCode.clear();
	m_nInstrumentID = 0;
}

CContractInfo::~CContractInfo()
{
	m_strExchangeName.clear();
	m_strUnderlyingCode.clear();
	m_strInstrumentCode.clear();
	m_nInstrumentID = 0;
}


CContractInfo& CContractInfo::operator=( const CContractInfo& exchangeParam )
{
	m_strExchangeName = exchangeParam.getExchangeName();
	m_strUnderlyingCode = exchangeParam.getUnderlyingCode();
	m_strInstrumentCode = exchangeParam.getInstrumentCode();
	m_nInstrumentID = exchangeParam.getInstrumentID();
	return *this;
}


void CContractInfo::setValue( const Instrument &instrument)
{
	m_strExchangeName = instrument.getExchangeName().c_str();
	m_strUnderlyingCode = instrument.getUnderlyingCode().c_str();
	m_strInstrumentCode = instrument.getInstrumentCode().c_str();
	m_nInstrumentID = instrument.getInstrumentID();
}



void CContractInfo::setValue( unsigned int nInstrumentID, const std::string& strExchangeName, const std::string& strUnderlyingCode, const std::string& strInstrumentCode )
{
	m_nInstrumentID = nInstrumentID;
	m_strExchangeName = strExchangeName.c_str();
	m_strUnderlyingCode = strUnderlyingCode.c_str();
	m_strInstrumentCode = strInstrumentCode.c_str();

}

QString CContractInfo::getExchangeName() const
{
	return m_strExchangeName;
}

QString CContractInfo::getUnderlyingCode() const
{
	return m_strUnderlyingCode;
}

QString CContractInfo::getInstrumentCode() const
{
	return m_strInstrumentCode;
}

unsigned int CContractInfo::getInstrumentID() const
{
	return m_nInstrumentID;
}
void CContractInfo::logInfo( const QString& strLogInfo ) const
{
	LOG_DEBUG<<strLogInfo.toStdString()
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_strExchangeName.toStdString()
		<<" "<<"m_strUnderlyingCode="<<m_strUnderlyingCode.toStdString()
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode.toStdString();
}

void CContractInfo::setDefaultValue()
{
	m_nInstrumentID = 1;
	m_strExchangeName = "AAAA";
	m_strUnderlyingCode = "BB";
	m_strInstrumentCode = "AAAA_BB_CC";
}



//QT_END_NAMESPACE

