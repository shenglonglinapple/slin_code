#include "WaitingInstrumentTreeView.h"
#include "ProjectQTInclude.h"
#include "ItemWaitingInstrument.h"
#include "ItemModelWaitingInstrument.h"
#include "DataWaitingInstrument.h"

#include "ClientDataManager.h"
#include "Log4cppLogger.h"

static const int DEFVALUE_INT_Window_Width = 300;
static const int DEFVALUE_INT_Window_Height = 300;

CWaitingInstrumentTreeView::CWaitingInstrumentTreeView( QWidget* parent /*= 0*/ )
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::FramelessWindowHint);

	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setAlternatingRowColors(true);
	this->setSelectionBehavior(QAbstractItemView::SelectItems);
	this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	this->setAnimated(false);
	this->setAllColumnsShowFocus(true);
	this->header()->setVisible(false);
	this->header()->setResizeMode(QHeaderView::ResizeToContents );
	this->header()->setStretchLastSection(false);//true ㊣那足a角??赤?豕℅?那那車|辰?o車℅?o車辰???米?3∟?豕辰??“辰a米‘米?℅?∩車
	
	m_pItemModelWaitingInstrument = NULL;
	m_pItemModelWaitingInstrument = new CItemModelWaitingInstrument(this);
	m_pItemModelWaitingInstrument->setRootItem(CDataWaitingInstrument::getInstance().getRootItem());
	
	//mvc
	this->setModel(m_pItemModelWaitingInstrument);
	//this->setColumnWidth(0, 200);
	_CreateConnect();
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
}

CWaitingInstrumentTreeView::~CWaitingInstrumentTreeView()
{

	if (NULL != m_pItemModelWaitingInstrument)
	{
		delete m_pItemModelWaitingInstrument;
		m_pItemModelWaitingInstrument = NULL;
	}
}

void CWaitingInstrumentTreeView::_CreateConnect()
{
	QObject::connect(this, SIGNAL(doubleClicked(const QModelIndex &)), 
		this, SLOT(slotdoubleClicked(const QModelIndex &))); 

}

void CWaitingInstrumentTreeView::slotParpareWaitingInstrument()
{
	MYLOG4CPP_DEBUG<<"CWaitingInstrumentTreeView process slotParpareWaitingInstrument";

	m_pItemModelWaitingInstrument->setRootItem(CDataWaitingInstrument::getInstance().getRootItem());
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);

}

void CWaitingInstrumentTreeView::slotdoubleClicked( const QModelIndex &index )
{
	MYLOG4CPP_DEBUG<<"CWaitingInstrumentTreeView process slotdoubleClicked";

	QAbstractItemModel* pModelRef = NULL;

	int nRowDoubleClick = 0;
	int nColumnDoubleClick = 0;
	QString strTmp;
	CItemWaitingInstrument* pTreeItemRef = NULL;
	CItemWaitingInstrument::EItemType nItemType = CItemWaitingInstrument::ItemType_ITEM3_InstrumentCode;
	unsigned int nInstrumentID = 0;


	nRowDoubleClick = index.row();
	nColumnDoubleClick = index.column();
	pTreeItemRef = static_cast<CItemWaitingInstrument*>(index.internalPointer());
	nInstrumentID = pTreeItemRef->getNodeKey();
	nItemType = pTreeItemRef->getItemType();

	pModelRef = this->model();
	strTmp = pModelRef->data(index, Qt::DisplayRole).toString();
	//QMessageBox::about(this, strTmp, strTmp);


	if (CItemWaitingInstrument::ItemType_ITEM3_InstrumentCode == nItemType)
	{
		pModelRef->removeRow(index.row(), index.parent());//use mvc to remove node first

		CClientDataManager::getInstance().addUserInstrument(nInstrumentID);
	}
}
