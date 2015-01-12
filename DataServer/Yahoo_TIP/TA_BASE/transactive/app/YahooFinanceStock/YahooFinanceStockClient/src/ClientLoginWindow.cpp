#include "ClientLoginWindow.h"

#include "ProjectCommonData.h"

#include "ClientLoginParam.h"
#include "LoginSettingWindow.h"
#include "PwdLineEdit.h"

#include "ClientWorkerManager.h"

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE

static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 300;

static const char* DEFVALUE_String_Window_Title_Text = "SmartTrader";


static const char* DEFVALUE_String_Label_UserName_Text = "User Name:";
static const char* DEFVALUE_String_Label_Password_Text = "Password:";
static const char* DEFVALUE_String_Button_Settings_Text = "Settings";
static const char* DEFVALUE_String_Button_Login_Text = "Login";
static const char* DEFVALUE_String_Button_Cancel_Text = "Cancel";
	
static const char* DEF_VALUE_MainWidgetWindowIcon = ":/images/MainWidgetWindowIcon.ico";//任务栏中的图标


CClientLoginWindow::CClientLoginWindow(QWidget *parent)
: QDialog(parent)
{
	m_strUserName.clear();
	m_strPassWord.clear();
	m_strServerIP.clear();
	m_nServerPort = 0;

	m_pLabel_UserName  = NULL;
	m_pComboBox_UserName  = NULL;

	m_pLabel_Password  = NULL;
	m_pLineEdit_Password  = NULL;

	m_pPushButtonSetting  = NULL;
	m_pPushButtonLogin  = NULL;
	m_pPushButtonCancle  = NULL;

	m_pLoginSettingWindow = NULL;

	m_pComboBox_UserName_Value.clear();
	m_pLineEdit_Password_Value.clear();

	CClientLoginParam loginParam;
	m_strUserName = loginParam.m_strUserName;
	m_strPassWord = loginParam.m_strPassWord;
	m_strServerIP = loginParam.m_strServerIP;
	m_nServerPort = loginParam.m_nServerPort;

	m_pLoginSettingWindow = new CLoginSettingWindow(this);

	_SetupUi();
	_TranslateLanguage();
	_CreateConnect();
}


CClientLoginWindow::~CClientLoginWindow()
{

}

void CClientLoginWindow::_CreateConnect()
{
	QObject::connect(m_pLoginSettingWindow, 
		SIGNAL(signalServerInfoChanged(QString, int)),
		this, 
		SLOT(slotServerInfoChanged(QString, int)));

	QObject::connect(m_pPushButtonSetting, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotButtonSettingClicked(bool)));

	QObject::connect(m_pPushButtonLogin, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotButtonLoginClicked(bool)));

	QObject::connect(m_pPushButtonCancle, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotButtonCancelClicked(bool)));

}


