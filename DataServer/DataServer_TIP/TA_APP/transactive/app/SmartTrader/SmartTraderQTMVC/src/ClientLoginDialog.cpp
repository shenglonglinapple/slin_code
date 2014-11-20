#include "ClientLoginDialog.h"

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"

#include "ClientLoginParam.h"
#include "ServerSettingDialog.h"
#include "PwdLineEdit.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE

static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 300;

static const std::string DEFVALUE_String_Window_Title_Text = "SmartTrader";


static const std::string DEFVALUE_String_Label_UserName_Text = "User Name:";
static const std::string DEFVALUE_String_Label_Password_Text = "Password:";
static const std::string DEFVALUE_String_Button_Settings_Text = "Settings";
static const std::string DEFVALUE_String_Button_Login_Text = "Login";
static const std::string DEFVALUE_String_Button_Cancel_Text = "Cancel";
	
static const  std::string DEF_VALUE_MainWidgetWindowIcon = ":/images/MainWidgetWindowIcon";//任务栏中的图标


CClientLoginDialog::CClientLoginDialog(QWidget *parent)
: QDialog(parent)
{
	m_pLabel_UserName  = NULL;
	m_pComboBox_UserName  = NULL;

	m_pLabel_Password  = NULL;
	m_pLineEdit_Password  = NULL;

	m_pPushButtonSetting  = NULL;
	m_pPushButtonLogin  = NULL;
	m_pPushButtonCancle  = NULL;

	m_pClientLoginParam = NULL;
	m_pServerSettingDialog = NULL;

	m_pComboBox_UserName_Value.clear();
	m_pLineEdit_Password_Value.clear();


	m_pClientLoginParam = new CClientLoginParam();
	m_pServerSettingDialog = new CServerSettingDialog(this);

	setupUi();
	translateLanguage();
	_CreateConnect();
}


CClientLoginDialog::~CClientLoginDialog()
{
	if (NULL != m_pClientLoginParam)
	{
		delete m_pClientLoginParam;
		m_pClientLoginParam = NULL;
	}
}

void CClientLoginDialog::_CreateConnect()
{
	QObject::connect(m_pServerSettingDialog, 
		SIGNAL(signalServerInfoChanged(CClientLoginParam*)),
		this, 
		SLOT(slotServerInfoChanged(CClientLoginParam*)));

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


void CClientLoginDialog::setupUi()
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

	this->setWindowIcon(QIcon(QObject::tr(DEF_VALUE_MainWidgetWindowIcon.c_str())));//任务栏中的图标
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);


	QMetaObject::connectSlotsByName(this);
}



void CClientLoginDialog::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title_Text.c_str()));

	m_pLabel_UserName->setText(QObject::tr(DEFVALUE_String_Label_UserName_Text.c_str()));
	m_pComboBox_UserName->insertItem(0, QObject::tr(DEFVALUE_String_UserName.c_str()));
	m_pComboBox_UserName->setCurrentIndex(0);
	m_pLabel_Password->setText(QObject::tr(DEFVALUE_String_Label_Password_Text.c_str()));
	m_pLineEdit_Password->setText(QObject::tr(DEFVALUE_String_PassWord.c_str()));
	m_pPushButtonSetting->setText(QObject::tr(DEFVALUE_String_Button_Settings_Text.c_str()));
	m_pPushButtonLogin->setText(QObject::tr(DEFVALUE_String_Button_Login_Text.c_str()));
	m_pPushButtonCancle->setText(QObject::tr(DEFVALUE_String_Button_Cancel_Text.c_str()));

}


void CClientLoginDialog::slotButtonSettingClicked( bool checked )
{
	m_pServerSettingDialog->show();
}

void CClientLoginDialog::slotButtonLoginClicked( bool checked )
{
	m_pComboBox_UserName_Value = m_pComboBox_UserName->currentText();
	m_pLineEdit_Password_Value = m_pLineEdit_Password->text();

	m_pClientLoginParam->m_strUserName = m_pComboBox_UserName_Value.toStdString();
	m_pClientLoginParam->m_strPassWord = m_pLineEdit_Password_Value.toStdString();

	MYLOG4CPP_DEBUG<<"set client info"
		<<" "<<"m_strUserName="<<m_pClientLoginParam->m_strUserName
		<<" "<<"m_strPassWord="<<m_pClientLoginParam->m_strPassWord;

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientLoginDialog"
		<<" "<<"fun:"<<"slotButtonLoginClicked()"
		<<" "<<"emit"
		<<" "<<"signalClientLoginParamChanged(CClientLoginParam* )"
		<<" "<<"param:"
		<<" "<<"m_pClientLoginParam=0x"<<m_pClientLoginParam;

	CSignalSlotManager::getInstance().emit_signalClientLoginParamChanged(m_pClientLoginParam);
}

void CClientLoginDialog::slotButtonCancelClicked( bool checked )
{
	this->close();

}

void CClientLoginDialog::slotLoginToServerResult( int nLoginResust )
{
	MYLOG4CPP_DEBUG<<"CClientLoginDialog process signalLoginToServerResult"
		<<" "<<"nLoginResust="<<nLoginResust;

	//logon ok
	if (nLoginResust >= 0)
	{
		this->setVisible(false);
		this->close();
	}
	else
	{
		QMessageBox::about(this, "login to server Error!", "login to server Error!");
	}
}

void CClientLoginDialog::slotServerInfoChanged( CClientLoginParam* pClientLoginParam )
{
	MYLOG4CPP_DEBUG<<"CClientLoginDialog process slotServerInfoChanged"
		<<" "<<"pClientLoginParam=0x"<<pClientLoginParam;

	m_pClientLoginParam->m_strServerIP = pClientLoginParam->m_strServerIP;
	m_pClientLoginParam->m_nServerPort = pClientLoginParam->m_nServerPort;

	MYLOG4CPP_DEBUG<<"set server info"
		<<" "<<"m_strServerIP="<<m_pClientLoginParam->m_strServerIP
		<<" "<<"m_nServerPort="<<m_pClientLoginParam->m_nServerPort;

}


//QT_END_NAMESPACE

