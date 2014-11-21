#include "InstrumentInfoView.h"

#include "ProjectQTInclude.h"

#include "ItemInstrumentInfo.h"
#include "ItemModelInstrumentInfo.h"

#include "DataInstrument.h"
#include "SignalSlotManager.h"

#include "InstrumentInfoHelper.h"



#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE

static const int DEFVALUE_INT_Window_Width = 300;
static const int DEFVALUE_INT_Window_Height = 300;



//, Qt::WindowMinMaxButtonsHint
//Qt::WStyle_Customize| Qt::WStyle_NoBorder
CInstrumentInfoView::CInstrumentInfoView(QWidget* parent)
: QMainWindow(parent)
{
	m_pItemModelInstrumentInfo = NULL;	

	setupUi();
	translateLanguage();
	_CreateConnect();

	slotInstrumentInfoChanged(CDataInstrument::getInstance().getRootHandle());
}


CInstrumentInfoView::~CInstrumentInfoView()
{
	if (NULL != m_pItemModelInstrumentInfo)
	{
		delete m_pItemModelInstrumentInfo;
		m_pItemModelInstrumentInfo = NULL;
	}
}


void CInstrumentInfoView::_CreateConnect()
{

	//
	QObject::connect(m_pTreeView_InstrumentInfo, 
		SIGNAL(doubleClicked ( const QModelIndex&)),
		this,
		SLOT(slotTreeViewDoubleClick(const QModelIndex&)));


}

void CInstrumentInfoView::setupUi()
{
	m_pWidget_Central = new QWidget(this);

	m_pTreeView_InstrumentInfo = new QTreeView(m_pWidget_Central);
	m_pTreeView_InstrumentInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTreeView_InstrumentInfo->setAlternatingRowColors(true);
	m_pTreeView_InstrumentInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
	m_pTreeView_InstrumentInfo->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pTreeView_InstrumentInfo->setAnimated(false);
	m_pTreeView_InstrumentInfo->setAllColumnsShowFocus(true);
	m_pTreeView_InstrumentInfo->header()->setVisible(false);
	m_pTreeView_InstrumentInfo->header()->setStretchLastSection(false);

	m_pVBoxLayout = new QVBoxLayout(m_pWidget_Central);
	m_pVBoxLayout->setSpacing(1);
	m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
	m_pVBoxLayout->addWidget(m_pTreeView_InstrumentInfo);

	this->setCentralWidget(m_pWidget_Central);
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);

	QMetaObject::connectSlotsByName(this);
} // setupUi


void CInstrumentInfoView::translateLanguage()
{

}


void CInstrumentInfoView::slotTreeViewDoubleClick(const QModelIndex & index)
{
	MYLOG4CPP_DEBUG<<"CContractInfoWindow process slotTreeViewDoubleClick";

	QAbstractItemModel* model = NULL;

	int nRowDoubleClick = 0;
	int nColumnDoubleClick = 0;
	QString strTmp;
	Qt::ItemFlags nFlagsTreeItem;
	Qt::ItemFlags nFlagsTreeItemCheck;
	CItemInstrumentInfo* pTreeItemGet = NULL;
	unsigned int nInstrumentID = 0;

	nFlagsTreeItemCheck = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
	model = m_pTreeView_InstrumentInfo->model();

	nRowDoubleClick = index.row();
	nColumnDoubleClick = index.column();

	strTmp = model->data(index, Qt::DisplayRole).toString();
	//QMessageBox::about(this, strTmp, strTmp);
	pTreeItemGet = static_cast<CItemInstrumentInfo*>(index.internalPointer());
	nInstrumentID = pTreeItemGet->getInstrumentID();
	nFlagsTreeItem = model->flags(index);
	if (nFlagsTreeItemCheck== nFlagsTreeItem)
	{
		model->removeRow(index.row(), index.parent());//use mvc to remove node first

		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CContractInfoWindow"
			<<" "<<"fun:"<<"slotTreeViewDoubleClick()"
			<<" "<<"emit"
			<<" "<<"signalAddContractToSmartQuotes(unsigned int)"
			<<" "<<"param:"
			<<" "<<"nInstrumentID="<<nInstrumentID;
		CSignalSlotManager::getInstance().emit_signalAddUserInstrument(nInstrumentID);
	}


}



void CInstrumentInfoView::slotInstrumentInfoChanged( CItemInstrumentInfo* pTreeItem )
{
	MYLOG4CPP_DEBUG<<"CContractInfoMainWindow process signalContractInfoChanged"
		<<" "<<"pTreeItem=ox"<<pTreeItem;

	if (NULL == m_pItemModelInstrumentInfo)
	{
		//
		m_pItemModelInstrumentInfo = new CItemModelInstrumentInfo(NULL);
		m_pItemModelInstrumentInfo->setRootItem(pTreeItem);

		//mvc
		m_pTreeView_InstrumentInfo->setModel(m_pItemModelInstrumentInfo);
		m_pTreeView_InstrumentInfo->setColumnWidth(0, 200);
	}
	else
	{
		m_pItemModelInstrumentInfo->setRootItem(pTreeItem);
	}


}



//QT_END_NAMESPACE

