#include "SymbolUseManager.h"
#include "Log4cppLogger.h"


static const int DEF_VALUE_UPDATE_FAILED_COUNT = 2;

CSymbolUseManager::CSymbolUseManager( void )
{
	_Clear();
}

CSymbolUseManager::~CSymbolUseManager( void )
{
	_Clear();
}


CSymbolUseManager& CSymbolUseManager::operator=( const CSymbolUseManager& objectCopy )
{
	m_strSymbolUse = objectCopy.m_strSymbolUse;
	m_strMaxTime = objectCopy.m_strMaxTime;
	m_nUpdateFailed = objectCopy.m_nUpdateFailed;

	return *this;
}

void CSymbolUseManager::_Clear()
{
	m_strSymbolUse.clear();
	m_strMaxTime.clear();
	m_nUpdateFailed = 0;
}

void CSymbolUseManager::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CSymbolUseManager:"
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strMaxTime="<<m_strMaxTime
		<<" "<<"m_nUpdateFailed="<<m_nUpdateFailed;
}

int CSymbolUseManager::getMaxUpdateFailedCount()
{
	return DEF_VALUE_UPDATE_FAILED_COUNT;
}
