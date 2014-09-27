#include "MidSubWidget.h"



#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "HistoryDataManager.h"
#include "MidSubDrawHelper.h"
#include "qcustomplot.h"



#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 100;
static int DEFVALUE_INT_Window_Height = 100;
static const std::string   DEFVALUE_String_Window_Title = "MidSubWidget";

CMidSubWidget::CMidSubWidget(QWidget* parent)
    : QWidget(parent)
{

	m_pCustomPlot = NULL;
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

void CMidSubWidget::setupUi()
{
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::Dialog);
	QCPAxisRect* pAxisRectTop = NULL;
	QCPAxisRect* pAxisRectBottom = NULL;
	m_pCustomPlot = new QCustomPlot(this);

	m_pCustomPlot->clearGraphs();
	m_pCustomPlot->plotLayout()->clear(); // clear default axis rect so we can start from scratch

	pAxisRectTop = new QCPAxisRect(m_pCustomPlot);
	pAxisRectTop->axis(QCPAxis::atLeft)->setLabel(QObject::tr("Y-value"));
	pAxisRectTop->axis(QCPAxis::atBottom)->setLabel(QObject::tr("X-time"));
	pAxisRectTop->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
	pAxisRectTop->axis(QCPAxis::atBottom)->setDateTimeFormat("yyyy-MM-dd hh-mm-ss");

	pAxisRectBottom = new QCPAxisRect(m_pCustomPlot);
	pAxisRectBottom->axis(QCPAxis::atLeft)->setLabel(QObject::tr("Y-value"));
	pAxisRectBottom->axis(QCPAxis::atBottom)->setLabel(QObject::tr("X-time"));
	pAxisRectBottom->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
	pAxisRectBottom->axis(QCPAxis::atBottom)->setDateTimeFormat("yyyy-MM-dd hh-mm-ss");

	m_pCustomPlot->plotLayout()->addElement(0, 0, pAxisRectTop); // insert axis rect in first row
	m_pCustomPlot->plotLayout()->addElement(1, 0, pAxisRectBottom); // insert axis rect in first row

	m_pCustomPlot->rescaleAxes();
	m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pCustomPlot->replot();//draw again


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
		LOG_DEBUG<<" "<<"slot"
			<<" "<<"class:"<<"CMidSubWidget"
			<<" "<<"fun:"<<"slotHistoryDataChanged()"
			<<" "<<"param:"
			<<" "<<"pHistoryDataManager=0x"<<pHistoryDataManager;
	}

	QCPAxisRect* pAxisRect = NULL;
	QCPLayoutGrid* pLayoutGrid = NULL;
	QCPMarginGroup* pMarginGroup = NULL;
	m_pCustomPlot->clearGraphs();
	m_pCustomPlot->plotLayout()->clear(); // clear default axis rect so we can start from scratch

	pAxisRect = NULL;
	pAxisRect = new QCPAxisRect(m_pCustomPlot);
	pAxisRect->setupFullAxesBox(true);
	m_pCustomPlot->plotLayout()->addElement(0, 0, pAxisRect); // insert axis rect in first row
	m_pMidSubDrawHelper->drawHistoryBarData(pHistoryDataManager, m_pCustomPlot, pAxisRect);

	pAxisRect = NULL;
	pAxisRect = new QCPAxisRect(m_pCustomPlot);
	pAxisRect->setupFullAxesBox(true);
	m_pCustomPlot->plotLayout()->addElement(0, 0, pAxisRect); // insert axis rect in first row
	m_pMidSubDrawHelper->drawHistoryVolumeData(pHistoryDataManager, m_pCustomPlot, pAxisRect);
	pAxisRect = NULL;


	pLayoutGrid = m_pCustomPlot->plotLayout();
	pMarginGroup = new QCPMarginGroup(m_pCustomPlot);
	pLayoutGrid->element(0, 0)->setMarginGroup(QCP::msAll, pMarginGroup);
	pLayoutGrid->element(1, 0)->setMarginGroup(QCP::msAll, pMarginGroup);
	pLayoutGrid = NULL;
	pMarginGroup = NULL;


	m_pCustomPlot->rescaleAxes();
	m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pCustomPlot->replot();//draw again

}


//QT_END_NAMESPACE

