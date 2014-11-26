#include "MidSubWidget.h"


#include <QtGui/QVBoxLayout>
#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "HistoryDataManager.h"
#include "MidSubDrawHelper.h"
#include "qcp.h"
#include "axis.h"
#include <QtCore/QDateTime>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */


#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 200;
static int DEFVALUE_INT_Window_Height = 200;
static const std::string   DEFVALUE_String_Window_Title = "MidSubWidget";

static std::string DEF_STRING_FORMAT_TIME = "yyyy-MM-dd\nhh:mm:ss";


CMidSubWidget::CMidSubWidget(QWidget* parent)
    : QWidget(parent)
{
	m_pCustomPlotTop = NULL;
	m_pCustomPlotBottom = NULL;
	m_ScrollBar_Horizontal = NULL;
	m_pQCPItemTracerCrossHairTop = NULL;
	m_pQCPItemTracerCrossHairBottom = NULL;
	m_nCurrentInstrumentID = 0;
	m_nCurrentBarType = DAY;

	m_pMidSubDrawHelper = NULL;
	m_pMidSubDrawHelper = new CMidSubDrawHelper();

    setupUi();
	translateLanguage();


	_CreateAction();
	_CreateConnect();

}


CMidSubWidget::~CMidSubWidget()
{
	if (NULL != m_pMidSubDrawHelper)
	{
		delete m_pMidSubDrawHelper;
		m_pMidSubDrawHelper = NULL;
	}
}


QSize CMidSubWidget::sizeHint() const
{
	//for QDockWidget
	return QSize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height); /* 在这里定义dock的初始大小 */
}

void CMidSubWidget::_CreateAction()
{

}

void CMidSubWidget::_CreateConnect()
{


}
void CMidSubWidget::_InitScrollBar()
{
	if (NULL == m_ScrollBar_Horizontal)
	{
		m_ScrollBar_Horizontal = new QScrollBar(this);
		m_ScrollBar_Horizontal->setOrientation(Qt::Horizontal);
		m_ScrollBar_Horizontal->setRange(-1000, 1000);
		m_ScrollBar_Horizontal->setValue(0); // adjust position of scroll bar slider
		m_ScrollBar_Horizontal->setPageStep(500); // adjust size of scroll bar slider

	}

}

void CMidSubWidget::_InitCustomPlots()
{
	if (NULL == m_pCustomPlotTop)
	{
		m_pCustomPlotTop = new QCustomPlot(this);
		m_pCustomPlotTop->yAxis->setLabel(QObject::tr("Y-value"));
		m_pCustomPlotTop->xAxis->setLabel(QObject::tr("X-time"));	
		m_pCustomPlotTop->xAxis->setTickLabelType(QCPAxis::ltDateTime);
		m_pCustomPlotTop->xAxis->setDateTimeFormat(DEF_STRING_FORMAT_TIME.c_str());

	}

	if (NULL == m_pCustomPlotBottom)
	{
		m_pCustomPlotBottom = new QCustomPlot(this);
		m_pCustomPlotBottom->yAxis->setLabel(QObject::tr("Y-value"));
		m_pCustomPlotBottom->xAxis->setLabel(QObject::tr("X-time"));	
		m_pCustomPlotBottom->xAxis->setTickLabelType(QCPAxis::ltDateTime);
		m_pCustomPlotBottom->xAxis->setDateTimeFormat(DEF_STRING_FORMAT_TIME.c_str());

	}
	
	//
	if (NULL == m_pQCPItemTracerCrossHairTop)
	{
		m_pQCPItemTracerCrossHairTop = NULL;
		m_pQCPItemTracerCrossHairTop = new QCPItemTracerCrossHair(m_pCustomPlotTop);
		m_pCustomPlotTop->addItem(m_pQCPItemTracerCrossHairTop);
		m_pQCPItemTracerCrossHairTop->setTracerAxisRect(m_pCustomPlotTop->axisRect());
		m_pQCPItemTracerCrossHairTop->setStyle(QCPItemTracerCrossHair::tsCrosshair);
		m_pQCPItemTracerCrossHairTop->setShowLeft(QCPAxis::ltNumber, true, QString(""));
		m_pQCPItemTracerCrossHairTop->setShowBottom(QCPAxis::ltDateTime, true, QString(DEF_STRING_FORMAT_TIME.c_str()));
	}
	
	//
	if (NULL == m_pQCPItemTracerCrossHairBottom)
	{
		m_pQCPItemTracerCrossHairBottom = NULL;
		m_pQCPItemTracerCrossHairBottom = new QCPItemTracerCrossHair(m_pCustomPlotBottom);
		m_pCustomPlotBottom->addItem(m_pQCPItemTracerCrossHairBottom);
		m_pQCPItemTracerCrossHairBottom->setTracerAxisRect(m_pCustomPlotBottom->axisRect());
		m_pQCPItemTracerCrossHairBottom->setStyle(QCPItemTracerCrossHair::tsCrosshair);
		m_pQCPItemTracerCrossHairBottom->setShowLeft(QCPAxis::ltNumber, true, QString(""));
		m_pQCPItemTracerCrossHairBottom->setShowBottom(QCPAxis::ltDateTime, true, QString(DEF_STRING_FORMAT_TIME.c_str()));
	}
	
	connect(m_pCustomPlotTop, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(QCPItemTracerCrossHairMouseMove(QMouseEvent*)));
	m_pCustomPlotTop->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pCustomPlotTop->replot();//draw again

	connect(m_pCustomPlotBottom, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(QCPItemTracerCrossHairMouseMove(QMouseEvent*)));
	m_pCustomPlotBottom->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pCustomPlotBottom->replot();//draw again

}

