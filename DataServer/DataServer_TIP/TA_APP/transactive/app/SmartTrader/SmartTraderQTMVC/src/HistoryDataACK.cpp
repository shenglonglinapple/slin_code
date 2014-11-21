#include "HistoryDataACK.h"
#include "ProjectUtilityFun.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <QtCore/QDateTime>
#include "Bar.h"

#include "Log4cppLogger.h"



CHistoryDataACK::CHistoryDataACK()
{
	m_pUtilityFun = NULL;
	m_pUtilityFun = new CProjectUtilityFun();

	m_nInstrumentID = 0;
	m_MapBarData.clear();
	
}

CHistoryDataACK::~CHistoryDataACK()
{
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}
	m_nInstrumentID = 0;
	m_MapBarData.clear();
}

void CHistoryDataACK::onHistoryDataDownloaded(BarsPtr bars )
{
	//std::set<Bar>;
	Bars::iterator iterSet;
	iterSet = bars->begin();

	m_MapBarData.clear();

	while (iterSet != bars->end())
	{
		Bar newBar = (*iterSet);
		m_MapBarData.insert(newBar.timestamp, newBar);
		iterSet++;
	}

	_ResetTimeValue();
}

void CHistoryDataACK::onBarDataUpdate( const BarSummary &barData )
{
	std::map<int, Bar>::const_iterator iterMap;// bars; //bars indexed by interval

	iterMap = barData.bars.begin();
	while (iterMap != barData.bars.end())
	{
		Bar newBar = iterMap->second;// (*iterMap).second;
		m_MapBarData.insert(newBar.timestamp, newBar);
		iterMap++;
	}

	_ResetTimeValue();
}

void CHistoryDataACK::_ResetTimeValue()
{
	QMap<unsigned int, Bar>::iterator iterMapFirst;
	QMap<unsigned int, Bar>::iterator iterMapLast;
	//if (RequestType_From_To == m_nRequestType)
	if (m_MapBarData.size() > 0)
	{
		iterMapFirst = m_MapBarData.begin();
		iterMapLast = m_MapBarData.end();
		iterMapLast--;

		m_nTimeFrom = iterMapFirst->timestamp;
		m_nTimeTo = iterMapLast->timestamp;

		m_strTimeFrom = m_pUtilityFun->dateTimeToStr_Qt(m_nTimeFrom);
		//m_strTimeFrom = m_pUtilityFun->dateTimeToStr_Qt(m_nTimeFrom);
		
		m_strTimeTo = m_pUtilityFun->dateTimeToStr_Qt(m_nTimeTo);
		//m_strTimeTo = m_pUtilityFun->dateTimeToStr_Qt(m_nTimeTo);
	}
}
void CHistoryDataACK::logInfo(const std::string& file, int line)
{

	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode
		<<" "<<"m_MapBarData.size()="<<m_MapBarData.size()
		<<" "<<"nFromTime="<<m_strTimeFrom
		<<" "<<"nToTime="<<m_strTimeTo;
}



void CHistoryDataACK::initTestData()
{
	unsigned int nBarIndex = 0;
	Bar barData;
	unsigned int nTimeNow;
	unsigned int nBarCount = 200;
	double tmp1 = 0;
	double tmp2 = 0;
	int nBarTypeSeconds = m_nBarType;//FIVE_MINUTE;

	//FIVE_MINUTES
	//one bar 5 minutes  * 60
	//double nTimeNow = QDateTime::currentDateTime().toTime_t();
	nTimeNow = QDateTime::currentDateTime().toTime_t();
	nTimeNow = nTimeNow - (nBarTypeSeconds * nBarCount);//set start time


	//::srand(8); // set the random seed, so we always get the same random data
	//FIVE_MINUTES
	//60  * 5 = 300 minutes  6 houres
	nBarIndex = 0;
	for (unsigned int nIndex = 0; nIndex < nBarCount; nIndex++)
	{
		barData.low = 0;
		barData.high = 0;
		barData.open = 0;
		barData.close = 0;
		barData.volume = ::rand() % 100;
		barData.timestamp = 0;

		tmp1 = ::rand() % 100;
		tmp2 = ::rand() % 100;

		barData.timestamp = nTimeNow + nIndex * nBarTypeSeconds;//m_nBarType;//FIVE_MINUTE;

		barData.open = tmp1;
		barData.close = tmp2;

		if (barData.open > barData.close)
		{
			barData.high = barData.open + 5;
			barData.low = barData.close - 5;
		}
		else
		{
			barData.high = barData.close + 5;
			barData.low = barData.open - 5;
		}


		//m_MapBarData.insert(std::map<int, Bar>::value_type(nBarIndex, barData));
		m_MapBarData.insert(nBarIndex, barData);
		nBarIndex++;
	}

	_ResetTimeValue();

}

unsigned int CHistoryDataACK::getTimeFrom()
{
	_ResetTimeValue();
	return m_nTimeFrom;
}

unsigned int CHistoryDataACK::getTimeTo()
{
	_ResetTimeValue();
	return m_nTimeTo;
}

BarType CHistoryDataACK::getBarType()
{
	return m_nBarType;
}
void CHistoryDataACK::setBarType( BarType nBarType )
{
	m_nBarType = nBarType;
}

void CHistoryDataACK::setInstrumentID( unsigned int nInstrumentID )
{
	m_nInstrumentID = nInstrumentID;
}

unsigned int CHistoryDataACK::getInstrumentID()
{
	return m_nInstrumentID;
}

