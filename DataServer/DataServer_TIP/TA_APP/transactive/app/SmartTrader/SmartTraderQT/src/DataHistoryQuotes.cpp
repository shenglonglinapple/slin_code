#include "DataHistoryQuotes.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <QtCore/QDateTime>
#include "MyBar.h"

#include "QtTimeHelper.h"

#include "Log4cppLogger.h"



CDataHistoryQuotes::CDataHistoryQuotes()
{
	m_nInstrumentID = 0;
	m_nBarType = FIVE_SECOND;
	m_MapBarData.clear();	
}

CDataHistoryQuotes::~CDataHistoryQuotes()
{
	m_nInstrumentID = 0;
	m_nBarType = FIVE_SECOND;
	m_MapBarData.clear();
}

void CDataHistoryQuotes::onHistoryDataDownloaded(pSetMyBarsPtr bars )
{
	//std::set<Bar>;
	setMyBars::iterator iterSet;
	iterSet = bars->begin();

	m_MapBarData.clear();

	while (iterSet != bars->end())
	{
		CMyBar newBar = (*iterSet);
		m_MapBarData.insert(newBar.timestamp, newBar);//duplick will not insert 
		iterSet++;
	}

	_ResetTimeValue();
}

void CDataHistoryQuotes::onBarDataUpdate( const CMyBarSummary &barData )
{
	std::map<int, CMyBar>::const_iterator iterMap;// bars; //bars indexed by interval

	iterMap = barData.bars.begin();
	while (iterMap != barData.bars.end())
	{
		CMyBar newBar = iterMap->second;// (*iterMap).second;
		m_MapBarData.insert(newBar.timestamp, newBar);//duplick will not insert 
		iterMap++;
	}

	_ResetTimeValue();
}

void CDataHistoryQuotes::_ResetTimeValue()
{
	QMap<unsigned int, CMyBar>::iterator iterMapFirst;
	QMap<unsigned int, CMyBar>::iterator iterMapLast;
	CQtTimeHelper timeHelper;
	//if (RequestType_From_To == m_nRequestType)
	if (m_MapBarData.size() > 0)
	{
		iterMapFirst = m_MapBarData.begin();
		iterMapLast = m_MapBarData.end();
		iterMapLast--;

		m_nTimeFrom = iterMapFirst->timestamp;
		m_nTimeTo = iterMapLast->timestamp;

		m_strTimeFrom = timeHelper.dateTimeToStr_Qt(m_nTimeFrom);
		//m_strTimeFrom = m_pUtilityFun->dateTimeToStr_Qt(m_nTimeFrom);
		
		m_strTimeTo = timeHelper.dateTimeToStr_Qt(m_nTimeTo);
		//m_strTimeTo = m_pUtilityFun->dateTimeToStr_Qt(m_nTimeTo);
	}
}
void CDataHistoryQuotes::logInfo(const std::string& file, int line)
{

	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode
		<<" "<<"m_MapBarData.size()="<<m_MapBarData.size()
		<<" "<<"nFromTime="<<m_strTimeFrom
		<<" "<<"nToTime="<<m_strTimeTo;
}



void CDataHistoryQuotes::initTestData()
{
	unsigned int nBarIndex = 0;
	CMyBar barData;
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

unsigned int CDataHistoryQuotes::getTimeFrom()
{
	_ResetTimeValue();
	return m_nTimeFrom;
}

unsigned int CDataHistoryQuotes::getTimeTo()
{
	_ResetTimeValue();
	return m_nTimeTo;
}

EMyBarType  CDataHistoryQuotes::getBarType()
{
	return m_nBarType;
}
void CDataHistoryQuotes::setBarType( EMyBarType  nBarType )
{
	if (nBarType != m_nBarType)
	{
		m_MapBarData.clear();
		m_nBarType = nBarType;
	}
}


