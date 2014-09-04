#include "StrategyOrdersWindow.h"


#include <QtGui/QMenu> 
#include <QtGui/QCursor> 
#include <QtGui/QMessageBox>

#include "TreeItem.h"
#include "TreeModel.h"

#include "ClientDataManagerWorker.h"


#include "BoostLogger.h"
USING_BOOST_LOG;


QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CStrategyOrdersWindow = 800;
static int DEFVALUE_Int_Hight_CStrategyOrdersWindow = 100;

CStrategyOrdersWindow::CStrategyOrdersWindow(QWidget* parent)
    : QWidget(parent)
{

	m_pWidget_Central = NULL;
	m_pVBoxLayout = NULL;
	m_pTreeModel = NULL;

	//
	QModelIndex inValidIndex;
	QStringList strLstColumnNames;
	TreeItem::getLstClumnName(strLstColumnNames);
	m_pTreeModel = new TreeModel(strLstColumnNames, NULL);

    setupUi(this);
	m_pTreeView->setModel(m_pTreeModel);
	m_pTreeView->setCurrentIndex(inValidIndex);

	_CreateAction();
	_CreateConnect();
}


CStrategyOrdersWindow::~CStrategyOrdersWindow()
{
	
}

void CStrategyOrdersWindow::_CreateAction()
{

}

void CStrategyOrdersWindow::_CreateConnect()
{

}

void CStrategyOrdersWindow::setupUi(QWidget* pMainWindow)
{
	if (pMainWindow->objectName().isEmpty())
	{
		pMainWindow->setObjectName(QString::fromUtf8("ObjectName_CStrategyOrdersWindow"));
	}

	pMainWindow->resize(DEFVALUE_Int_Wide_CStrategyOrdersWindow, DEFVALUE_Int_Hight_CStrategyOrdersWindow);


	m_pWidget_Central = new QWidget(pMainWindow);
	m_pWidget_Central->setObjectName(QString::fromUtf8("ObjectName_CStrategyOrdersWindow_Widget_Central"));
	//

	m_pVBoxLayout = new QVBoxLayout(m_pWidget_Central);
	m_pVBoxLayout->setSpacing(0);
	m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
	m_pVBoxLayout->setObjectName(QString::fromUtf8("ObjectName_CStrategyOrdersWindow_VBoxLayout"));


	m_pTreeView = new QTreeView(pMainWindow);
	m_pTreeView->setObjectName(QString::fromUtf8("ObjectName_CStrategyOrdersWindow_TreeView"));
	m_pTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTreeView->setAlternatingRowColors(true);
	m_pTreeView->setSelectionBehavior(QAbstractItemView::SelectItems);
	m_pTreeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pTreeView->setAnimated(false);
	m_pTreeView->setAllColumnsShowFocus(true);
	m_pTreeView->header()->setVisible(true);
	m_pTreeView->header()->setStretchLastSection(false);
	m_pVBoxLayout->addWidget(m_pTreeView);
	//
	
	
	//
	//pMainWindow->setCentralWidget(m_pWidget_Central);

	retranslateUi(pMainWindow);

	QMetaObject::connectSlotsByName(pMainWindow);
} 

void CStrategyOrdersWindow::retranslateUi(QWidget *pMainWindow)
{

} 



void CStrategyOrdersWindow::slotStrategyOrdersInfoChanged( TreeItem* pTreeItem )
{
	LOG_DEBUG<<"CSmartHotQuotesWindow process slotQuotesInfoChanged"
		<<" "<<"pTreeItem=ox"<<pTreeItem;

	QModelIndex inValidIndex;

	if (NULL == m_pTreeModel)
	{
		//
		QStringList strLstColumnNames;
		TreeItem::getLstClumnName(strLstColumnNames);


		m_pTreeModel = new TreeModel(strLstColumnNames, NULL);
		//m_pTreeModel->setRootItem(pTreeItem);

		//mvc
		m_pTreeView->setModel(m_pTreeModel);
		//m_pTreeView_Quotes->setColumnWidth(0, 200);

		m_pTreeView->setCurrentIndex(inValidIndex);
	}
	else
	{
		//m_pTreeModel->setRootItem(pTreeItem);
		m_pTreeView->setCurrentIndex(inValidIndex);
	}
}

void CStrategyOrdersWindow::translateLanguage()
{

}


QT_END_NAMESPACE

