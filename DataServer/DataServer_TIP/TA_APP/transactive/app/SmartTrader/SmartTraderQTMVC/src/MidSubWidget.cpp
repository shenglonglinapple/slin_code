#include "MidSubWidget.h"



#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "ProjectLogHelper.h"
#include "ClientDataManagerWorker.h"
#include "HistoryDataManager.h"
#include "MidSubDrawHelper.h"
#include "DataUserHistoryBar.h"
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

static std::string DEF_STRING_FORMAT_TIME = "yyyy-MM-dd\nhh:mm:ss";


CMidSubWidget::CMidSubWidget(QWidget* parent)
    : QWidget(parent)
{

	m_pCustomPlot = NULL;
	m_pAxisRectTop = NULL;
	m_pAxisRectBottom = NULL;
	m_pQCPItemTracerCrossHairTop = NULL;
	m_pQCPItemTracerCrossHairBottom = NULL;
	m_pProjectLogHelper = NULL;
	m_nEHistoryDataStates = EHistoryDataStates_Ready;
	MYLOG4CPP_DEBUG<<"m_nEHistoryDataStates = EHistoryDataStates_Ready";

	m_pProjectLogHelper = new CProjectLogHelper();
	m_nInstrumentID = 0;
	m_nBarType = m_pProjectLogHelper->getBarTypeByString(DEFVALUE_String_HistoryBarType);
	m_nPage = 1;

	m_pMidSubDrawHelper = NULL;
	m_pMidSubDrawHelper = new CMidSubDrawHelper();

    setupUi();
	translateLanguage();

	_CreateAction();
	_CreateConnect();
}


CMidSubWidget::~CMidSubWidget()
{
	m_nEHistoryDataStates = EHistoryDataStates_End;

	if (NULL != m_pMidSubDrawHelper)
	{
		delete m_pMidSubDrawHelper;
		m_pMidSubDrawHelper = NULL;
	}
	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
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

		QObject::connect(m_pAxisRectTop->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), 
			this, SLOT(slotTopxAxisChanged(QCPRange)));
	}

	if (NULL == m_pAxisRectBottom)
	{
		m_pAxisRectBottom = new QCPAxisRect(m_pCustomPlot);
		m_pAxisRectBottom->setupFullAxesBox(true);
		m_pAxisRectBottom->axis(QCPAxis::atLeft)->setLabel(QObject::tr("Y-value"));

		m_pAxisRectBottom->axis(QCPAxis::atBottom)->setLabel(QObject::tr("X-time"));
		m_pAxisRectBottom->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
		m_pAxisRectBottom->axis(QCPAxis::atBottom)->setDateTimeFormat(DEF_STRING_FORMAT_TIME.c_str());//("yyyy-MM-dd hh-mm-ss");

		QObject::connect(m_pAxisRectBottom->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), 
			this, SLOT(slotBottomxAxisChanged(QCPRange)));
	}

	m_pCustomPlot->plotLayout()->addElement(0, 0, m_pAxisRectTop); // insert axis rect in first row
	m_pCustomPlot->plotLayout()->addElement(1, 0, m_pAxisRectBottom); // insert axis rect in first row

	{
		QCPMarginGroup* m_pMarginGroup = NULL;
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
		//m_pQCPItemTracerCrossHairTop->setShowLeft(QCPAxis::ltNumber, true, QString(""));
		m_pQCPItemTracerCrossHairTop->setShowLeft(QCPAxis::ltDateTime, true, QString(DEF_STRING_FORMAT_TIME.c_str()));
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
		//m_pQCPItemTracerCrossHairBottom->setShowLeft(QCPAxis::ltNumber, true, QString(""));
		m_pQCPItemTracerCrossHairBottom->setShowLeft(QCPAxis::ltDateTime, true, QString(DEF_STRING_FORMAT_TIME.c_str()));
		m_pQCPItemTracerCrossHairBottom->setShowBottom(QCPAxis::ltDateTime, true, QString(DEF_STRING_FORMAT_TIME.c_str()));
	}
	

	connect(m_pCustomPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(QCPItemTracerCrossHairMouseMove(QMouseEvent*)));
	//m_pCustomPlot->rescaleAxes();
	//m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pAxisRectTop->setRangeDrag(Qt::Horizontal);//只在水平方向上可拖动
	m_pAxisRectBottom->setRangeDrag(Qt::Horizontal);//只在水平方向上可拖动

	m_pCustomPlot->setInteractions(QCP::iRangeDrag);//只可拖动
	m_pCustomPlot->replot();//draw again

}

void CMidSubWidget::_InitUIData()
{
	unsigned int nTimeFrom = 0;
	unsigned int nTimeTo = 0;
	double nLeftAxisRangeMinAdjuest = 0;
	double nLeftAxisRangeMaxAdjuest = 0;

	nTimeFrom =  m_pMidSubDrawHelper->getBottomTimeFrom();;
	nTimeTo = m_pMidSubDrawHelper->getBottomTimeTo();

	nLeftAxisRangeMinAdjuest = 0;
	nLeftAxisRangeMaxAdjuest = 100;

	m_pAxisRectTop->axis(QCPAxis::atBottom)->setRange(nTimeFrom, nTimeTo);//x
	m_pAxisRectTop->axis(QCPAxis::atLeft)->setRange(nLeftAxisRangeMinAdjuest, nLeftAxisRangeMaxAdjuest);//y

	m_pAxisRectBottom->axis(QCPAxis::atBottom)->setRange(nTimeFrom, nTimeTo);//x
	m_pAxisRectBottom->axis(QCPAxis::atLeft)->setRange(nLeftAxisRangeMinAdjuest*10000, nLeftAxisRangeMaxAdjuest*10000);//y

	m_pCustomPlot->replot();//draw again

}

