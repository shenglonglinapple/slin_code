#include "QuotesTableView.h"

#include <QtGui/QMenu>
#include <QtGui/QCursor>
#include <QtGui/QMessageBox>
#include <QtCore/QEvent>
#include <QtGui/QContextMenuEvent>

#include "TreeItemQuotes.h"
#include "IconDelegate.h"
#include "CustomColumnsDialog.h"
#include "ContractInfoWindow.h"
#include "CreateNewOrderDialog.h"
#include "QuotesHHeaderView.h"
#include "ConfigInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


static const std::string DEFVALUE_String_ActionAddHotQuotes = "AddQuotes";//"添加合约报价";
static const std::string DEFVALUE_String_ActionRemoveHotQuotes = "RemoveQuotes";//"从列表中移除此合约报价";
static const std::string DEFVALUE_String_ActionCustomColumns = "CustomColumns";//"自定义列";

static const std::string DEFAULT_STRING_VALUE_STRING_SPLIT = ",";

CQuotesTableView::CQuotesTableView( QWidget* parent /*= 0*/ )
:QTableView(parent)
{
	m_pHorizontalHeader = NULL;
	m_pVerticalHeader = NULL;
	m_pActionAddHotQuotes = NULL;
	m_pActionRemoveHotQuotes = NULL;
	m_pActionCustomColumns = NULL;
	m_pCreateNewOrderDialog = NULL;
	m_pContractInfoWindow = NULL;
	m_pCustomColumnsDialog = NULL;
	m_pIconDelegate_Column_Change = NULL;
	m_nColumnIndex_Change = -1;

	m_nColumnIndex_Change = CConfigInfo::getInstance().getColumnIndex_Change();


	m_pIconDelegate_Column_Change = new IconDelegate(this);
	//this->setItemDelegateForColumn(nColumnIndex_Change, this->itemDelegate());
	if (-1 != m_nColumnIndex_Change)
	{
		this->setItemDelegateForColumn(m_nColumnIndex_Change, m_pIconDelegate_Column_Change);
	}
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setAlternatingRowColors(true);
	this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

	// 	this->setStyleSheet("QTableView{background-color: rgb(250, 250, 115);"
	// 		"alternate-background-color: rgb(141, 163, 215);}");  //把表格的背景调成黄蓝相间
	//this->setSelectionBehavior(QAbstractItemView::SelectItems);
	//this->setAnimated(false);
	//this->setAllColumnsShowFocus(true);
	//this->header()->setVisible(true);
	//m_pTreeView_Quotes->header()->setStretchLastSection(false);

	m_pHorizontalHeader = new CQuotesHHeaderView(Qt::Horizontal, this);
	//m_pHorizontalHeader = this->horizontalHeader();
	this->setHorizontalHeader(m_pHorizontalHeader);
	m_pVerticalHeader = this->verticalHeader();


	m_pActionAddHotQuotes = new QAction(QObject::tr(DEFVALUE_String_ActionAddHotQuotes.c_str()), this); 
	m_pActionRemoveHotQuotes = new QAction(QObject::tr(DEFVALUE_String_ActionRemoveHotQuotes.c_str()), this); 
	m_pActionCustomColumns = new QAction(QObject::tr(DEFVALUE_String_ActionCustomColumns.c_str()), this); 

	m_pCreateNewOrderDialog = new CCreateNewOrderDialog(this);
	m_pContractInfoWindow = new CContractInfoWindow(this);
	m_pCustomColumnsDialog = new CCustomColumnsDialog(this);

	//this->setWindowTitle(QObject::tr("Market Watch:"));
	//connect action
	_CreateConnect();

	m_strSelectedColumnsForCheck.clear();
}

