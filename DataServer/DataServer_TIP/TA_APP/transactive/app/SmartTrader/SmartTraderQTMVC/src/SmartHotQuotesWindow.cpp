#include "SmartHotQuotesWindow.h"



#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "QuotesTableView.h"
#include "TreeModelQuotes.h"
#include "TreeItemQuotes.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 400;
static int DEFVALUE_INT_Window_Height = 300;


static const std::string DEFVALUE_String_ObjectName_CSmartHotQuotesWindow = "ObjectName_CSmartHotQuotesWindow";
static const std::string DEFVALUE_String_ObjectName_CSmartHotQuotesWindow_WidgetCentral = "ObjectName_CSmartHotQuotesWindow_WidgetCentral";
static const std::string DEFVALUE_String_ObjectName_CSmartHotQuotesWindow_VBoxLayout = "ObjectName_CSmartHotQuotesWindow_VBoxLayout";
static const std::string DEFVALUE_String_ObjectName_CSmartHotQuotesWindow_TreeViewQuotes = "ObjectName_CSmartHotQuotesWindow_TreeViewQuotes";

static const std::string DEFVALUE_String_ActionAddHotQuotes = "AddQuotes";//添加合约报价


CSmartHotQuotesWindow::CSmartHotQuotesWindow(QWidget* parent)
    : QWidget(parent)
{

	m_pVBoxLayout = NULL;
	m_pTreeModelQuotes = NULL;
	m_pTreeView_Quotes = NULL;//m_pTreeModelQuotes

    setupUi();
	translateLanguage();

	_CreateAction();
	_CreateConnect();
}


CSmartHotQuotesWindow::~CSmartHotQuotesWindow()
{
	
}


QSize CSmartHotQuotesWindow::sizeHint() const
{
	//for QDockWidget
	return QSize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height); /* 在这里定义dock的初始大小 */
}

void CSmartHotQuotesWindow::_CreateAction()
{

}

void CSmartHotQuotesWindow::_CreateConnect()
{

}

void CSmartHotQuotesWindow::setupUi()
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	this->setWindowFlags(Qt::Dialog);

	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->setTabPosition(QTabWidget::South);	//enum TabPosition { North, South, West, East

	m_pTreeView_Quotes = new CQuotesTableView(m_pTabWidget);

	
 	m_pVBoxLayout = new QVBoxLayout(this);
 	m_pVBoxLayout->addWidget(m_pTabWidget);
 	m_pVBoxLayout->setSpacing(0);
 	m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
	//

	this->setLayout(m_pVBoxLayout);


	QMetaObject::connectSlotsByName(this);
} 
void CSmartHotQuotesWindow::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_ObjectName_CSmartHotQuotesWindow.c_str()));
	m_pTabWidget->addTab(m_pTreeView_Quotes, QObject::tr("Symbols"));

}


void CSmartHotQuotesWindow::slotQuotesInfoChanged( CTreeItemQuotes* pTreeItem )
{
	LOG_DEBUG<<"CSmartHotQuotesWindow process slotQuotesInfoChanged"
		<<" "<<"pTreeItem=ox"<<pTreeItem;

	QModelIndex inValidIndex;

	if (NULL == m_pTreeModelQuotes)
	{
		//
		m_pTreeModelQuotes = new CTreeModelQuotes(this);
		m_pTreeModelQuotes->setRootItem(pTreeItem);

		//mvc
		m_pTreeView_Quotes->setModel(m_pTreeModelQuotes);
		//m_pTreeView_Quotes->setColumnWidth(0, 200);
		m_pTreeView_Quotes->setCurrentIndex(inValidIndex);
		m_pTreeView_Quotes->resizeColumnsToContents();

	}
	else
	{
		m_pTreeModelQuotes->setRootItem(pTreeItem);
		m_pTreeView_Quotes->setCurrentIndex(inValidIndex);
		m_pTreeView_Quotes->resizeColumnsToContents();
	}
}



//QT_END_NAMESPACE

