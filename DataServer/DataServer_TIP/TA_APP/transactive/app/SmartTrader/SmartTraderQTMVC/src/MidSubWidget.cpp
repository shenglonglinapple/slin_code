#include "MidSubWidget.h"



#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "HistoryDataManager.h"
#include "MidSubDrawHelper.h"
#include "qcp.h"
#include <QtCore/QDateTime>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */


#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 100;
static int DEFVALUE_INT_Window_Height = 100;
static const std::string   DEFVALUE_String_Window_Title = "MidSubWidget";

static std::string DEF_STRING_FORMAT_TIME = "yyyy-MM-dd hh:mm:ss";


CMidSubWidget::CMidSubWidget(QWidget* parent)
    : QWidget(parent)
{

	m_pCustomPlot = NULL;
	m_pAxisRectTop = NULL;
	m_pAxisRectBottom = NULL;
	m_pMarginGroup = NULL;
	m_pQCPItemTracerCrossHairTop = NULL;
	m_pQCPItemTracerCrossHairBottom = NULL;

	m_pMidSubDrawHelper = NULL;
	m_pMidSubDrawHelper = new CMidSubDrawHelper();

    setupUi();
	translateLanguage();


	_CreateAction();
	_CreateConnect();

	//doTest(customPlot);


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


	//
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	verticalLayout->addWidget(m_pCustomPlot);

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


	m_pCustomPlot->clearGraphs();
	m_pCustomPlot->clearPlottables();

	m_pMidSubDrawHelper->drawHistoryVolumeData(pHistoryDataManager, m_pCustomPlot, m_pAxisRectTop);
	m_pMidSubDrawHelper->drawHistoryBarData(pHistoryDataManager, m_pCustomPlot, m_pAxisRectBottom);


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


//QT_END_NAMESPACE

