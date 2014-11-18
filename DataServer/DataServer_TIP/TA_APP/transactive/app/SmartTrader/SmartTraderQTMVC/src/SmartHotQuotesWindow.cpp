#include "SmartHotQuotesWindow.h"



#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "QuotesTableView.h"
#include "TreeModelQuotes.h"
#include "TreeItemQuotes.h"

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
	m_pTreeModelQuotes = NULL;
	m_pTableView_Quotes = NULL;//m_pTreeModelQuotes

    setupUi();
	translateLanguage();

	_CreateAction();
	_CreateConnect();
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

	m_pTableView_Quotes = new CQuotesTableView(m_pTabWidget);

	
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
	m_pTabWidget->addTab(m_pTableView_Quotes, QObject::tr("Symbols"));

}


void CLeftDockWidget::slotQuotesInfoChanged( CTreeItemQuotes* pTreeItem )
{
	MYLOG4CPP_DEBUG<<"CSmartHotQuotesWindow process slotQuotesInfoChanged"
		<<" "<<"pTreeItem=ox"<<pTreeItem;

	QModelIndex inValidIndex;

	if (NULL == m_pTreeModelQuotes)
	{
		//
		m_pTreeModelQuotes = new CTreeModelQuotes(this);
		m_pTreeModelQuotes->setRootItem(pTreeItem);

		//mvc
		m_pTableView_Quotes->setModel(m_pTreeModelQuotes);
		//m_pTreeView_Quotes->setColumnWidth(0, 200);
		m_pTableView_Quotes->setCurrentIndex(inValidIndex);
		m_pTableView_Quotes->resizeColumnsToContents();

	}
	else
	{
		m_pTreeModelQuotes->setRootItem(pTreeItem);
		m_pTableView_Quotes->setCurrentIndex(inValidIndex);
		m_pTableView_Quotes->resizeColumnsToContents();
	}
}



//QT_END_NAMESPACE

