#include "MidSubDrawHelper.h"
#include "ProjectUtilityFun.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <QtCore/QDateTime>
#include "Bar.h"
#include "HistoryDataManager.h"

#include "qcustomplot.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


CMidSubDrawHelper::CMidSubDrawHelper()
{

}

CMidSubDrawHelper::~CMidSubDrawHelper()
{

}


void CMidSubDrawHelper::drawHistoryData(CHistoryDataManager* pHistoryDataManager, QCustomPlot* pCustomPlot)
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
	int nBarWith = pHistoryDataManager->getBarType();//FIVE_MINUTES
	nTimeFrom = pHistoryDataManager->getTimeFrom();
	nTimeTo = pHistoryDataManager->getTimeTo();

	// prepare axes:
	pCustomPlot->xAxis->setLabel(QObject::tr("X-time"));
	pCustomPlot->yAxis->setLabel(QObject::tr("Y-value"));

	// configure bottom axis to show date and time instead of number:
	pCustomPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
	pCustomPlot->xAxis->setDateTimeFormat("yyyy-MM-dd\nhh-mm-ss");

	// make key axis range scroll with the data (at a constant range size of 8):
	pCustomPlot->xAxis->setRange(nTimeFrom, nTimeTo);
	//customPlot->yAxis->setRange(0, 200);
	// show legend:
	pCustomPlot->legend->setVisible(false);

	nIndex = 0;
	iterMap = pHistoryDataManager->m_pHistoryACK->m_MapBarData.begin();
	while (iterMap != pHistoryDataManager->m_pHistoryACK->m_MapBarData.end())
	{
		//iterMap->second;
		// create empty statistical box plottables:
		pStatisticalBoxRef = NULL;
		pStatisticalBoxRef = new QCPStatisticalBox(pCustomPlot->xAxis, pCustomPlot->yAxis);
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
		pStatisticalBoxRef->setKey(iterMap->timestamp);
		pStatisticalBoxRef->setMinimum(fMinimum);
		pStatisticalBoxRef->setLowerQuartile(fLowerQuartile);
		pStatisticalBoxRef->setMedian(fLowerQuartile);
		pStatisticalBoxRef->setUpperQuartile(fUpperQuartile);
		pStatisticalBoxRef->setMaximum(fMaximum);

		//pStatisticalBoxTmp->setWidth(1);//矩形宽度
		pStatisticalBoxRef->setWidth(nBarWith);//矩形宽度

		pStatisticalBoxRef->setWhiskerWidth(0);//上顶，下底 直线宽度

		nIndex++;
		iterMap++;
	}//while


	pCustomPlot->rescaleAxes();
	pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
