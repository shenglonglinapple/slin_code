#include "HistoryData.h"



CHistoryData::CHistoryData()
{
	_Init();
}

CHistoryData::~CHistoryData()
{
	
}

CHistoryData& CHistoryData::operator=( const CHistoryData& objectCopy )
{
	m_strDate = objectCopy.m_strDate;
	m_strOpen = objectCopy.m_strOpen;
	m_strHigh = objectCopy.m_strHigh;
	m_strLow = objectCopy.m_strLow;
	m_strClose = objectCopy.m_strClose;
	m_strVolume = objectCopy.m_strVolume;
	m_strAdjClose = objectCopy.m_strAdjClose;
	
	return *this;
}

/*
Date,Open,High,Low,Close,Volume,Adj Close
2014-11-14,9.27,9.27,9.27,9.27,000,9.27
*/
void CHistoryData::resetValue(const QString& strLine)
{
	QStringList strLstData;
	int nIndex = 0;

	_Init();

	strLstData = strLine.split(",");
	if (7 == strLstData.size())
	{
		nIndex = 0;
		m_strDate = strLstData[nIndex];
		m_strDate += " 23:00:00";

		nIndex++;
		m_strOpen = strLstData[nIndex];
		nIndex++;
		m_strHigh = strLstData[nIndex];
		nIndex++;
		m_strLow = strLstData[nIndex];
		nIndex++;
		m_strClose = strLstData[nIndex];
		nIndex++;
		m_strVolume = strLstData[nIndex];
		nIndex++;
		m_strAdjClose = strLstData[nIndex];
	}

}

void CHistoryData::_Init()
{
	m_strDate.clear();
	m_strOpen.clear();
	m_strHigh.clear();
	
	m_strLow.clear();
	m_strClose.clear();
	m_strVolume.clear();
	
	m_strAdjClose.clear();

}

