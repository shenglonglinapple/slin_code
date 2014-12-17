#include "WaitingInstrumentTreeView.h"
#include "ProjectQTInclude.h"
#include "ItemModelWaitingInstrument.h"
#include "DataWaitingInstrument.h"
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
	this->header()->setStretchLastSection(false);


	
	m_pItemModelWaitingInstrument = NULL;
	m_pItemModelWaitingInstrument = new CItemModelWaitingInstrument(this);
	m_pItemModelWaitingInstrument->setRootItem(CDataWaitingInstrument::getInstance().getRootItem());

	//mvc
	this->setModel(m_pItemModelWaitingInstrument);
	//this->setColumnWidth(0, 200);


}

CWaitingInstrumentTreeView::~CWaitingInstrumentTreeView()
{

	if (NULL != m_pItemModelWaitingInstrument)
	{
		delete m_pItemModelWaitingInstrument;
		m_pItemModelWaitingInstrument = NULL;
	}
}

void CWaitingInstrumentTreeView::resetData()
{
	m_pItemModelWaitingInstrument->setRootItem(CDataWaitingInstrument::getInstance().getRootItem());
}