void CMidSubWidget::setupUi()
{
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::Dialog);	

	_InitCustomPlots();
	_InitScrollBar();
	_InitUIData();

	QObject::connect(m_pCustomPlotTop->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(slotTopxAxisChanged(QCPRange)));
	QObject::connect(m_pCustomPlotBottom->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(slotBottomxAxisChanged(QCPRange)));
	QObject::connect(m_ScrollBar_Horizontal, SIGNAL(valueChanged(int)), this, SLOT(slotHorzScrollBarChanged(int)));



	//
	QVBoxLayout* pVBoxLayout = NULL;
	pVBoxLayout = new QVBoxLayout(this);
	pVBoxLayout->setSpacing(6);
	pVBoxLayout->setContentsMargins(11, 11, 11, 11);
	pVBoxLayout->addWidget(m_pCustomPlotTop);
	pVBoxLayout->addWidget(m_pCustomPlotBottom);
	pVBoxLayout->addWidget(m_ScrollBar_Horizontal);
	this->setLayout(pVBoxLayout);
	//setGeometry(400, 250, 542, 390);	
	QMetaObject::connectSlotsByName(this);
} 
void CMidSubWidget::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title.c_str()));

}



void CMidSubWidget::doTest()
{



}


void CMidSubWidget::slotHistoryDataChanged( CHistoryDataManager* pHistoryDataManager )
{
	//emit
	{
		MYLOG4CPP_DEBUG<<"CMidSubWidget process slotHistoryDataChanged"
			<<" "<<"param:"
			<<" "<<"pHistoryDataManager=0x"<<pHistoryDataManager;
	}

	if ((m_nCurrentInstrumentID != pHistoryDataManager->getInstrumentID()) && (0 != m_nCurrentInstrumentID))
	{
		MYLOG4CPP_DEBUG<<" "<<"CMidSubWidget m_nCurrentInstrumentID="<<m_nCurrentInstrumentID
			<<" "<<"but CHistoryDataManager InstrumentID="<<pHistoryDataManager->getInstrumentID()
			<<" "<<"not draw bar";
		return;
	}
	m_nCurrentInstrumentID = pHistoryDataManager->getInstrumentID();

	m_pCustomPlotTop->clearGraphs();
	m_pCustomPlotTop->clearPlottables();

	m_pCustomPlotBottom->clearGraphs();
	m_pCustomPlotBottom->clearPlottables();

	m_pMidSubDrawHelper->drawHistoryBarData(pHistoryDataManager, m_pCustomPlotTop, m_pCustomPlotTop->axisRect());//m_pAxisRectTop
	m_pMidSubDrawHelper->drawHistoryVolumeData(pHistoryDataManager, m_pCustomPlotBottom,  m_pCustomPlotBottom->axisRect());//m_pAxisRectBottom


	//m_pCustomPlot->rescaleAxes();
	//m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pCustomPlotTop->replot();//draw again
	m_pCustomPlotBottom->replot();//draw again

}

void CMidSubWidget::QCPItemTracerCrossHairMouseMove( QMouseEvent *event )
{
	if (NULL != m_pQCPItemTracerCrossHairTop)
	{ 
		QPointF pointfValue_e_QPointF;
		pointfValue_e_QPointF = event->posF();
		m_pQCPItemTracerCrossHairTop->setCenterPos(pointfValue_e_QPointF);
	}

	if (NULL != m_pQCPItemTracerCrossHairBottom)
	{
		QPointF pointfValue_e_QPointF;
		pointfValue_e_QPointF = event->posF();
		m_pQCPItemTracerCrossHairBottom->setCenterPos(pointfValue_e_QPointF);
	}


	m_pCustomPlotTop->replot();
	m_pCustomPlotBottom->replot();
}