CQuotesTableView::~CQuotesTableView()
{
	if (NULL != m_pActionAddHotQuotes)
	{
		delete m_pActionAddHotQuotes;
		m_pActionAddHotQuotes = NULL;
	}

	if (NULL != m_pActionRemoveHotQuotes)
	{
		delete m_pActionRemoveHotQuotes;
		m_pActionRemoveHotQuotes = NULL;
	}

	if (NULL != m_pActionCustomColumns)
	{
		delete m_pActionCustomColumns;
		m_pActionCustomColumns = NULL;
	}

	if (NULL != m_pCreateNewOrderDialog)
	{
		delete m_pCreateNewOrderDialog;
		m_pCreateNewOrderDialog = NULL;
	}

	if (NULL != m_pContractInfoWindow)
	{
		delete m_pContractInfoWindow;
		m_pContractInfoWindow = NULL;
	}

	if (NULL != m_pCustomColumnsDialog)
	{
		delete m_pCustomColumnsDialog;
		m_pCustomColumnsDialog = NULL;
	}
	if (NULL != m_pIconDelegate_Column_Change)
	{
		delete m_pIconDelegate_Column_Change;
		m_pIconDelegate_Column_Change = NULL;
	}

	m_pHorizontalHeader = NULL;
	m_pVerticalHeader = NULL;
	m_strSelectedColumnsForCheck.clear();
}


void CQuotesTableView::_CreateConnect()
{

	//connect action
	QObject::connect(m_pActionAddHotQuotes, 
		SIGNAL(triggered()), 
		this, 
		SLOT(slotActionAddHotQuotesTriggered())); 

	QObject::connect(m_pActionRemoveHotQuotes, 
		SIGNAL(triggered()), 
		this, 
		SLOT(slotActionRemoveHotQuotesTriggered())); 

	QObject::connect(m_pActionCustomColumns, 
		SIGNAL(triggered()), 
		this, 
		SLOT(slotActionCustomColumnsTriggered())); 

	//鼠标右键单击
	QObject::connect(m_pHorizontalHeader, 
		SIGNAL(signalMouseRightClickInHHeaderView(QMouseEvent*)), 
		this, 
		SLOT(slotMouseRightClickInHHeaderView(QMouseEvent*))); 

	QObject::connect(m_pCustomColumnsDialog, 
		SIGNAL(signalModifySelectedColumns(QStringList, QStringList)), 
		this, 
		SLOT(slotModifySelectedColumns(QStringList, QStringList))); 
	
}


void CQuotesTableView::contextMenuEvent( QContextMenuEvent* pEvent )
{

	LOG_DEBUG<<"CQuotesTableView process contextMenuEvent"
		<<" "<<"pEvent=0x"<<pEvent;

	QPoint point;
	QCursor currentCursor;
	QModelIndex nCurrentTreeItemIndex;
	CTreeItemQuotes* pCurrentTreeItem = NULL;
	unsigned int  nInstrumentID = 0;
	QString strLogInfo;

	point = pEvent->pos(); //get Pos
	currentCursor = this->cursor(); 
	nCurrentTreeItemIndex = this->currentIndex();	

	if (false == nCurrentTreeItemIndex.isValid())
	{
		//treeview line no data
		//set menu pos
		QMenu menuRightClieck(this);
		menuRightClieck.addAction(m_pActionAddHotQuotes);
		menuRightClieck.exec(QCursor::pos());
		return;
	}

	//treeview line have data
	pCurrentTreeItem = (CTreeItemQuotes*)nCurrentTreeItemIndex.internalPointer();
	nInstrumentID = pCurrentTreeItem->getInstrumentID();
	strLogInfo = QString("contextMenuEvent nInstrumentID=%1").arg(nInstrumentID);
	LOG_DEBUG<<"CQuotesTableView::contextMenuEvent"
		<<" "<<"nInstrumentID="<<nInstrumentID;
	//QMessageBox::about(this, strLogInfo, strLogInfo);

	//set menu pos
	QMenu menuRightClieck(this);
	menuRightClieck.addAction(m_pActionAddHotQuotes);
	menuRightClieck.addAction(m_pActionRemoveHotQuotes);
	menuRightClieck.addAction(m_pActionCustomColumns);
	//menuRightClieck.exec(currentCursor.pos());
	menuRightClieck.exec(QCursor::pos());
	pEvent->accept();
}


