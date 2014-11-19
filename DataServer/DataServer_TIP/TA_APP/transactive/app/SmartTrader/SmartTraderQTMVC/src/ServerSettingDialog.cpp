#include "ServerSettingDialog.h"

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"

#include "ClientLoginParam.h"


#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE

static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 300;

static const std::string DEFVALUE_String_Window_Title_Text = "Server Setting";

static const std::string DEFVALUE_String_Label_IPAddress_Text = "IP Address:";
static const std::string DEFVALUE_String_Label_Port_Text = "Port:";
static const std::string DEFVALUE_String_PushButton_OK_Text = "OK";
static const std::string DEFVALUE_String_PushButton_Cancel_Text = "Cancel";

	


CServerSettingDialog::CServerSettingDialog(QWidget *parent)
: QDialog(parent)
{
	m_pLabel_IPAddress = NULL;
	m_pLineEdit_IPAddress = NULL;
	m_pLabel_Port = NULL;
	m_pLineEdit_Port = NULL;
	m_pPushButton_OK = NULL;
	m_pPushButton_Cancel = NULL;

	m_pClientLoginParam = NULL;
	m_str_LineEdit_IPAddress_Value.clear();
	m_str_LineEdit_Port_Value.clear();

	m_pClientLoginParam = new CClientLoginParam();

	setupUi();
	translateLanguage();
	_CreateConnect();
}


CServerSettingDialog::~CServerSettingDialog()
{
	if (NULL != m_pClientLoginParam)
	{
		delete m_pClientLoginParam;
		m_pClientLoginParam = NULL;
	}
}

void CServerSettingDialog::_CreateConnect()
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


void CServerSettingDialog::setupUi()
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


void CServerSettingDialog::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title_Text.c_str()));

	m_pLabel_IPAddress->setText(QObject::tr(DEFVALUE_String_Label_IPAddress_Text.c_str()));
	m_pLineEdit_IPAddress->setText(QObject::tr(DEFVALUE_String_ServerIP.c_str()));
	m_pLabel_Port->setText(QObject::tr(DEFVALUE_String_Label_Port_Text.c_str()));
	m_pLineEdit_Port->setText(QString("%1").arg(DEFVALUE_Int_ServerPort));
	m_pPushButton_OK->setText(QObject::tr(DEFVALUE_String_PushButton_OK_Text.c_str()));
	m_pPushButton_Cancel->setText(QObject::tr(DEFVALUE_String_PushButton_Cancel_Text.c_str()));

}





void CServerSettingDialog::slotButtonOKlicked( bool checked )
{
	m_str_LineEdit_IPAddress_Value = m_pLineEdit_IPAddress->text();
	m_str_LineEdit_Port_Value = m_pLineEdit_Port->text();

	m_pClientLoginParam->m_strServerIP = m_str_LineEdit_IPAddress_Value.toStdString();
	m_pClientLoginParam->m_nServerPort = m_str_LineEdit_Port_Value.toInt();

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CServerSettingDialog"
		<<" "<<"fun:"<<"slotButtonOKlicked()"
		<<" "<<"emit"
		<<" "<<"signalServerInfoChanged(CClientLoginParam* )"
		<<" "<<"param:"
		<<" "<<"m_pClientLoginParam=0x"<<m_pClientLoginParam;

	emit signalServerInfoChanged(m_pClientLoginParam);

	this->setVisible(false);
	this->close();
}

void CServerSettingDialog::slotButtonCancellicked( bool checked )
{
	this->setVisible(false);
	this->close();
}


//QT_END_NAMESPACE

