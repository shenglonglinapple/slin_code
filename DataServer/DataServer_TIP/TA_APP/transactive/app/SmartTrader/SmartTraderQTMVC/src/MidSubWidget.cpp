#include "MidSubWidget.h"



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
	m_pCustomPlot = NULL;
	m_ScrollBar_Vertical = NULL;
	m_ScrollBar_Horizontal = NULL;
	m_pAxisRectTop = NULL;
	m_pAxisRectBottom = NULL;
	m_pMarginGroup = NULL;
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
	// create connection between axes and scroll bars:

	QObject::connect(m_ScrollBar_Vertical, SIGNAL(valueChanged(int)), 
		this, SLOT(slotVertScrollBarChanged(int)));
	QObject::connect(m_ScrollBar_Horizontal, SIGNAL(valueChanged(int)), 
		this, SLOT(slotHorzScrollBarChanged(int)));

	connect(m_pCustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), 
		this, SLOT(slotQCustomPlotxAxisChanged(QCPRange)));
	connect(m_pCustomPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), 
		this, SLOT(slotQCustomPlotyAxisChanged(QCPRange)));
}


void CMidSubWidget::_ReSetCustomPlot()
{
	QCPLayoutGrid* pLayoutGrid = NULL;

	if (NULL == m_pCustomPlot)
	{
		m_pCustomPlot = new QCustomPlot(this);

		m_pCustomPlot->clearGraphs();
		m_pCustomPlot->clearPlottables();
		m_pCustomPlot->plotLayout()->clear(); // clear default axis rect so we can start from scratch

	}

	if (NULL == m_pAxisRectTop)
	{
		m_pAxisRectTop = new QCPAxisRect(m_pCustomPlot);
		m_pAxisRectTop->setupFullAxesBox(true);
		m_pAxisRectTop->axis(QCPAxis::atLeft)->setLabel(QObject::tr("Y-value"));
		m_pAxisRectTop->axis(QCPAxis::atBottom)->setLabel(QObject::tr("X-time"));
		m_pAxisRectTop->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
		m_pAxisRectTop->axis(QCPAxis::atBottom)->setDateTimeFormat(DEF_STRING_FORMAT_TIME.c_str());
	}

	if (NULL == m_pAxisRectBottom)
	{
		m_pAxisRectBottom = new QCPAxisRect(m_pCustomPlot);
		m_pAxisRectBottom->setupFullAxesBox(true);
		m_pAxisRectBottom->axis(QCPAxis::atLeft)->setLabel(QObject::tr("Y-value"));
		m_pAxisRectBottom->axis(QCPAxis::atBottom)->setLabel(QObject::tr("X-time"));
		m_pAxisRectBottom->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
		m_pAxisRectBottom->axis(QCPAxis::atBottom)->setDateTimeFormat(DEF_STRING_FORMAT_TIME.c_str());//("yyyy-MM-dd hh-mm-ss");

		m_pCustomPlot->plotLayout()->addElement(0, 0, m_pAxisRectTop); // insert axis rect in first row
		m_pCustomPlot->plotLayout()->addElement(1, 0, m_pAxisRectBottom); // insert axis rect in first row
	}


	if (NULL == m_pMarginGroup)
	{
		m_pMarginGroup = NULL;
		m_pMarginGroup = new QCPMarginGroup(m_pCustomPlot);
		pLayoutGrid = m_pCustomPlot->plotLayout();
		pLayoutGrid->element(0, 0)->setMarginGroup(QCP::msAll, m_pMarginGroup);
		pLayoutGrid->element(1, 0)->setMarginGroup(QCP::msAll, m_pMarginGroup);
	}
	

	//
	if (NULL == m_pQCPItemTracerCrossHairTop)
	{
		m_pQCPItemTracerCrossHairTop = NULL;
		m_pQCPItemTracerCrossHairTop = new QCPItemTracerCrossHair(m_pCustomPlot);
		m_pCustomPlot->addItem(m_pQCPItemTracerCrossHairTop);
		m_pQCPItemTracerCrossHairTop->setTracerAxisRect(m_pAxisRectTop);
		m_pQCPItemTracerCrossHairTop->setStyle(QCPItemTracerCrossHair::tsCrosshair);
		m_pQCPItemTracerCrossHairTop->setShowLeft(QCPAxis::ltNumber, true, QString(""));
		m_pQCPItemTracerCrossHairTop->setShowBottom(QCPAxis::ltDateTime, true, QString(DEF_STRING_FORMAT_TIME.c_str()));
	}
	
	//
	if (NULL == m_pQCPItemTracerCrossHairBottom)
	{
		m_pQCPItemTracerCrossHairBottom = NULL;
		m_pQCPItemTracerCrossHairBottom = new QCPItemTracerCrossHair(m_pCustomPlot);
		m_pCustomPlot->addItem(m_pQCPItemTracerCrossHairBottom);
		m_pQCPItemTracerCrossHairBottom->setTracerAxisRect(m_pAxisRectBottom);
		m_pQCPItemTracerCrossHairBottom->setStyle(QCPItemTracerCrossHair::tsCrosshair);
		m_pQCPItemTracerCrossHairBottom->setShowLeft(QCPAxis::ltNumber, true, QString(""));
		m_pQCPItemTracerCrossHairBottom->setShowBottom(QCPAxis::ltDateTime, true, QString(DEF_STRING_FORMAT_TIME.c_str()));
	}
	
	/*
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(m_pCustomPlot->sizePolicy().hasHeightForWidth());
	m_pCustomPlot->setSizePolicy(sizePolicy);
	*/

	connect(m_pCustomPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(QCPItemTracerCrossHairMouseMove(QMouseEvent*)));
	//m_pCustomPlot->rescaleAxes();
	m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pCustomPlot->replot();//draw again

}

