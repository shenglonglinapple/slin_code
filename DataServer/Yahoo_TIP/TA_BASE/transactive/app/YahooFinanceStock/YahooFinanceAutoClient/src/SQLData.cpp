#include "SQLData.h"

CSQLData::CSQLData()
{

}

CSQLData::~CSQLData()
{

}

CSQLData& CSQLData::operator=( const CSQLData& objectCopy )
{
	m_strDataKey = objectCopy.m_strDataKey;
	return *this;
}

