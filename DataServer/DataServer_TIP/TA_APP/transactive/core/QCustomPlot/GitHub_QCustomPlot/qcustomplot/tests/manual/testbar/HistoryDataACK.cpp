#include "HistoryDataACK.h"

#include <set>
#include <stdlib.h>
#include <math.h>
#include <QtCore/QDateTime>
#include "Bar.h"




CHistoryDataACK::CHistoryDataACK()
{

	m_nInstrumentID = 0;
	m_MapBarData.clear();
	m_nBarType = FIVE_SECOND;
}

CHistoryDataACK::~CHistoryDataACK()
{

	m_nInstrumentID = 0;
	m_MapBarData.clear();
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

		//m_strTimeFrom = m_pUtilityFun->dataTimeToStr(m_nTimeFrom);
		//m_strTimeTo = m_pUtilityFun->dataTimeToStr(m_nTimeTo);
	}
}
void CHistoryDataACK::logInfo()
{


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