void CMidSubWidget::setupUi()
{
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::Dialog);	
	_ReSetCustomPlot();


	m_ScrollBar_Vertical = new QScrollBar(this);
	m_ScrollBar_Vertical->setOrientation(Qt::Vertical);
	m_ScrollBar_Horizontal = new QScrollBar(this);
	m_ScrollBar_Horizontal->setOrientation(Qt::Horizontal);


	// configure scroll bars:
	// Since scroll bars only support integer values, we'll set a high default range of -500..500 and
	// divide scroll bar position values by 100 to provide a scroll range -5..5 in floating point
	// axis coordinates. if you want to dynamically grow the range accessible with the scroll bar,
	// just increase the the minimum/maximum values of the scroll bars as needed.
	m_ScrollBar_Vertical->setRange(-500, 500);
	m_ScrollBar_Horizontal->setRange(-500, 500);

	//
	QGridLayout* gridLayout = NULL;
	gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	gridLayout->addWidget(m_pCustomPlot, 0, 0, 1, 1);
	gridLayout->addWidget(m_ScrollBar_Vertical, 0, 1, 1, 1);
	gridLayout->addWidget(m_ScrollBar_Horizontal, 1, 0, 1, 1);
	this->setLayout(gridLayout);

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

	m_pCustomPlot->clearGraphs();
	m_pCustomPlot->clearPlottables();

	m_pMidSubDrawHelper->drawHistoryBarData(pHistoryDataManager, m_pCustomPlot, m_pAxisRectTop);//m_pAxisRectTop
	m_pMidSubDrawHelper->drawHistoryVolumeData(pHistoryDataManager, m_pCustomPlot, m_pAxisRectBottom);//m_pAxisRectBottom


	//m_pCustomPlot->rescaleAxes();
	//m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pCustomPlot->replot();//draw again

}

void CMidSubWidget::QCPItemTracerCrossHairMouseMove( QMouseEvent *event )
{
	if (NULL != m_pQCPItemTracerCrossHairTop)
	{ 
		QPointF pointfValue_e_QPointF;
		pointfValue_e_QPointF = event->posF();
		//m_pQCPItemTracerCrossHair->setGraphKey(mCustomPlot->xAxis->pixelToCoord(event->pos().x()));
		//m_pQCPItemTracerCrossHair->position->setCoords(event->posF());
		m_pQCPItemTracerCrossHairTop->setCenterPos(pointfValue_e_QPointF);
	}

	if (NULL != m_pQCPItemTracerCrossHairBottom)
	{
		QPointF pointfValue_e_QPointF;
		pointfValue_e_QPointF = event->posF();
		m_pQCPItemTracerCrossHairBottom->setCenterPos(pointfValue_e_QPointF);
	}


	m_pCustomPlot->replot();
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
	if (qAbs(m_pCustomPlot->xAxis->range().center() - value / 100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		m_pCustomPlot->xAxis->setRange(value / 100.0, m_pCustomPlot->xAxis->range().size(), Qt::AlignCenter);
		m_pCustomPlot->replot();
	}
}

void CMidSubWidget::slotVertScrollBarChanged( int value )
{
	if (qAbs(m_pCustomPlot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		m_pCustomPlot->yAxis->setRange(-value/100.0, m_pCustomPlot->yAxis->range().size(), Qt::AlignCenter);
		m_pCustomPlot->replot();
	}
}

void CMidSubWidget::slotQCustomPlotxAxisChanged(QCPRange range)
{
	m_ScrollBar_Horizontal->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
	m_ScrollBar_Horizontal->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}
void CMidSubWidget::slotQCustomPlotyAxisChanged(QCPRange range)
{
	m_ScrollBar_Vertical->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
	m_ScrollBar_Vertical->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}