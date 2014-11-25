#include "MainWindowToolBar.h"

#include <QtGui/QAction>
#include "Bar.h"
#include "Log4cppLogger.h"

static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Text = "BarInfo";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M1_Text = "M1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M5_Text = "M5";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M15_Text = "M15";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M30_Text = "M30";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_H1_Text = "H1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_D1_Text = "D1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_W1_Text = "W1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_MN_Text = "WN";


CMainWindowToolBar::CMainWindowToolBar( const QString &title, QWidget *parent /*= 0*/ )
:QToolBar(title, parent)
{
	m_nCurrentInstrumentID = 1;
	m_nCurrentBarType = DAY;

	_CreateActions();
	_AddAction();
	translateLanguage();
	_CreateConnect();
	
	m_pAction_BarInfo_D1->setChecked(true);//default D1
	m_pAction_BarInfo_D1->trigger();//default D1
	
}

CMainWindowToolBar::CMainWindowToolBar( QWidget *parent /*= 0*/ )
:QToolBar(parent)
{
	m_nCurrentInstrumentID = 1;
	m_nCurrentBarType = DAY;

	_CreateActions();
	_AddAction();
	translateLanguage();
	_CreateConnect();
	
	m_pAction_BarInfo_D1->setChecked(true);//default D1
	m_pAction_BarInfo_D1->trigger();//default D1

}

CMainWindowToolBar::~CMainWindowToolBar()
{

}

void CMainWindowToolBar::_CreateActions()
{
	m_pAction_Group_BarType = new QActionGroup(this);

	m_pAction_BarInfo_M1 = new QAction(this); 
	m_pAction_BarInfo_M1->setCheckable(true);
	m_pAction_BarInfo_M1->setChecked(false);
	m_pAction_Group_BarType->addAction(m_pAction_BarInfo_M1);

	m_pAction_BarInfo_M5 = new QAction(this); 
	m_pAction_BarInfo_M5->setCheckable(true);
	m_pAction_BarInfo_M5->setChecked(false);
	m_pAction_Group_BarType->addAction(m_pAction_BarInfo_M5);

	m_pAction_BarInfo_M15 = new QAction(this); 
	m_pAction_BarInfo_M15->setCheckable(true);
	m_pAction_BarInfo_M15->setChecked(false);
	m_pAction_Group_BarType->addAction(m_pAction_BarInfo_M15);

	m_pAction_BarInfo_M30 = new QAction(this); 
	m_pAction_BarInfo_M30->setCheckable(true);
	m_pAction_BarInfo_M30->setChecked(false);
	m_pAction_Group_BarType->addAction(m_pAction_BarInfo_M30);

	m_pAction_BarInfo_H1 = new QAction(this); 
	m_pAction_BarInfo_H1->setCheckable(true);
	m_pAction_BarInfo_H1->setChecked(false);
	m_pAction_Group_BarType->addAction(m_pAction_BarInfo_H1);

	m_pAction_BarInfo_D1 = new QAction(this);
	m_pAction_BarInfo_D1->setCheckable(true);
	m_pAction_BarInfo_D1->setChecked(false);//default D1
	m_pAction_Group_BarType->addAction(m_pAction_BarInfo_D1);

	m_pAction_BarInfo_W1 = new QAction(this);
	m_pAction_BarInfo_W1->setCheckable(true);
	m_pAction_BarInfo_W1->setChecked(false);
	m_pAction_Group_BarType->addAction(m_pAction_BarInfo_W1);

	m_pAction_BarInfo_MN = new QAction(this);
	m_pAction_BarInfo_MN->setCheckable(true);
	m_pAction_BarInfo_MN->setChecked(false);
	m_pAction_Group_BarType->addAction(m_pAction_BarInfo_MN);
}
void CMainWindowToolBar::_AddAction()
{	
	this->addActions(m_pAction_Group_BarType->actions());

}
void CMainWindowToolBar::_CreateConnect()
{
	QObject::connect(m_pAction_BarInfo_M1, SIGNAL(triggered()), 
		this, SLOT(slotActionM1Triggered()));

	QObject::connect(m_pAction_BarInfo_M5, SIGNAL(triggered()), 
		this, SLOT(slotActionM5Triggered()));

	QObject::connect(m_pAction_BarInfo_M15, SIGNAL(triggered()), 
		this, SLOT(slotActionM15Triggered()));

	QObject::connect(m_pAction_BarInfo_M30, SIGNAL(triggered()), 
		this, SLOT(slotActionM30Triggered()));

	QObject::connect(m_pAction_BarInfo_H1, SIGNAL(triggered()), 
		this, SLOT(slotActionH1Triggered()));

	QObject::connect(m_pAction_BarInfo_D1, SIGNAL(triggered()), 
		this, SLOT(slotActionD1Triggered()));
	
	QObject::connect(m_pAction_BarInfo_W1, SIGNAL(triggered()), 
		this, SLOT(slotActionW1Triggered()));

	QObject::connect(m_pAction_BarInfo_MN, SIGNAL(triggered()), 
		this, SLOT(slotActionMNTriggered()));

}
void CMainWindowToolBar::translateLanguage()
{
	//
	m_pAction_BarInfo_M1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M1_Text.c_str()));
	m_pAction_BarInfo_M5->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M5_Text.c_str()));
	m_pAction_BarInfo_M15->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M15_Text.c_str()));
	m_pAction_BarInfo_M30->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M30_Text.c_str()));
	m_pAction_BarInfo_H1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_H1_Text.c_str()));
	m_pAction_BarInfo_D1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_D1_Text.c_str()));
	m_pAction_BarInfo_W1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_W1_Text.c_str()));
	m_pAction_BarInfo_MN->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_MN_Text.c_str()));
}