void CMidSubWidget::setCurrentInstrumentID( unsigned int nInstrumentID )
{
	m_nCurrentInstrumentID = nInstrumentID;

	MYLOG4CPP_DEBUG<<"CMidSubWidget setCurrentInstrumentID"
		<<" "<<"m_nCurrentInstrumentID="<<m_nCurrentInstrumentID;
}

unsigned int CMidSubWidget::getCurrentInstrumentID()
{
	return m_nCurrentInstrumentID;
}

void CMidSubWidget::setHistoryBarType( enum BarType nBarType )
{
	m_nCurrentBarType = nBarType;
	MYLOG4CPP_DEBUG<<"CMidSubWidget setHistoryBarType"
		<<" "<<"m_nCurrentBarType="<<m_nCurrentBarType;

}

enum BarType CMidSubWidget::getHistoryBarType()
{
	return m_nCurrentBarType;
}

void CMidSubWidget::slotHorzScrollBarChanged( int value )
{
	double fValueCenter = 0.0;
	double fChangeValue = 0.0;
	QCPRange rangeXAxis;
	double rangeSize = 0.0;
	double newPostion = 0.0;

	rangeXAxis = m_pCustomPlotTop->xAxis->range();
	rangeSize = rangeXAxis.size();

	fValueCenter = m_pCustomPlotTop->xAxis->range().center();
	fChangeValue = qAbs(fValueCenter - value);

	newPostion = value;

	if (fChangeValue > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		m_pCustomPlotTop->xAxis->setRange(newPostion, rangeSize, Qt::AlignCenter);
		m_pCustomPlotBottom->yAxis->setRange(newPostion, rangeSize, Qt::AlignCenter);

		m_pCustomPlotTop->replot();
		m_pCustomPlotBottom->replot();
	}	
}



void CMidSubWidget::slotTopxAxisChanged(QCPRange range)
{
	m_ScrollBar_Horizontal->setValue(qRound(range.center())); // adjust position of scroll bar slider
	m_ScrollBar_Horizontal->setPageStep(qRound(range.size())); // adjust size of scroll bar slider
	
	m_pCustomPlotBottom->yAxis->setRange(range);
	m_pCustomPlotBottom->replot();

}
void CMidSubWidget::slotBottomxAxisChanged(QCPRange range)
{
	m_ScrollBar_Horizontal->setValue(qRound(range.center())); // adjust position of scroll bar slider
	m_ScrollBar_Horizontal->setPageStep(qRound(range.size())); // adjust size of scroll bar slider

	m_pCustomPlotTop->yAxis->setRange(range);
	m_pCustomPlotTop->replot();

}


void CMidSubWidget::_InitUIData()
{
	if (NULL == m_pCustomPlotTop
		|| NULL == m_pCustomPlotBottom
		|| NULL == m_ScrollBar_Horizontal)
	{
		return;
	}

	unsigned int nTimeFrom = 0;
	unsigned int nTimeTo = 0;
	double nLeftAxisRangeMinAdjuest = 0;
	double nLeftAxisRangeMaxAdjuest = 0;
	double fPositionValue = 0.0;
	double fSizeValue = 0.0;
	Qt::AlignmentFlag nAlignment = Qt::AlignCenter;

	nTimeFrom = 0;
	nTimeTo = MONTH;
	nLeftAxisRangeMinAdjuest = 0;
	nLeftAxisRangeMaxAdjuest = 100;

	fSizeValue = nTimeTo - nTimeFrom;
	fPositionValue = nTimeFrom + (fSizeValue/3);//3 page
	nAlignment = Qt::AlignCenter;

	m_pCustomPlotTop->xAxis->setRange(fPositionValue, fSizeValue, nAlignment);
	m_pCustomPlotTop->yAxis->setRange(nLeftAxisRangeMinAdjuest, nLeftAxisRangeMaxAdjuest);
	m_pCustomPlotBottom->xAxis->setRange(fPositionValue, fSizeValue, nAlignment);
	m_pCustomPlotBottom->yAxis->setRange(nLeftAxisRangeMinAdjuest, nLeftAxisRangeMaxAdjuest);
	m_ScrollBar_Horizontal->setRange(m_pCustomPlotTop->xAxis->range().lower, m_pCustomPlotTop->xAxis->range().upper);
	m_ScrollBar_Horizontal->setValue(m_pCustomPlotTop->xAxis->range().center());
	m_ScrollBar_Horizontal->setPageStep(qRound(m_pCustomPlotTop->xAxis->range().size())); // adjust size of scroll bar slider

	m_pCustomPlotTop->replot();//draw again
	m_pCustomPlotBottom->replot();//draw again

}