void CQuotesTableView::slotActionRemoveHotQuotesTriggered()
{
	LOG_DEBUG<<"CQuotesTableView process slotActionRemoveHotQuotesTriggered";

	QAbstractItemModel* pModel = NULL;
	int nRowDoubleClick = 0;
	int nColumnDoubleClick = 0;
	Qt::ItemFlags nFlagsTreeItem;
	unsigned int nInstrumentID = 0;
	QModelIndex nCurrentTreeItemIndex;
	CTreeItemQuotes* pCurrentTreeItem = NULL;
	QString strLogInfo;


	nCurrentTreeItemIndex = this->currentIndex();
	if (false == nCurrentTreeItemIndex.isValid())
	{
		return;
	}
	pCurrentTreeItem = (CTreeItemQuotes*)nCurrentTreeItemIndex.internalPointer();
	nInstrumentID = pCurrentTreeItem->getInstrumentID();

	strLogInfo = QString("contextMenuEvent nInstrumentID=%1").arg(nInstrumentID);

	pModel = this->model();
	nRowDoubleClick = nCurrentTreeItemIndex.row();
	nColumnDoubleClick = nCurrentTreeItemIndex.column();
	strLogInfo += pModel->data(nCurrentTreeItemIndex, Qt::DisplayRole).toString();

	pModel->removeRow(nCurrentTreeItemIndex.row(), nCurrentTreeItemIndex.parent());
		
	LOG_DEBUG<<"CQuotesTableView emit signalRemoveContractFromSmartQuotes"
		<<" "<<"nInstrumentID="<<nInstrumentID;

	emit signalRemoveContractFromSmartQuotes(nInstrumentID);
}

void CQuotesTableView::slotActionAddHotQuotesTriggered()
{
	LOG_DEBUG<<"CQuotesTableView process slotActionAddHotQuotesTriggered";

	QCursor currentCursor = this->cursor(); 
	currentCursor.pos();

	m_pContractInfoWindow->move(QCursor::pos());
	m_pContractInfoWindow->show();

}


void CQuotesTableView::slotActionCustomColumnsTriggered()
{
	LOG_DEBUG<<"CQuotesTableView process slotActionCustomColumnsTriggered";
	m_pCustomColumnsDialog->show();
}


void CQuotesTableView::mouseDoubleClickEvent( QMouseEvent* pEvent )
{
	if (Qt::LeftButton == pEvent->button())
	{
		LOG_DEBUG<<"CQuotesTableView process mouseDoubleClickEvent Qt::LeftButton";

		QAbstractItemModel* pModel = NULL;
		unsigned int nInstrumentID = 0;
		QString strInstrumentCode;
		float fLastPrice;
		QModelIndex nCurrentTreeItemIndex;
		CTreeItemQuotes* pCurrentTreeItem = NULL;
		QString strLogInfo;
		QPoint point = pEvent->pos(); //get Pos
		QCursor currentCursor = this->cursor(); 

		nCurrentTreeItemIndex = this->currentIndex();
		pCurrentTreeItem = (CTreeItemQuotes*)nCurrentTreeItemIndex.internalPointer();
		nInstrumentID = pCurrentTreeItem->getInstrumentID();
		strInstrumentCode = pCurrentTreeItem->getInstrumentCode();
		fLastPrice = pCurrentTreeItem->getLastPrice();

		strLogInfo = QString("mouseDoubleClickEvent nInstrumentID=%1").arg(nInstrumentID);

		pModel = this->model();
		strLogInfo += pModel->data(nCurrentTreeItemIndex, Qt::DisplayRole).toString();

		m_pCreateNewOrderDialog->resetData(strInstrumentCode, 1, fLastPrice);
		m_pCreateNewOrderDialog->move(point);
		m_pCreateNewOrderDialog->show();
	}
	else
	{
		QModelIndex inValidIndex;
		this->setCurrentIndex(inValidIndex);
	}

}


