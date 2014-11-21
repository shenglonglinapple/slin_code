#include "UserInstrumentInfoView.h"

#include <QtGui/QMenu>
#include <QtGui/QCursor>
#include <QtGui/QMessageBox>
#include <QtCore/QEvent>
#include <QtGui/QContextMenuEvent>

#include "ItemUserInstrumentInfo.h"
#include "IconDelegate.h"
#include "UserInstrumentInfoHeaderView.h"
#include "CustomColumnsDialog.h"
#include "InstrumentInfoView.h"
#include "CreateNewOrderDialog.h"

#include "ConfigInfo.h"
#include "UserOrderInfo.h"
#include "SignalSlotManager.h"
#include "ClientDataManagerWorker.h"

#include "Log4cppLogger.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


static const std::string DEFVALUE_String_ActionAddHotQuotes = "AddQuotes";//"添加合约报价";
static const std::string DEFVALUE_String_ActionRemoveHotQuotes = "RemoveQuotes";//"从列表中移除此合约报价";
static const std::string DEFVALUE_String_ActionCustomColumns = "CustomColumns";//"自定义列";

static const std::string DEFAULT_STRING_VALUE_STRING_SPLIT = ",";

CUserInstrumentInfoView::CUserInstrumentInfoView( QWidget* parent /*= 0*/ )
:QTableView(parent)
{
	m_pHorizontalHeader = NULL;
	m_pVerticalHeader = NULL;
	m_pActionAddUserInstrument = NULL;
	m_pActionRemoveUserInstrument = NULL;
	m_pActionCustomColumns = NULL;
	m_pCreateNewOrderDialog = NULL;
	m_pInstrumentInfoView = NULL;
	m_pCustomColumnsDialog = NULL;
	m_pIconDelegate_Column_Change = NULL;
	m_nColumnIndex_Change = -1;
	m_pUserOrderInfo = NULL;

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


	m_pHorizontalHeader = new CUserInstrumentInfoHeaderView(Qt::Horizontal, this);
	//m_pHorizontalHeader = this->horizontalHeader();
	this->setHorizontalHeader(m_pHorizontalHeader);
	m_pVerticalHeader = this->verticalHeader();


	m_pActionAddUserInstrument = new QAction(QObject::tr(DEFVALUE_String_ActionAddHotQuotes.c_str()), this); 
	m_pActionRemoveUserInstrument = new QAction(QObject::tr(DEFVALUE_String_ActionRemoveHotQuotes.c_str()), this); 
	m_pActionCustomColumns = new QAction(QObject::tr(DEFVALUE_String_ActionCustomColumns.c_str()), this); 

	m_pCreateNewOrderDialog = new CCreateNewOrderDialog(this);
	m_pCreateNewOrderDialog->hide();
	CSignalSlotManager::getInstance().setSignalSlot_NewOrder(m_pCreateNewOrderDialog, &(CClientDataManagerWorker::getInstance()));

	m_pInstrumentInfoView = new CInstrumentInfoView(this);
	m_pInstrumentInfoView->hide();
	CSignalSlotManager::getInstance().setSignalSlot_AddUserInstrument(m_pInstrumentInfoView, &(CClientDataManagerWorker::getInstance()));
	CSignalSlotManager::getInstance().setSignalSlot_InstrumentInfoChanged(&(CClientDataManagerWorker::getInstance()), m_pInstrumentInfoView);

	

	m_pCustomColumnsDialog = new CCustomColumnsDialog(this);
	m_pCustomColumnsDialog->hide();
	m_pUserOrderInfo = new CUserOrderInfo();

	//this->setWindowTitle(QObject::tr("Market Watch:"));
	//connect action
	_CreateConnect();

	m_strSelectedColumnsForCheck.clear();
}