void CMidSubWidget::setupUi()
{
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::Dialog);
	
	_ReSetCustomPlot();
	_InitUIData();


	{
		QVBoxLayout* verticalLayout = NULL;	
		verticalLayout = new QVBoxLayout(this);
		verticalLayout->setSpacing(6);
		verticalLayout->setContentsMargins(11, 11, 11, 11);
		verticalLayout->addWidget(m_pCustomPlot);
		this->setLayout(verticalLayout);
	}

	QMetaObject::connectSlotsByName(this);
} 
void CMidSubWidget::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title.c_str()));

}

void CMidSubWidget::slotHistoryDataChanged( unsigned int nInstrumentID  )
{
	m_nEHistoryDataStates = EHistoryDataStates_GetACK;
	MYLOG4CPP_DEBUG<<"m_nEHistoryDataStates = EHistoryDataStates_GetACK";


	//emit
	{
		MYLOG4CPP_DEBUG<<"CMidSubWidget process slotHistoryDataChanged"
			<<" "<<"param:"
			<<" "<<"nInstrumentID="<<nInstrumentID;
	}

	CHistoryQutoes* pHistoryDataManager = NULL;
	CDataHistoryQuotesManager::getInstance().lock();
	pHistoryDataManager = CDataHistoryQuotesManager::getInstance().lockUseData(nInstrumentID);
	if (NULL == pHistoryDataManager)
	{
		CDataHistoryQuotesManager::getInstance().unlock();
		return;
	}

	m_pCustomPlot->clearGraphs();
	m_pCustomPlot->clearPlottables();

	m_pMidSubDrawHelper->drawHistoryVolumeData(pHistoryDataManager, m_pCustomPlot, m_pAxisRectBottom);
	m_pMidSubDrawHelper->drawHistoryBarData(pHistoryDataManager, m_pCustomPlot, m_pAxisRectTop);

	CDataHistoryQuotesManager::getInstance().unlock();

	m_pCustomPlot->replot();//draw again

	m_nEHistoryDataStates = EHistoryDataStates_Ready;
	MYLOG4CPP_DEBUG<<"m_nEHistoryDataStates = EHistoryDataStates_Ready";



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


	m_pCustomPlot->replot();
}

void CMidSubWidget::setCurrentInstrumentID(unsigned int nInstrumentID)
{
	m_nInstrumentID = nInstrumentID;
	m_nPage = 1;//reset
}

unsigned int CMidSubWidget::getCurrentInstrumentID()
{
	return m_nInstrumentID;

}

void CMidSubWidget::setHistoryBarType(enum BarType nBarType, const QString& strBarType)
{
	m_nBarType = nBarType;
}

void CMidSubWidget::slotTopxAxisChanged(QCPRange range)
{

	//check GUI have data
	if (range.lower < m_pMidSubDrawHelper->getBottomTimeFrom())
	{
		if (m_nEHistoryDataStates == EHistoryDataStates_Ready)
		{
			m_nEHistoryDataStates = EHistoryDataStates_SentReqest;
			MYLOG4CPP_DEBUG<<"m_nEHistoryDataStates = EHistoryDataStates_SentReqest";

			//if no data sent req to server
			unsigned int nTimeFrom = 0;
			unsigned int nTimeTo = 0;
			nTimeTo = m_pProjectLogHelper->getTimeNow_Qt();
			nTimeFrom = nTimeTo - (m_nPage * m_nBarType * DEFVALUE_Int_OnePage_HistoryBarNumber);
			CClientDataManagerWorker::getInstance().slotRequestHistoryData(
				m_nInstrumentID, m_nBarType, nTimeFrom, nTimeTo);
			m_nPage = m_nPage + 1;
			m_nEHistoryDataStates = EHistoryDataStates_WaitACK;
			MYLOG4CPP_DEBUG<<"m_nEHistoryDataStates = EHistoryDataStates_WaitACK";

		}

	}

	if (range == m_pAxisRectBottom->axis(QCPAxis::atBottom)->range())
	{
		return;
	}
	MYLOG4CPP_DEBUG<<"slotTopxAxisChanged"
		<<" "<<"range.lower="<<m_pProjectLogHelper->dateTimeToStr_Qt(range.lower)
		<<" "<<"range.upper="<<m_pProjectLogHelper->dateTimeToStr_Qt(range.upper);

	m_pAxisRectBottom->axis(QCPAxis::atBottom)->setRange(range);//x
	m_pCustomPlot->replot();
}

void CMidSubWidget::slotBottomxAxisChanged(QCPRange range)
{	

	if (range == m_pAxisRectTop->axis(QCPAxis::atBottom)->range())
	{
		return;
	}
	MYLOG4CPP_DEBUG<<"slotBottomxAxisChanged"
		<<" "<<"range.lower="<<m_pProjectLogHelper->dateTimeToStr_Qt(range.lower)
		<<" "<<"range.upper="<<m_pProjectLogHelper->dateTimeToStr_Qt(range.upper);


	m_pAxisRectTop->axis(QCPAxis::atBottom)->setRange(range);//x
	m_pCustomPlot->replot();
}




//QT_END_NAMESPACE