void CQuotesTableView::slotModifySelectedColumns( QStringList lstAllAvailableColums, QStringList lstSelectedColumns )
{
	LOG_DEBUG<<" "<<"slot"
		<<" "<<"class:"<<"CQuotesTableView"
		<<" "<<"slot"
		<<" "<<"slotModifySelectedColumns(AllAvailableColums, SelectedColumns)"
		<<" "<<"param:"
		<<" "<<"lstAllAvailableColums.count="<<lstAllAvailableColums.count()
		<<" "<<"lstSelectedColumns.count="<<lstSelectedColumns.count();

	//check
	bool bIsColumnModified = false;
	int nColumnIndex_Change_NewValue = -1;

	bIsColumnModified = _CheckIsColumnModified(lstAllAvailableColums, lstSelectedColumns);
	if (!bIsColumnModified)
	{
		return;//not change
	}

	//column changed
	nColumnIndex_Change_NewValue = CConfigInfo::getInstance().getColumnIndex_Change();
	//this->setItemDelegateForColumn(nColumnIndex_Change, this->itemDelegate());
	if (-1 != nColumnIndex_Change_NewValue)
	{
		this->setItemDelegateForColumn(m_nColumnIndex_Change, this->itemDelegate());
		m_nColumnIndex_Change = nColumnIndex_Change_NewValue;
		this->setItemDelegateForColumn(m_nColumnIndex_Change, m_pIconDelegate_Column_Change);
	}

	m_strSelectedColumnsForCheck = lstSelectedColumns.join(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());

	//emit
	{
		LOG_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CQuotesTableView"
			<<" "<<"function:"<<"slotModifySelectedColumns"
			<<" "<<"emit"
			<<" "<<"signalQuotesTableViewColumnsChanged()";

		emit signalQuotesTableViewColumnsChanged();
	}
	

}

void CQuotesTableView::slotMouseRightClickInHHeaderView( QMouseEvent* e )
{
	LOG_DEBUG<<" "<<"slot"
		<<" "<<"class:"<<"CQuotesTableView"
		<<" "<<"slot"
		<<" "<<"slotMouseRightClickInHHeaderView(QMouseEvent*)"
		<<" "<<"param:"
		<<" "<<"QMouseEvent* e="<<e;

	//set menu pos
	QMenu menuRightClieck(this);
	menuRightClieck.addAction(m_pActionAddHotQuotes);
	menuRightClieck.addAction(m_pActionRemoveHotQuotes);
	menuRightClieck.addAction(m_pActionCustomColumns);
	//menuRightClieck.exec(currentCursor.pos());
	menuRightClieck.exec(QCursor::pos());
}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CQuotesTableView::_CheckIsColumnModified(const QStringList& lstAllAvailableColums, const QStringList& lstSelectedColumns)
{
	bool bIsColumnModified = false;
	QString strNewSelectedColumnsForCheck;
	//CTreeItemQuotes::getLstClumnName(strlstClumnName);
	//strLstSelectedColumnsDefault = CConfigInfo::getInstance().getLstSelectedColumnsDefault();
	strNewSelectedColumnsForCheck = lstSelectedColumns.join(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());
	//strLstAllAvailableColumsDefault = CConfigInfo::getInstance().getLstAllAvailableColumsDefault();

	if (m_strSelectedColumnsForCheck.isEmpty())
	{
		m_strSelectedColumnsForCheck = strNewSelectedColumnsForCheck;
		bIsColumnModified = true;
		return bIsColumnModified;
	}
	
	if (strNewSelectedColumnsForCheck == m_strSelectedColumnsForCheck)
	{
		bIsColumnModified = false;
	}
	else
	{
		bIsColumnModified = true;
	}

	return bIsColumnModified;
}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//QT_END_NAMESPACE










