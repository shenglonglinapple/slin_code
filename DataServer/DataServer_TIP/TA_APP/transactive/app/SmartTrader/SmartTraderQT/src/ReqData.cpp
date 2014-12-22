#include "ReqData.h"

#include <QtCore/QDateTime>
#include "QtTimeHelper.h"

CReqData::CReqData()
{
	m_nReqType = EReqType_Begin;
}

CReqData::~CReqData( void )
{

}
void CReqData::setAutoRequestUUID()
{
	CQtTimeHelper timeHelper;

	m_strRequestUUID = timeHelper.getUUID();
}

QString CReqData::getRequestUUID()
{
	return m_strRequestUUID;
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

void CReqData::setMyBarType(EMyBarType nMyBarType)
{
	m_nMyBarType = nMyBarType;
}
EMyBarType CReqData::getMyBarType()
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

void CReqData::setVolume( int nVolume )
{
	m_nVolume = nVolume;
}

int CReqData::getVolume()
{
	return m_nVolume;
}