CUserInstrumentInfoView::~CUserInstrumentInfoView()
{
	if (NULL != m_pActionAddUserInstrument)
	{
		delete m_pActionAddUserInstrument;
		m_pActionAddUserInstrument = NULL;
	}

	if (NULL != m_pActionRemoveUserInstrument)
	{
		delete m_pActionRemoveUserInstrument;
		m_pActionRemoveUserInstrument = NULL;
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

	if (NULL != m_pUserOrderInfo)
	{
		delete m_pUserOrderInfo;
		m_pUserOrderInfo = NULL;
	}
	

	if (NULL != m_pInstrumentInfoView)
	{
		delete m_pInstrumentInfoView;
		m_pInstrumentInfoView = NULL;
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


void CUserInstrumentInfoView::_CreateConnect()
{

	//connect action
	QObject::connect(m_pActionAddUserInstrument, 
		SIGNAL(triggered()), 
		this, 
		SLOT(slotActionAddHotQuotesTriggered())); 

	QObject::connect(m_pActionRemoveUserInstrument, 
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


void CUserInstrumentInfoView::contextMenuEvent( QContextMenuEvent* pEvent )
{

	MYLOG4CPP_DEBUG<<"CQuotesTableView process contextMenuEvent"
		<<" "<<"pEvent=0x"<<pEvent;

	//prepare data for view
	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CQuotesTableView"
			<<" "<<"fun:"<<"contextMenuEvent()"
			<<" "<<"emit"
			<<" "<<"signalContractInfoWindowResetData()";

		CSignalSlotManager::getInstance().emit_signalInstrumentViewResetData();
	}

	QPoint point;
	QCursor currentCursor;
	QModelIndex nCurrentTreeItemIndex;
	CItemUserInstrumentInfo* pCurrentTreeItem = NULL;
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
		menuRightClieck.addAction(m_pActionAddUserInstrument);	//first ContractInfoWindow reset data
		menuRightClieck.exec(QCursor::pos());
		return;
	}

	//treeview line have data
	pCurrentTreeItem = (CItemUserInstrumentInfo*)nCurrentTreeItemIndex.internalPointer();
	MYLOG4CPP_DEBUG<<"CQuotesTableView::contextMenuEvent"
		<<" "<<"getInstrumentID="<<pCurrentTreeItem->getInstrumentID()
		<<" "<<"getInstrumentCode="<<pCurrentTreeItem->getInstrumentCode().toStdString()
		<<" "<<"getExchangeName="<<pCurrentTreeItem->getExchangeName().toStdString();
	//QMessageBox::about(this, strLogInfo, strLogInfo);

	//set Current Instrument
	CClientDataManagerWorker::getInstance().setCurrentInstrument(pCurrentTreeItem->getInstrumentID());
	//set menu pos
	QMenu menuRightClieck(this);
	menuRightClieck.addAction(m_pActionAddUserInstrument);	//first ContractInfoWindow reset data
	menuRightClieck.addAction(m_pActionRemoveUserInstrument);
	menuRightClieck.addAction(m_pActionCustomColumns);
	//menuRightClieck.exec(currentCursor.pos());
	menuRightClieck.exec(QCursor::pos());
	pEvent->accept();
}


void CUserInstrumentInfoView::slotActionRemoveHotQuotesTriggered()
{
	MYLOG4CPP_DEBUG<<"CQuotesTableView process slotActionRemoveHotQuotesTriggered";

	QAbstractItemModel* pModel = NULL;
	int nRowDoubleClick = 0;
	int nColumnDoubleClick = 0;
	Qt::ItemFlags nFlagsTreeItem;
	unsigned int nInstrumentID = 0;
	QModelIndex nCurrentTreeItemIndex;
	CItemUserInstrumentInfo* pCurrentTreeItem = NULL;
	QString strLogInfo;


	nCurrentTreeItemIndex = this->currentIndex();
	if (false == nCurrentTreeItemIndex.isValid())
	{
		return;
	}
	pCurrentTreeItem = (CItemUserInstrumentInfo*)nCurrentTreeItemIndex.internalPointer();
	nInstrumentID = pCurrentTreeItem->getInstrumentID();

	//strLogInfo = QString("contextMenuEvent nInstrumentID=%1").arg(nInstrumentID);

	pModel = this->model();
	nRowDoubleClick = nCurrentTreeItemIndex.row();
	nColumnDoubleClick = nCurrentTreeItemIndex.column();
	//strLogInfo += pModel->data(nCurrentTreeItemIndex, Qt::DisplayRole).toString();


	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CQuotesTableView"
		<<" "<<"fun:"<<"slotActionRemoveHotQuotesTriggered()"
		<<" "<<"emit"
		<<" "<<"signalRemoveContractFromSmartQuotes(unsigned int)"
		<<" "<<"param:"
		<<" "<<"nInstrumentID="<<pCurrentTreeItem->getInstrumentID()
		<<" "<<"getInstrumentCode="<<pCurrentTreeItem->getInstrumentCode().toStdString()
		<<" "<<"getExchangeName="<<pCurrentTreeItem->getExchangeName().toStdString();

	pModel->removeRow(nCurrentTreeItemIndex.row(), nCurrentTreeItemIndex.parent());

	CSignalSlotManager::getInstance().emit_signalRemoveUserInstrument(nInstrumentID);

}

void CUserInstrumentInfoView::slotActionAddHotQuotesTriggered()
{
	MYLOG4CPP_DEBUG<<"CQuotesTableView process slotActionAddHotQuotesTriggered";

	//first ContractInfoWindow reset data

	QCursor currentCursor = this->cursor(); 
	currentCursor.pos();

	m_pInstrumentInfoView->move(QCursor::pos());
	m_pInstrumentInfoView->show();

}


void CUserInstrumentInfoView::slotActionCustomColumnsTriggered()
{
	MYLOG4CPP_DEBUG<<"CQuotesTableView process slotActionCustomColumnsTriggered";
	m_pCustomColumnsDialog->show();
}


void CUserInstrumentInfoView::mouseDoubleClickEvent( QMouseEvent* pEvent )
{
	if (Qt::LeftButton == pEvent->button())
	{
		MYLOG4CPP_DEBUG<<"CQuotesTableView process mouseDoubleClickEvent Qt::LeftButton";

		QAbstractItemModel* pModel = NULL;
		QModelIndex nCurrentTreeItemIndex;
		CItemUserInstrumentInfo* pCurrentTreeItem = NULL;
		QPoint point = pEvent->pos(); //get Pos
		QCursor currentCursor = this->cursor(); 

		nCurrentTreeItemIndex = this->currentIndex();
		pCurrentTreeItem = (CItemUserInstrumentInfo*)nCurrentTreeItemIndex.internalPointer();
		//set Current Instrument
		CClientDataManagerWorker::getInstance().setCurrentInstrument(pCurrentTreeItem->getInstrumentID());
		pModel = this->model();

		m_pUserOrderInfo->setDataByItem(pCurrentTreeItem);
		m_pUserOrderInfo->m_nQuantity = 1;
		m_pCreateNewOrderDialog->resetData(m_pUserOrderInfo);
		m_pCreateNewOrderDialog->move(QCursor::pos());		
		m_pCreateNewOrderDialog->show();
	}
	else
	{
		QModelIndex inValidIndex;
		this->setCurrentIndex(inValidIndex);
	}

}


void CUserInstrumentInfoView::slotModifySelectedColumns( QStringList lstAllAvailableColums, QStringList lstSelectedColumns )
{
	MYLOG4CPP_DEBUG<<"CQuotesTableView process slotModifySelectedColumns"
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
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CQuotesTableView"
			<<" "<<"function:"<<"slotModifySelectedColumns"
			<<" "<<"emit"
			<<" "<<"signalQuotesTableViewColumnsChanged()";

		CSignalSlotManager::getInstance().emit_signalUserInstrumentViewColumnsChanged();
	}
	

}

void CUserInstrumentInfoView::slotMouseRightClickInHHeaderView( QMouseEvent* e )
{
	MYLOG4CPP_DEBUG<<"CQuotesTableView process slotMouseRightClickInHHeaderView"
		<<" "<<"param:"
		<<" "<<"QMouseEvent* e=0x"<<e;

	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CQuotesTableView"
			<<" "<<"fun:"<<"slotMouseRightClickInHHeaderView(e)"
			<<" "<<"emit"
			<<" "<<"signalContractInfoWindowResetData()";

		CSignalSlotManager::getInstance().emit_signalInstrumentViewResetData();
	}

	//set menu pos
	QMenu menuRightClieck(this);
	menuRightClieck.addAction(m_pActionAddUserInstrument);	//first ContractInfoWindow reset data
	menuRightClieck.addAction(m_pActionRemoveUserInstrument);
	menuRightClieck.addAction(m_pActionCustomColumns);
	//menuRightClieck.exec(currentCursor.pos());
	menuRightClieck.exec(QCursor::pos());
}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

bool CUserInstrumentInfoView::_CheckIsColumnModified(const QStringList& lstAllAvailableColums, const QStringList& lstSelectedColumns)
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










