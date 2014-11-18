#include "ContractInfoWindow.h"


#include "ProjectQTInclude.h"

#include "ContractInfo.h"
#include "TreeItemContract.h"
#include "TreeModelContract.h"



#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE

static const int DEFVALUE_INT_Window_Width = 300;
static const int DEFVALUE_INT_Window_Height = 300;



//, Qt::WindowMinMaxButtonsHint
//Qt::WStyle_Customize| Qt::WStyle_NoBorder
CContractInfoWindow::CContractInfoWindow(QWidget* parent)
: QMainWindow(parent)
{
	m_pTreeModel = NULL;	

	setupUi();
	translateLanguage();
	_CreateConnect();	
}


CContractInfoWindow::~CContractInfoWindow()
{
	if (NULL != m_pTreeModel)
	{
		delete m_pTreeModel;
		m_pTreeModel = NULL;
	}
}


void CContractInfoWindow::_CreateConnect()
{

	//
	QObject::connect(m_pTreeView_ContractInfo, 
		SIGNAL(doubleClicked ( const QModelIndex&)),
		this,
		SLOT(slotTreeViewDoubleClick(const QModelIndex&)));


}

void CContractInfoWindow::setupUi()
{
	m_pWidget_Central = new QWidget(this);

	m_pTreeView_ContractInfo = new QTreeView(m_pWidget_Central);
	m_pTreeView_ContractInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTreeView_ContractInfo->setAlternatingRowColors(true);
	m_pTreeView_ContractInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
	m_pTreeView_ContractInfo->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pTreeView_ContractInfo->setAnimated(false);
	m_pTreeView_ContractInfo->setAllColumnsShowFocus(true);
	m_pTreeView_ContractInfo->header()->setVisible(false);
	m_pTreeView_ContractInfo->header()->setStretchLastSection(false);

	m_pVBoxLayout = new QVBoxLayout(m_pWidget_Central);
	m_pVBoxLayout->setSpacing(1);
	m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
	m_pVBoxLayout->addWidget(m_pTreeView_ContractInfo);

	this->setCentralWidget(m_pWidget_Central);
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);

	QMetaObject::connectSlotsByName(this);
} // setupUi


void CContractInfoWindow::translateLanguage()
{

}


void CContractInfoWindow::slotTreeViewDoubleClick(const QModelIndex & index)
{
	MYLOG4CPP_DEBUG<<"CContractInfoWindow process slotTreeViewDoubleClick";

	QAbstractItemModel* model = NULL;

	int nRowDoubleClick = 0;
	int nColumnDoubleClick = 0;
	QString strTmp;
	Qt::ItemFlags nFlagsTreeItem;
	Qt::ItemFlags nFlagsTreeItemCheck;
	CTreeItemContract* pTreeItemGet = NULL;
	unsigned int nInstrumentID = 0;

	nFlagsTreeItemCheck = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
	model = m_pTreeView_ContractInfo->model();

	nRowDoubleClick = index.row();
	nColumnDoubleClick = index.column();

	strTmp = model->data(index, Qt::DisplayRole).toString();
	//QMessageBox::about(this, strTmp, strTmp);
	pTreeItemGet = static_cast<CTreeItemContract*>(index.internalPointer());
	nInstrumentID = pTreeItemGet->getInstrumentID();
	nFlagsTreeItem = model->flags(index);
	if (nFlagsTreeItemCheck== nFlagsTreeItem)
	{
		model->removeRow(index.row(), index.parent());//use mvc to remove node first

		MYLOG4CPP_DEBUG<<"CContractInfoWindow emit signalAddContractToSmartQuotes"
			<<" "<<"nInstrumentID="<<nInstrumentID;

		emit signalAddContractToSmartQuotes(nInstrumentID);
	}


}



void CContractInfoWindow::slotContractInfoChanged( CTreeItemContract* pTreeItem )
{
	MYLOG4CPP_DEBUG<<"CContractInfoMainWindow process signalContractInfoChanged"
		<<" "<<"pTreeItem=ox"<<pTreeItem;

	if (NULL == m_pTreeModel)
	{
		//
		m_pTreeModel = new CTreeModelContract(NULL);
		m_pTreeModel->setRootItem(pTreeItem);

		//mvc
		m_pTreeView_ContractInfo->setModel(m_pTreeModel);
		m_pTreeView_ContractInfo->setColumnWidth(0, 200);
	}
	else
	{
		m_pTreeModel->setRootItem(pTreeItem);
	}


}



//QT_END_NAMESPACE

