#include "LoginSettingWindow.h"

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE

static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 300;

static const char* DEFVALUE_String_Window_Title_Text = "Server Setting";

static const char* DEFVALUE_String_Label_IPAddress_Text = "IP Address:";
static const char* DEFVALUE_String_Label_Port_Text = "Port:";
static const char* DEFVALUE_String_PushButton_OK_Text = "OK";
static const char* DEFVALUE_String_PushButton_Cancel_Text = "Cancel";

	


CLoginSettingWindow::CLoginSettingWindow(QWidget *parent)
: QDialog(parent)
{
	m_pLabel_IPAddress = NULL;
	m_pLineEdit_IPAddress = NULL;
	m_pLabel_Port = NULL;
	m_pLineEdit_Port = NULL;
	m_pPushButton_OK = NULL;
	m_pPushButton_Cancel = NULL;

	m_str_LineEdit_IPAddress_Value.clear();
	m_str_LineEdit_Port_Value.clear();


	_SetupUi();
	_TranslateLanguage();
	_CreateConnect();
}


CLoginSettingWindow::~CLoginSettingWindow()
{
}

void CLoginSettingWindow::_CreateConnect()
{
	QObject::connect(m_pPushButton_OK, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotButtonOKlicked(bool)));

	QObject::connect(m_pPushButton_Cancel, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotButtonCancellicked(bool)));
}


void CLoginSettingWindow::_SetupUi()
{
	QGridLayout* pGridLayout_Main = NULL;
	QSize qSizeLeftAreaOne(100, 20);
	QSize qSizeRightAreaOne(200, 20);
	int nSpacing = 10;
	int nMargin = 10;


	m_pLabel_IPAddress = new QLabel(this);

	m_pLineEdit_IPAddress = new QLineEdit(this);
	m_pLineEdit_IPAddress->setMinimumSize(qSizeRightAreaOne);

	m_pLabel_Port = new QLabel(this);

	m_pLineEdit_Port = new QLineEdit(this);
	m_pLineEdit_Port->setMinimumSize(qSizeRightAreaOne);


	m_pPushButton_OK = new QPushButton(this);
	m_pPushButton_OK->setDefault(true);

	m_pPushButton_Cancel = new QPushButton(this);
	m_pPushButton_Cancel->setDefault(false);

	pGridLayout_Main = new QGridLayout(this);
	pGridLayout_Main->addWidget(m_pLabel_IPAddress, 0, 0, 1, 1);
	pGridLayout_Main->addWidget(m_pLineEdit_IPAddress, 0, 1, 1, 2);
	pGridLayout_Main->addWidget(m_pLabel_Port, 1, 0, 1, 1);
	pGridLayout_Main->addWidget(m_pLineEdit_Port, 1, 1, 1, 2);
	pGridLayout_Main->addWidget(m_pPushButton_OK, 2, 0, 1, 1);
	pGridLayout_Main->addWidget(m_pPushButton_Cancel, 2, 2, 1, 1);

	
	this->setLayout(pGridLayout_Main);
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);

	QMetaObject::connectSlotsByName(this);
}


void CLoginSettingWindow::_TranslateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title_Text));

	m_pLabel_IPAddress->setText(QObject::tr(DEFVALUE_String_Label_IPAddress_Text));
	m_pLineEdit_IPAddress->setText(QObject::tr(DEFVALUE_String_ServerIP));
	m_pLabel_Port->setText(QObject::tr(DEFVALUE_String_Label_Port_Text));
	m_pLineEdit_Port->setText(QString("%1").arg(DEFVALUE_Int_ServerPort));
	m_pPushButton_OK->setText(QObject::tr(DEFVALUE_String_PushButton_OK_Text));
	m_pPushButton_Cancel->setText(QObject::tr(DEFVALUE_String_PushButton_Cancel_Text));

}





void CLoginSettingWindow::slotButtonOKlicked( bool checked )
{
	QString strServerIP;
	qint32 nServerPort;

	m_str_LineEdit_IPAddress_Value = m_pLineEdit_IPAddress->text();
	m_str_LineEdit_Port_Value = m_pLineEdit_Port->text();

	strServerIP = m_str_LineEdit_IPAddress_Value;
	nServerPort = m_str_LineEdit_Port_Value.toInt();

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CLoginSettingWindow"
		<<" "<<"fun:"<<"slotButtonOKlicked()"
		<<" "<<"emit"
		<<" "<<"signalServerInfoChanged(strServerIP, nServerPort)"
		<<" "<<"param:"
		<<" "<<"strServerIP="<<strServerIP
		<<" "<<"nServerPort="<<nServerPort;

	emit signalServerInfoChanged(strServerIP, nServerPort);

	this->setVisible(false);
	this->close();
}

void CLoginSettingWindow::slotButtonCancellicked( bool checked )
{
	this->setVisible(false);
	this->close();
}


//QT_END_NAMESPACE

