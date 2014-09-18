#include "HistoryDataACK.h"
#include "ProjectUtilityFun.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <QtCore/QDateTime>
#include "Bar.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


CHistoryDataACK::CHistoryDataACK()
{
	m_pUtilityFun = NULL;
	m_pUtilityFun = new CProjectUtilityFun();

	m_nInstrumentID = 0;
	m_MapBarData.clear();
	m_nBarType = FIVE_MINUTE;//5 * 60
	m_nBarTypeSeconds = m_nBarType;
	


	
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
	m_nBarType = FIVE_MINUTE;//5 * 60
	m_nBarTypeSeconds = m_nBarType;
}

void CHistoryDataACK::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	m_nRequestID = requestID;
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

}


void CHistoryDataACK::logInfo()
{
	//if (RequestType_From_To == m_nRequestType)
	{
		LOG_DEBUG<<" "<<"RequestType_From_To"
			<<" "<<"m_nRequestID="<<m_nRequestID
			<<" "<<"m_nBarType="<<m_nBarType
			<<" "<<"m_nInstrumentID="<<m_nInstrumentID
			<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode
			<<" "<<"nFromTime="<<m_pUtilityFun->dataTimeToStr(m_nFromTime).c_str()
			<<" "<<"nToTime="<<m_pUtilityFun->dataTimeToStr(m_nToTime).c_str()
			<<" "<<"m_MapBarData.size()="<<m_MapBarData.size();

	}
}



void CHistoryDataACK::initTestData()
{
	unsigned int nBarIndex = 0;
	Bar barData;
	unsigned int nTimeNow;
	unsigned int nBarCount = 60;
	double tmp1 = 0;
	double tmp2 = 0;

	//FIVE_MINUTES
	//one bar 5 minutes  * 60
	//double nTimeNow = QDateTime::currentDateTime().toTime_t();
	nTimeNow = QDateTime::currentDateTime().toTime_t();
	nTimeNow = nTimeNow - (m_nBarTypeSeconds * nBarCount);//set start time


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
		barData.volume = 0;
		barData.timestamp = 0;

		tmp1 = ::rand() % 100;
		tmp2 = ::rand() % 100;

		barData.timestamp = nTimeNow + nIndex * m_nBarTypeSeconds;//5 minutes

		barData.open = tmp1;
		barData.close = tmp2;

		if (barData.open > barData.close)
		{
			barData.high = barData.open + 0.5;
			barData.low = barData.close - 0.5;
		}
		else
		{
			barData.high = barData.close + 0.5;
			barData.low = barData.open - 0.5;
		}


		//m_MapBarData.insert(std::map<int, Bar>::value_type(nBarIndex, barData));
		m_MapBarData.insert(nBarIndex, barData);
		nBarIndex++;
	}


}