void CMainWindowToolBar::slotActionM1Triggered()
{
	enum BarType  nBarType = MINUTE;
	setHistoryBarType(nBarType, "MINUTE");
}
void CMainWindowToolBar::slotActionM5Triggered()
{
	enum BarType  nBarType = FIVE_MINUTE;
	setHistoryBarType(nBarType, "FIVE_MINUTE");
}
void CMainWindowToolBar::slotActionM15Triggered()
{
	enum BarType  nBarType = FIFTEEN_MINUTE;
	setHistoryBarType(nBarType, "FIFTEEN_MINUTE");
}
void CMainWindowToolBar::slotActionM30Triggered()
{
	enum BarType  nBarType = THIRTY_MINUTE;
	setHistoryBarType(nBarType, "THIRTY_MINUTE");
}
void CMainWindowToolBar::slotActionH1Triggered()
{
	enum BarType  nBarType = ONE_HOUR;
	setHistoryBarType(nBarType, "ONE_HOUR");
}
void CMainWindowToolBar::slotActionD1Triggered()
{
	enum BarType  nBarType = DAY;
	setHistoryBarType(nBarType, "DAY");
}
void CMainWindowToolBar::slotActionW1Triggered()
{
	enum BarType  nBarType = WEEK;
	setHistoryBarType(nBarType, "WEEK");
}
void CMainWindowToolBar::slotActionMNTriggered()
{
	enum BarType  nBarType = MONTH;
	setHistoryBarType(nBarType, "MONTH");
}

void CMainWindowToolBar::setCurrentInstrumentID( unsigned int nInstrumentID )
{
	m_nCurrentInstrumentID = nInstrumentID;
	MYLOG4CPP_DEBUG<<"CMainWindowToolBar setCurrentInstrumentID"
		<<" "<<"m_nCurrentInstrumentID="<<m_nCurrentInstrumentID;
}

unsigned int CMainWindowToolBar::getCurrentInstrumentID()
{
	return m_nCurrentInstrumentID;
}

void CMainWindowToolBar::setHistoryBarType( enum BarType nBarType, const QString& strBarType )
{
	m_nCurrentBarType = nBarType;
	MYLOG4CPP_DEBUG<<"CMainWindowToolBar setHistoryBarType"
				<<" "<<"m_nCurrentBarType="<<m_nCurrentBarType
				<<" "<<"strBarType="<<strBarType.toStdString();

	if (1 == m_nCurrentInstrumentID)
	{
		MYLOG4CPP_DEBUG<<"CMainWindowToolBar setHistoryBarType"
			<<" "<<"1 == m_nCurrentInstrumentID not emit signalRequestHistoryData";
		return;
	}

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CMainWindowToolBar"
		<<" "<<"fun:"<<"setHistoryBarType()"
		<<" "<<"emit"
		<<" "<<"signalRequestHistoryData()"
		<<" "<<"param:"
		<<" "<<"m_nCurrentInstrumentID="<<m_nCurrentInstrumentID
		<<" "<<"m_nCurrentBarType="<<m_nCurrentBarType;

	emit signalRequestHistoryData(m_nCurrentInstrumentID, m_nCurrentBarType);
}

enum BarType CMainWindowToolBar::getHistoryBarType()
{
	return m_nCurrentBarType;
}


