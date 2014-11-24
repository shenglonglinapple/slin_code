#include "SmartHotQuotesWindow.h"



#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "UserInstrumentInfoView.h"
#include "ItemUserInstrumentInfo.h"
#include "ItemModelUserInstrumentInfo.h"

#include "DataUserInstrument.h"
#include "SignalSlotManager.h"
#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 400;
static int DEFVALUE_INT_Window_Height = 300;

static const std::string DEFVALUE_String_Window_Title = "CLeftDockWidget_Window_Title";



CLeftDockWidget::CLeftDockWidget(QWidget* parent)
    : QWidget(parent)
{

	m_pVBoxLayout = NULL;
	m_pItemModelUserInstrumentInfo = NULL;
	m_pUserInstrumentInfoView = NULL;//m_pTreeModelQuotes

    setupUi();
	translateLanguage();

	_CreateAction();
	_CreateConnect();

	slotUserInstrumentInfoChanged(CDataUserInstrument::getInstance().getRootHandle());
}


CLeftDockWidget::~CLeftDockWidget()
{
	
}


QSize CLeftDockWidget::sizeHint() const
{
	//for QDockWidget
	return QSize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height); /* 在这里定义dock的初始大小 */
}

void CLeftDockWidget::_CreateAction()
{

}

void CLeftDockWidget::_CreateConnect()
{

}

void CLeftDockWidget::setupUi()
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	this->setWindowFlags(Qt::Dialog);

	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->setTabPosition(QTabWidget::South);	//enum TabPosition { North, South, West, East

	m_pUserInstrumentInfoView = new CUserInstrumentInfoView(m_pTabWidget);
	CSignalSlotManager::getInstance().setSignalSlot_UserInstrumentViewColumnsChanged(m_pUserInstrumentInfoView, &(CClientDataManagerWorker::getInstance()));
	CSignalSlotManager::getInstance().setSignalSlot_RemoveUserInstrument(m_pUserInstrumentInfoView, &(CClientDataManagerWorker::getInstance()));
	CSignalSlotManager::getInstance().setSignalSlot_InstrumentViewResetData(m_pUserInstrumentInfoView, &(CClientDataManagerWorker::getInstance()));
	QObject::connect(m_pUserInstrumentInfoView, SIGNAL(signalCurrentInstrumentChanged(unsigned int)), 
		this, SLOT(slotCurrentInstrumentChanged(unsigned int)));

	
 	m_pVBoxLayout = new QVBoxLayout(this);
 	m_pVBoxLayout->addWidget(m_pTabWidget);
 	m_pVBoxLayout->setSpacing(0);
 	m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
	//

	this->setLayout(m_pVBoxLayout);


	QMetaObject::connectSlotsByName(this);
} 
void CLeftDockWidget::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title.c_str()));
	m_pTabWidget->addTab(m_pUserInstrumentInfoView, QObject::tr("Symbols"));

}


void CLeftDockWidget::slotUserInstrumentInfoChanged( CItemUserInstrumentInfo* pTreeItem )
{
	MYLOG4CPP_DEBUG<<"CSmartHotQuotesWindow process slotUserInstrumentInfoChanged"
		<<" "<<"pTreeItem=ox"<<pTreeItem;

	QModelIndex inValidIndex;

	if (NULL == m_pItemModelUserInstrumentInfo)
	{
		//
		m_pItemModelUserInstrumentInfo = new CItemModelUserInstrumentInfo(this);
		m_pItemModelUserInstrumentInfo->setRootItem(pTreeItem);

		//mvc
		m_pUserInstrumentInfoView->setModel(m_pItemModelUserInstrumentInfo);
		//m_pTreeView_Quotes->setColumnWidth(0, 200);
		m_pUserInstrumentInfoView->setCurrentIndex(inValidIndex);
		m_pUserInstrumentInfoView->resizeColumnsToContents();

	}
	else
	{
		m_pItemModelUserInstrumentInfo->setRootItem(pTreeItem);
		m_pUserInstrumentInfoView->setCurrentIndex(inValidIndex);
		m_pUserInstrumentInfoView->resizeColumnsToContents();
	}
}

void CLeftDockWidget::slotCurrentInstrumentChanged( unsigned int nInstrumentID )
{
	MYLOG4CPP_DEBUG<<"CLeftDockWidget process slotCurrentInstrumentChanged"
		<<" "<<"param:"
		<<" "<<"nInstrumentID="<<nInstrumentID;


	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CLeftDockWidget"
			<<" "<<"fun:"<<"slotCurrentInstrumentChanged()"
			<<" "<<"emit"
			<<" "<<"signalCurrentInstrumentChanged(unsigned int)"
			<<" "<<"nInstrumentID="<<nInstrumentID;
		emit signalCurrentInstrumentChanged(nInstrumentID);
	}

}




//QT_END_NAMESPACE

