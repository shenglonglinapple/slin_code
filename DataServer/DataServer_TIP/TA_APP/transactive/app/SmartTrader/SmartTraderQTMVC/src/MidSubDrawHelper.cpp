#include "MidSubDrawHelper.h"
#include "ProjectUtilityFun.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <QtCore/QDateTime>
#include "Bar.h"
#include "HistoryDataManager.h"

#include "qcp.h"

#include "Log4cppLogger.h"


static std::string DEF_STRING_FORMAT_TIME = "yyyy-MM-dd\nhh:mm:ss";

CMidSubDrawHelper::CMidSubDrawHelper()
{

}

CMidSubDrawHelper::~CMidSubDrawHelper()
{

}


void CMidSubDrawHelper::drawHistoryBarData(CHistoryDataManager* pHistoryDataManager, QCustomPlot* pCustomPlot, QCPAxisRect* pRect)
{
	QBrush redBrush(QColor(255, 0, 0, 255));//red
	QPen redPen(QColor(255, 0, 0, 255));//red
	QBrush greenBrush(QColor(0, 255, 0, 255));//green
	QPen greenPen(QColor(0, 255, 0, 255));//green

	QBrush* pBoxBrushRef = NULL;
	QPen* pBoxPenRef = NULL;
	QCPStatisticalBox *pStatisticalBoxRef = NULL;

	double fMinimum = 0;
	double fMaximum = 0;
	double fLowerQuartile = 0;
	double fUpperQuartile = 0;

	QMap<unsigned int, Bar>::iterator iterMap;
	int nIndex = 0;
	unsigned int nTimeFrom = 0;
	unsigned int nTimeTo = 0;
	double nLeftAxisRangeMin = 0;
	double nLeftAxisRangeMax = 0;
	double nLeftAxisRangeMinAdjuest = 0;
	double nLeftAxisRangeMaxAdjuest = 0;

	int nBarWith = 0;
	nBarWith = pHistoryDataManager->getBarType();//FIVE_MINUTES
	nTimeFrom = pHistoryDataManager->getTimeFrom();
	nTimeTo = pHistoryDataManager->getTimeTo();

	// prepare axes:
	pRect->axis(QCPAxis::atLeft)->setLabel(QObject::tr("Y-value"));
	pRect->axis(QCPAxis::atBottom)->setLabel(QObject::tr("X-time"));
	pRect->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
	pRect->axis(QCPAxis::atBottom)->setDateTimeFormat(DEF_STRING_FORMAT_TIME.c_str());


	nIndex = 0;
	iterMap = pHistoryDataManager->m_pHistoryACK->m_MapBarData.begin();
	if (iterMap != pHistoryDataManager->m_pHistoryACK->m_MapBarData.end())
	{
		//init first value
		nLeftAxisRangeMin = iterMap->low;
		nLeftAxisRangeMax = iterMap->high;
	}
	while (iterMap != pHistoryDataManager->m_pHistoryACK->m_MapBarData.end())
	{
		//iterMap->second;
		// create empty statistical box plottables:
		pStatisticalBoxRef = NULL;
		pStatisticalBoxRef = new QCPStatisticalBox(pRect->axis(QCPAxis::atBottom), pRect->axis(QCPAxis::atLeft));
		pCustomPlot->addPlottable(pStatisticalBoxRef);

		fMinimum = iterMap->low;
		fMaximum= iterMap->high;

		if (iterMap->open > iterMap->close)
		{
			//high->low
			fLowerQuartile = iterMap->close;
			fUpperQuartile = iterMap->open;
			pBoxBrushRef = &redBrush;
			pBoxPenRef = &redPen;
		}
		else
		{
			fLowerQuartile = iterMap->open;
			fUpperQuartile = iterMap->close;
			pBoxBrushRef = &greenBrush;
			pBoxPenRef = &greenPen;
		}

		//boxBrush.setStyle(Qt::SolidPattern); // make it look oldschool Qt::SolidPattern  Qt::Dense6Pattern
		pStatisticalBoxRef->setBrush(*pBoxBrushRef);
		pStatisticalBoxRef->setPen(*pBoxPenRef);
		pStatisticalBoxRef->setWhiskerPen(*pBoxPenRef);
		pStatisticalBoxRef->setWhiskerBarPen(*pBoxPenRef);
		pStatisticalBoxRef->setMedianPen(*pBoxPenRef);

		// set data:
		//pStatisticalBoxTmp->setKey(nIndex);
		pStatisticalBoxRef->setBoxType(QCPStatisticalBox::btBar);
		pStatisticalBoxRef->setKey(iterMap->timestamp);
		pStatisticalBoxRef->setMinimum(fMinimum);
		pStatisticalBoxRef->setLowerQuartile(fLowerQuartile);
		pStatisticalBoxRef->setMedian(fLowerQuartile);
		pStatisticalBoxRef->setUpperQuartile(fUpperQuartile);
		pStatisticalBoxRef->setMaximum(fMaximum);

		//pStatisticalBoxTmp->setWidth(1);//矩形宽度
		pStatisticalBoxRef->setWidth(nBarWith);//矩形宽度

		pStatisticalBoxRef->setWhiskerWidth(0);//上顶，下底 直线宽度


		if (fMinimum < nLeftAxisRangeMin)
		{
			nLeftAxisRangeMin = fMinimum;
		}

		if (fMaximum > nLeftAxisRangeMax)
		{
			nLeftAxisRangeMax = fMaximum;
		}

		nIndex++;
		iterMap++;
	}//while

	// make key axis range scroll with the data (at a constant range size of 8):
	pRect->axis(QCPAxis::atBottom)->setRange(nTimeFrom, nTimeTo);
	nLeftAxisRangeMinAdjuest = nLeftAxisRangeMin * (1 - 5/100);
	nLeftAxisRangeMaxAdjuest = nLeftAxisRangeMax * (1 + 5/100);
	pRect->axis(QCPAxis::atLeft)->setRange(nLeftAxisRangeMinAdjuest, nLeftAxisRangeMaxAdjuest);

// 	pCustomPlot->rescaleAxes();
// 	pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

	pBoxBrushRef = NULL;
	pBoxPenRef = NULL;
	pStatisticalBoxRef = NULL;
}



