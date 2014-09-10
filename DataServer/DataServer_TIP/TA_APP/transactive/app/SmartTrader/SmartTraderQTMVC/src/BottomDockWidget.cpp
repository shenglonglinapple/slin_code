#include "BottomDockWidget.h"



#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "TreeModelQuotes.h"
#include "TreeItemQuotes.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 100;




CBottomDockWidget::CBottomDockWidget(QWidget* parent)
    : QWidget(parent)
{

	m_pVBoxLayout = NULL;
	m_pTreeModelQuotes = NULL;
	m_pTableView_Order = NULL;//m_pTreeModelQuotes

    setupUi();
	translateLanguage();

	_CreateAction();
	_CreateConnect();
}


CBottomDockWidget::~CBottomDockWidget()
{
	
}


QSize CBottomDockWidget::sizeHint() const
{
	//for QDockWidget
	return QSize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height); /* 在这里定义dock的初始大小 */
}

void CBottomDockWidget::_CreateAction()
{

}

void CBottomDockWidget::_CreateConnect()
{

}

void CBottomDockWidget::setupUi()
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	this->setWindowFlags(Qt::Dialog);

	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->setTabPosition(QTabWidget::South);	//enum TabPosition { North, South, West, East

	m_pTableView_Order = new CQuotesTableView(m_pTabWidget);

	
 	m_pVBoxLayout = new QVBoxLayout(this);
 	m_pVBoxLayout->addWidget(m_pTabWidget);
 	m_pVBoxLayout->setSpacing(0);
 	m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
	//

	this->setLayout(m_pVBoxLayout);


	QMetaObject::connectSlotsByName(this);
} 
void CBottomDockWidget::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_ObjectName_CSmartHotQuotesWindow.c_str()));
	m_pTabWidget->addTab(m_pTableView_Order, QObject::tr("Symbols"));

}


void CBottomDockWidget::slotQuotesInfoChanged( CTreeItemQuotes* pTreeItem )
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
		m_pTableView_Order->setModel(m_pTreeModelQuotes);
		//m_pTreeView_Quotes->setColumnWidth(0, 200);
		m_pTableView_Order->setCurrentIndex(inValidIndex);
		m_pTableView_Order->resizeColumnsToContents();

	}
	else
	{
		m_pTreeModelQuotes->setRootItem(pTreeItem);
		m_pTableView_Order->setCurrentIndex(inValidIndex);
		m_pTableView_Order->resizeColumnsToContents();
	}
}



//QT_END_NAMESPACE

