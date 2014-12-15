#include "ReqData.h"

#include <QtCore/QDateTime>

CReqData::CReqData()
{
	m_nReqType = EReqType_Begin;
}

CReqData::~CReqData( void )
{

}
void CReqData::setAutoRequestID()
{
	QDateTime time_local;
	time_t timeGetTimeValue;

	time_local = QDateTime::currentDateTime();

	timeGetTimeValue = time_local.toTime_t();

	m_nRequestID = timeGetTimeValue;
}
void CReqData::setRequestID(unsigned int nRequestID)
{
	m_nRequestID = nRequestID;
}
unsigned int CReqData::getRequestID()
{
	return m_nRequestID;
}
void CReqData::setReqType( EReqType nReqType )
{
	m_nReqType = nReqType;
}

EReqType CReqData::getReqType()
{
	return m_nReqType;
}

void CReqData::setInstrumentCode( const std::string& strInstrumentCode )
{
	m_strInstrumentCode = strInstrumentCode;
}

std::string CReqData::getInstrumentCode()
{
	return m_strInstrumentCode;
}

void CReqData::setMyBarType(BarType nMyBarType)
{
	m_nMyBarType = nMyBarType;
}
BarType CReqData::getMyBarType()
{
	return m_nMyBarType;
}


void CReqData::setTimeFrom( const std::string& strTimeFrom )
{
	m_strTimeFrom = strTimeFrom;
}

std::string CReqData::getTimeFrom()
{
	return m_strTimeFrom;
}

void CReqData::setTimeTo( const std::string& strTimeTo )
{
	m_strTimeTo = strTimeTo;
}

std::string CReqData::getTimeTo()
{
	return m_strTimeTo;
}