void CMidSubDrawHelper::drawHistoryVolumeData(CHistoryDataManager* pHistoryDataManager, QCustomPlot* pCustomPlot, QCPAxisRect* pRect)
{
	QBrush redBrush(QColor(255, 0, 0, 255));//red
	QPen redPen(QColor(255, 0, 0, 255));//red
	QBrush greenBrush(QColor(0, 255, 0, 255));//green
	QPen greenPen(QColor(0, 255, 0, 255));//green


	QBrush* pBoxBrushRef = NULL;
	QPen* pBoxPenRef = NULL;
	QCPStatisticalBox *pStatisticalBoxRef = NULL;


	double fMinimum = 0;
	double fMaximum = 0;
	double fLowerQuartile = 0;
	double fUpperQuartile = 0;

	QMap<unsigned int, Bar>::iterator iterMap;
	int nIndex = 0;
	unsigned int nTimeFrom = 0;
	unsigned int nTimeTo = 0;
	double nLeftAxisRangeMin = 0;
	double nLeftAxisRangeMax = 0;
	double nLeftAxisRangeMinAdjuest = 0;
	double nLeftAxisRangeMaxAdjuest = 0;
	int nBarWith = 0;
	nBarWith = pHistoryDataManager->getBarType();//FIVE_MINUTES
	nTimeFrom = pHistoryDataManager->getTimeFrom();
	nTimeTo = pHistoryDataManager->getTimeTo();

	// prepare axes:
	pRect->axis(QCPAxis::atLeft)->setLabel(QObject::tr("Y-value"));
	pRect->axis(QCPAxis::atBottom)->setLabel(QObject::tr("X-time"));
	pRect->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
	pRect->axis(QCPAxis::atBottom)->setDateTimeFormat(DEF_STRING_FORMAT_TIME.c_str());



	nIndex = 0;
	iterMap = pHistoryDataManager->m_pHistoryACK->m_MapBarData.begin();
	while (iterMap != pHistoryDataManager->m_pHistoryACK->m_MapBarData.end())
	{
		//iterMap->second;
		// create empty statistical box plottables:
		pStatisticalBoxRef = NULL;
		pStatisticalBoxRef = new QCPStatisticalBox(pRect->axis(QCPAxis::atBottom), pRect->axis(QCPAxis::atLeft));
		pCustomPlot->addPlottable(pStatisticalBoxRef);

		if (iterMap->open > iterMap->close)
		{
			//high->low
			pBoxBrushRef = &redBrush;
			pBoxPenRef = &redPen;
		}
		else
		{
			pBoxBrushRef = &greenBrush;
			pBoxPenRef = &greenPen;
		}

		fMinimum = 0;
		fLowerQuartile = 0;
		fUpperQuartile = iterMap->volume;
		fMaximum = fUpperQuartile;

		//boxBrush.setStyle(Qt::SolidPattern); // make it look oldschool Qt::SolidPattern  Qt::Dense6Pattern
		pStatisticalBoxRef->setBrush(*pBoxBrushRef);
		pStatisticalBoxRef->setPen(*pBoxPenRef);
		pStatisticalBoxRef->setWhiskerPen(*pBoxPenRef);
		pStatisticalBoxRef->setWhiskerBarPen(*pBoxPenRef);
		pStatisticalBoxRef->setMedianPen(*pBoxPenRef);

		// set data:
		//pStatisticalBoxTmp->setKey(nIndex);
		pStatisticalBoxRef->setBoxType(QCPStatisticalBox::btVolume);
		pStatisticalBoxRef->setKey(iterMap->timestamp);		
		pStatisticalBoxRef->setMinimum(fMinimum);
		pStatisticalBoxRef->setLowerQuartile(fLowerQuartile);
		pStatisticalBoxRef->setMedian(fLowerQuartile);
		pStatisticalBoxRef->setUpperQuartile(fUpperQuartile);
		pStatisticalBoxRef->setMaximum(fMaximum);

		//pStatisticalBoxTmp->setWidth(1);//矩形宽度
		pStatisticalBoxRef->setWidth(nBarWith);//矩形宽度
		pStatisticalBoxRef->setWhiskerWidth(0);//上顶，下底 直线宽度

		if (fMinimum < nLeftAxisRangeMin)
		{
			nLeftAxisRangeMin = fMinimum;
		}
		
		if (fMaximum > nLeftAxisRangeMax)
		{
			nLeftAxisRangeMax = fMaximum;
		}

		nIndex++;
		iterMap++;
	}//while

	// make key axis range scroll with the data (at a constant range size of 8):
	pRect->axis(QCPAxis::atBottom)->setRange(nTimeFrom, nTimeTo);
	nLeftAxisRangeMaxAdjuest = nLeftAxisRangeMax * (1 + 5/100);
	pRect->axis(QCPAxis::atLeft)->setRange(nLeftAxisRangeMin, nLeftAxisRangeMaxAdjuest);

	pBoxBrushRef = NULL;
	pBoxPenRef = NULL;
	pStatisticalBoxRef = NULL;
}

