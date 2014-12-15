#include "UserInstrumentWindow.h"

#include "ProjectQTInclude.h"
#include "UserInstrumentTableView.h"
#include "ItemModelUserInstrument.h"
#include "DataUserInstrument.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 400;
static int DEFVALUE_INT_Window_Height = 300;



CUserInstrumentWindow::CUserInstrumentWindow(QWidget* parent)
    : QMdiSubWindow(parent)
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);



	//
	m_pItemModelUserInstrument = NULL;
	m_pItemModelUserInstrument = new CItemModelUserInstrument(this);
	//
	m_pUserInstrumentTableView = NULL;
	m_pUserInstrumentTableView = new CUserInstrumentTableView(this);


	CItemUserInstrument* pGetRootItemRef = NULL;
	pGetRootItemRef = CDataUserInstrument::getInstance().getRootItem();
	m_pItemModelUserInstrument->setRootItem(pGetRootItemRef);

	m_pUserInstrumentTableView->setModel(m_pItemModelUserInstrument);
	m_pUserInstrumentTableView->move(10, 10);
	m_pUserInstrumentTableView->resize(200, 200);

	QVBoxLayout* pVBoxLayout;
	pVBoxLayout = new QVBoxLayout(this);
	pVBoxLayout->addWidget(m_pUserInstrumentTableView);
	this->setLayout(pVBoxLayout);

	
}


CUserInstrumentWindow::~CUserInstrumentWindow()
{
	if (NULL != m_pItemModelUserInstrument)
	{
		delete m_pItemModelUserInstrument;
		m_pItemModelUserInstrument = NULL;
	}
	
}


QSize CUserInstrumentWindow::sizeHint() const
{
	//for QDockWidget
	return QSize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height); /* 在这里定义dock的初始大小 */
}