void CClientLoginWindow::_SetupUi()
{
	QGridLayout* pGridLayout_UserInfo = NULL;
	QSize qSizeLeftAreaOne(100, 20);
	QSize qSizeRightAreaOne(200, 20);
	int nSpacing = 10;
	int nMargin = 10;



	m_pLabel_UserName = new QLabel(this);
	
	m_pComboBox_UserName = new QComboBox(this);
	m_pComboBox_UserName->setEditable(true);
	m_pComboBox_UserName->setMinimumSize(qSizeRightAreaOne);
	m_pLabel_UserName->setBuddy(m_pComboBox_UserName);

	m_pLabel_Password = new QLabel(this);

	m_pLineEdit_Password = new CPwdLineEdit(this);
	m_pLineEdit_Password->setEchoMode(QLineEdit::Password);
	m_pLineEdit_Password->setMinimumSize(qSizeRightAreaOne);
	m_pLabel_Password->setBuddy(m_pLineEdit_Password);

	m_pPushButtonSetting = new QPushButton(this);
	m_pPushButtonSetting->setDefault(false);

	m_pPushButtonLogin = new QPushButton(this);
	m_pPushButtonLogin->setFocus();//设置默认焦点
	m_pPushButtonLogin->setShortcut( QKeySequence::InsertParagraphSeparator );//设置快捷键为键盘的“回车”键
	m_pPushButtonLogin->setShortcut(Qt::Key_Enter);//设置快捷键为enter键
	m_pPushButtonLogin->setShortcut(Qt::Key_Return);//设置快捷键为小键盘上的enter键
	m_pPushButtonLogin->setDefault(true);//设置默认按钮，设置了这个属性，当用户按下回车的时候，就会按下该按钮


	m_pPushButtonCancle = new QPushButton(this);
	m_pPushButtonCancle->setDefault(false);

	pGridLayout_UserInfo = new QGridLayout(this);
	pGridLayout_UserInfo->addWidget(m_pLabel_UserName, 0, 0, 1, 1);
	pGridLayout_UserInfo->addWidget(m_pComboBox_UserName, 0, 1, 1,2);
	pGridLayout_UserInfo->addWidget(m_pLabel_Password, 1, 0, 1, 1);
	pGridLayout_UserInfo->addWidget(m_pLineEdit_Password, 1, 1, 1, 2);
	pGridLayout_UserInfo->addWidget(m_pPushButtonSetting, 2, 0, 1, 1);
	pGridLayout_UserInfo->addWidget(m_pPushButtonLogin, 2, 1, 1, 1);
	pGridLayout_UserInfo->addWidget(m_pPushButtonCancle, 2, 2, 1, 1);



	this->setLayout(pGridLayout_UserInfo);

	this->setWindowIcon(QIcon(QObject::tr(DEF_VALUE_MainWidgetWindowIcon)));//任务栏中的图标
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);


	QMetaObject::connectSlotsByName(this);
}



void CClientLoginWindow::_TranslateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title_Text));

	m_pLabel_UserName->setText(QObject::tr(DEFVALUE_String_Label_UserName_Text));
	m_pComboBox_UserName->insertItem(0, QObject::tr(DEFVALUE_String_UserName));
	m_pComboBox_UserName->setCurrentIndex(0);
	m_pLabel_Password->setText(QObject::tr(DEFVALUE_String_Label_Password_Text));
	m_pLineEdit_Password->setText(QObject::tr(DEFVALUE_String_PassWord));
	m_pPushButtonSetting->setText(QObject::tr(DEFVALUE_String_Button_Settings_Text));
	m_pPushButtonLogin->setText(QObject::tr(DEFVALUE_String_Button_Login_Text));
	m_pPushButtonCancle->setText(QObject::tr(DEFVALUE_String_Button_Cancel_Text));

}


void CClientLoginWindow::slotButtonSettingClicked( bool checked )
{
	m_pLoginSettingWindow->show();
}

void CClientLoginWindow::slotButtonLoginClicked( bool checked )
{
	int nloginToServerRes = -1;

	m_pComboBox_UserName_Value = m_pComboBox_UserName->currentText();
	m_pLineEdit_Password_Value = m_pLineEdit_Password->text();

	MYLOG4CPP_DEBUG<<"set client info"
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassWord="<<m_strPassWord;

	m_strUserName = m_pComboBox_UserName_Value;
	m_strPassWord = m_pLineEdit_Password_Value;

	CClientLoginParam loginParam;
	loginParam.setValue(m_strUserName, m_strPassWord, m_strServerIP, m_nServerPort);
	loginParam.logInfo(__FILE__, __LINE__);
	CClientWorkerManager::getInstance().createClient(&loginParam);

	this->setVisible(false);
	this->close();
	
}

void CClientLoginWindow::slotButtonCancelClicked( bool checked )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<"CClientLoginWindow"
		<<" "<<"slot:"<<"slotButtonCancelClicked()"
		<<" "<<"param:"
		<<" "<<"checked="<<checked;

	this->close();
}



void CClientLoginWindow::slotServerInfoChanged(QString strServerIP, int nServerPort)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<"CClientLoginWindow"
		<<" "<<"slot:"<<"slotServerInfoChanged()"
		<<" "<<"param:"
		<<" "<<"strServerIP="<<strServerIP
		<<" "<<"nServerPort="<<nServerPort;

	m_strServerIP = strServerIP;
	m_nServerPort = nServerPort;

	MYLOG4CPP_DEBUG<<"set server info"
		<<" "<<"m_strServerIP="<<m_strServerIP
		<<" "<<"m_nServerPort="<<m_nServerPort;

}


//QT_END_NAMESPACE

