#include "InstrumentBarInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

QT_BEGIN_NAMESPACE


CInstrumentBarInfo::CInstrumentBarInfo(int interval, Bar& barInfo)
{
	BOOST_LOG_FUNCTION();
	m_nInterval = interval;
	m_BarInfo = barInfo;

}

CInstrumentBarInfo::~CInstrumentBarInfo(void)
{
	BOOST_LOG_FUNCTION();
}


CInstrumentBarInfo& CInstrumentBarInfo::operator=(const CInstrumentBarInfo& instrumentBarInfo )
{
	BOOST_LOG_FUNCTION();
	m_nInterval = instrumentBarInfo.m_nInterval;
	m_BarInfo = instrumentBarInfo.m_BarInfo;
	return *this;
}




void CInstrumentBarInfo::logInfo()
{
	BOOST_LOG_FUNCTION();

	return;
}


QT_END_NAMESPACE
















