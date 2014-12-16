#include "UserInstrumentTableView.h"
#include "DataUserInstrument.h"
#include "ItemModelUserInstrument.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"

CUserInstrumentTableView::CUserInstrumentTableView( QWidget* parent)
:QTableView(parent)
{
	m_pItemModelUserInstrument = NULL;
	m_pItemModelUserInstrument = new CItemModelUserInstrument(this);
	m_pItemModelUserInstrument->setRootItem(CDataUserInstrument::getInstance().getRootItem());
	this->setModel(m_pItemModelUserInstrument);

	CSignalSlotManager::getInstance().set_SignalSlot_DataChange_UserInstrument(NULL, this);
}

CUserInstrumentTableView::~CUserInstrumentTableView()
{
	if (NULL != m_pItemModelUserInstrument)
	{
		delete m_pItemModelUserInstrument;
		m_pItemModelUserInstrument = NULL;
	}
}

void CUserInstrumentTableView::slot_DataChange_UserInstrument()
{
	MYLOG4CPP_DEBUG<<"CUserInstrumentTableView process slot_DataChange_UserInstrument";
	QModelIndex inValidIndex;
	m_pItemModelUserInstrument->setRootItem(CDataUserInstrument::getInstance().getRootItem());
	this->setCurrentIndex(inValidIndex);
}

