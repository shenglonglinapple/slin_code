#include "ServerSettingDialog.h"

#include <QtGui>
#include <QtGui/QMessageBox>
#include <QtGui/QMenu> 
#include <QtGui/QCursor> 
#include <QtCore/QSize>

#include "ProcessorWorker.h"
#include "QTProjectEnvironment.h"
#include "ConfigInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


QT_BEGIN_NAMESPACE



//////////////////////////////////////////////////////////////////////////
static const std::string DEF_PARAM_VALUE_HisDataDirectory_default = "D:\\HistData";
static const std::string DEF_PARAM_VALUE_SaveDataDirectoryBAR_default = "D:\\sllin_code\\DataServer\\SaveDataBAR";
static const std::string DEF_PARAM_VALUE_SaveDataDirectoryTIK_default = "D:\\sllin_code\\DataServer\\SaveDataTIK";
static const std::string DEF_PARAM_VALUE_DbType_default = "SQLITE";//MYSQL
static const std::string DEF_PARAM_VALUE_StartTime_default = "1980-01-01 09:00:01";//file time 1980-01-01 09:00:00
static const std::string DEF_PARAM_VALUE_AutoRun_default = "YES";//AutoRun=NO
static const std::string DEF_PARAM_VALUE_AutoRunTime_default = "2014-04-09 02:00:01";//2014-04-09 02::00:00 
//
// static const std::string DEF_PARAM_VALUE_HisDataDirectory_default = "E:\\HisData";
// static const std::string DEF_PARAM_VALUE_SaveDataDirectoryBAR_default = "E:\\LSL_Code\\slin_code\\DataServer\\SaveDataBAR";
// static const std::string DEF_PARAM_VALUE_SaveDataDirectoryTIK_default = "E:\\LSL_Code\\slin_code\\DataServer\\SaveDataTIK";
// static const std::string DEF_PARAM_VALUE_DbType_default = "SQLITE";//MYSQL
// static const std::string DEF_PARAM_VALUE_StartTime_default = "2013-02-29 09:00:01";//file time 1980-01-01 09:00:00
// static const std::string DEF_PARAM_VALUE_AutoRun_default = "YES";//AutoRun=NO
// static const std::string DEF_PARAM_VALUE_AutoRunTime_default = "2014-04-09 02:00:01";//2014-04-09 02::00:00 
//



static const std::string DEF_PARAM_VALUE_DbType_SQLITE = "SQLITE";//MYSQL
static const std::string DEF_PARAM_VALUE_DbType_MYSQL = "MYSQL";//MYSQL
static const std::string DEF_PARAM_VALUE_AutoRun_YES = "YES";//
static const std::string DEF_PARAM_VALUE_AutoRun_NO = "NO";//
//////////////////////////////////////////////////////////////////////////
static const std::string DEF_PARAM_KEY_ConfigFileName = "CFGFile";//CFGFile=./cfg/cfdServerConfigfile.cfg
static const std::string DEF_PARAM_KEY_HisDataDirectory = "hisdata";
static const std::string DEF_PARAM_KEY_SaveDataDirectoryBAR = "savedatabar";
static const std::string DEF_PARAM_KEY_SaveDataDirectoryTIK = "savedatatik";
static const std::string DEF_PARAM_KEY_DbType = "dbtype";//dbtype=SQLITE
static const std::string DEF_PARAM_KEY_StartTime = "starttime";//dbtype=SQLITE
static const std::string DEF_PARAM_KEY_AutoRun = "AutoRun";//AutoRun=YES
static const std::string DEF_PARAM_KEY_AutoRunTime = "AutoRunTime";//02
//////////////////////////////////////////////////////////////////////////




CServerSettingDialog::CServerSettingDialog(QWidget *parent)
: QDialog(parent)
{
	this->setupUi(this);
	_CreateConnect();

	m_pProcessWorker = NULL;
	m_pProcessWorker = new CProcessorWorker();
}


CServerSettingDialog::~CServerSettingDialog()
{
	if (NULL != m_pProcessWorker)
	{
		LOG_INFO<<"m_pProcessWorker->terminateAndWait";

		m_pProcessWorker->terminateAndWait();
		delete m_pProcessWorker;
		m_pProcessWorker = NULL;
	}
}

void CServerSettingDialog::_CreateConnect()
{
	QObject::connect(m_pPushButton_Run, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotButtonRunClicked(bool)));

	QObject::connect(m_pPushButton_Cancel, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotButtonCancelClicked(bool)));


	QObject::connect(this, 
		SIGNAL(signalPrcessorDoWork()),
		this, 
		SLOT(slotPrcessorDoWork()));
}


void CServerSettingDialog::setupUi( QDialog* pDialog )
{
	int nDialogWidth = 800;
	int nDialogLength = 800;

	QSize qSizeLeftAreaOne(200, 20);
	QSize qSizeRightAreaOne(400, 20);

	int nSpacing = 10;
	int nMargin = 10;

	if (pDialog->objectName().isEmpty())
	{
		pDialog->setObjectName(QString::fromUtf8("ObjectName_CServerSettingDialog"));
	}
	pDialog->resize(nDialogWidth, nDialogLength);
	/*
	Qt::WindowFlags flags=Qt::Dialog;
	flags |=Qt::WindowMinimizeButtonHint;
	setWindowFlags(flags);
	*/
	pDialog->setWindowFlags(Qt::Widget);//

	//////////////////////////////////////////////////////////////////////////
	m_pFormLayout = new QFormLayout(pDialog);
	m_pFormLayout->setObjectName(QString::fromUtf8("ObjectName_CServerSettingDialog_FormLayout"));
	m_pFormLayout->setFormAlignment(Qt::AlignCenter);
	m_pFormLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_pFormLayout->setSizeConstraint(QLayout::SetFixedSize);
	m_pFormLayout->setHorizontalSpacing(20);
	m_pFormLayout->setVerticalSpacing(20);
	m_pFormLayout->setContentsMargins(10,30,10,20);
	m_pFormLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
	m_pFormLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

	m_pHBoxLayout_Buttons = new QHBoxLayout(pDialog);
	m_pHBoxLayout_Buttons->setObjectName(QString::fromUtf8("ObjectName_CServerSettingDialog_HBoxLayout_Buttons"));
	//////////////////////////////////////////////////////////////////////////
	//0
	m_pLabel_HisData = new QLabel(pDialog);
	m_pLabel_HisData->setObjectName(QString::fromUtf8("ObjectName_Label_HisData"));
	m_pLabel_HisData->setText(QString::fromUtf8(DEF_PARAM_KEY_HisDataDirectory.c_str()));

	m_pLineEdit_HisData = new QLineEdit(pDialog);
	m_pLineEdit_HisData->setObjectName(QString::fromUtf8("ObjectName_LineEdit_HisData"));
	m_pLineEdit_HisData->setMinimumSize(qSizeRightAreaOne);
	m_pLineEdit_HisData->setText(QString::fromUtf8(DEF_PARAM_VALUE_HisDataDirectory_default.c_str()));
	m_pFormLayout->addRow(m_pLabel_HisData, m_pLineEdit_HisData);

	//1
	m_pLabel_SaveDataBar = new QLabel(pDialog);
	m_pLabel_SaveDataBar->setObjectName(QString::fromUtf8("ObjectName_Label_SaveDataBar"));
	m_pLabel_SaveDataBar->setText(QString::fromUtf8(DEF_PARAM_KEY_SaveDataDirectoryBAR.c_str()));

	m_pLineEdit_SaveDataBar = new QLineEdit(pDialog);
	m_pLineEdit_SaveDataBar->setObjectName(QString::fromUtf8("ObjectName_LineEdit_SaveDataBar"));
	m_pLineEdit_SaveDataBar->setMinimumSize(qSizeRightAreaOne);
	m_pLineEdit_SaveDataBar->setText(QString::fromUtf8(DEF_PARAM_VALUE_SaveDataDirectoryBAR_default.c_str()));
	m_pFormLayout->addRow(m_pLabel_SaveDataBar, m_pLineEdit_SaveDataBar);

	//2
	m_pLabel_SaveDataTik = new QLabel(pDialog);
	m_pLabel_SaveDataTik->setObjectName(QString::fromUtf8("ObjectName_Label_SaveDataTik"));
	m_pLabel_SaveDataTik->setText(QString::fromUtf8(DEF_PARAM_KEY_SaveDataDirectoryTIK.c_str()));

	m_pLineEdit_SaveDataTik = new QLineEdit(pDialog);
	m_pLineEdit_SaveDataTik->setObjectName(QString::fromUtf8("ObjectName_LineEdit_SaveDataTik"));
	m_pLineEdit_SaveDataTik->setMinimumSize(qSizeRightAreaOne);
	m_pLineEdit_SaveDataTik->setText(QString::fromUtf8(DEF_PARAM_VALUE_SaveDataDirectoryTIK_default.c_str()));
	m_pFormLayout->addRow(m_pLabel_SaveDataTik, m_pLineEdit_SaveDataTik);

	//3
	m_pLabel_DBType = new QLabel(pDialog);
	m_pLabel_DBType->setObjectName(QString::fromUtf8("ObjectName_Label_DBType"));
	m_pLabel_DBType->setText(QString::fromUtf8(DEF_PARAM_KEY_DbType.c_str()));

	m_pComboBox_DBType = new QComboBox(pDialog);
	m_pComboBox_DBType->setObjectName(QString::fromUtf8("ObjectName_ComboBox_DBType"));
	m_pComboBox_DBType->setMinimumSize(qSizeRightAreaOne);
	m_pComboBox_DBType->insertItem(0, QString::fromUtf8(DEF_PARAM_VALUE_DbType_SQLITE.c_str()));
	m_pComboBox_DBType->insertItem(1, QString::fromUtf8(DEF_PARAM_VALUE_DbType_MYSQL.c_str()));
	m_pComboBox_DBType->setCurrentIndex(0);
	m_pFormLayout->addRow(m_pLabel_DBType, m_pComboBox_DBType);


	//4
	m_pLabel_StartTime = new QLabel(pDialog);
	m_pLabel_StartTime->setObjectName(QString::fromUtf8("ObjectName_Label_StartTime"));
	m_pLabel_StartTime->setText(QString::fromUtf8(DEF_PARAM_KEY_StartTime.c_str()));

	m_pLineEdit_StartTime = new QLineEdit(pDialog);
	m_pLineEdit_StartTime->setObjectName(QString::fromUtf8("ObjectName_LineEdit_SaveDataTik"));
	m_pLineEdit_StartTime->setMinimumSize(qSizeRightAreaOne);
	m_pLineEdit_StartTime->setText(QString::fromUtf8(DEF_PARAM_VALUE_StartTime_default.c_str()));
	m_pFormLayout->addRow(m_pLabel_StartTime, m_pLineEdit_StartTime);

	//5
	m_pLabel_AutoRun = new QLabel(pDialog);
	m_pLabel_AutoRun->setObjectName(QString::fromUtf8("ObjectName_Label_AutoRun"));
	m_pLabel_AutoRun->setText(QString::fromUtf8(DEF_PARAM_KEY_AutoRun.c_str()));

	m_pComboBox_AutoRun = new QComboBox(pDialog);
	m_pComboBox_AutoRun->setObjectName(QString::fromUtf8("ObjectName_ComboBox_AutoRun"));
	m_pComboBox_AutoRun->setMinimumSize(qSizeRightAreaOne);
	m_pComboBox_AutoRun->insertItem(0, QString::fromUtf8(DEF_PARAM_VALUE_AutoRun_YES.c_str()));
	m_pComboBox_AutoRun->insertItem(1, QString::fromUtf8(DEF_PARAM_VALUE_AutoRun_NO.c_str()));
	m_pComboBox_AutoRun->setCurrentIndex(0);
	m_pFormLayout->addRow(m_pLabel_AutoRun, m_pComboBox_AutoRun);

	//6
	m_pLabel_AutoRunTime = new QLabel(pDialog);
	m_pLabel_AutoRunTime->setObjectName(QString::fromUtf8("ObjectName_Label_AutoRunTime"));
	m_pLabel_AutoRunTime->setText(QString::fromUtf8(DEF_PARAM_KEY_AutoRunTime.c_str()));

	m_pLineEdit_AutoRunTime = new QLineEdit(pDialog);
	m_pLineEdit_AutoRunTime->setObjectName(QString::fromUtf8("ObjectName_LineEdit_SaveDataTik"));
	m_pLineEdit_AutoRunTime->setMinimumSize(qSizeRightAreaOne);
	m_pLineEdit_AutoRunTime->setText(QString::fromUtf8(DEF_PARAM_VALUE_AutoRunTime_default.c_str()));
	m_pFormLayout->addRow(m_pLabel_AutoRunTime, m_pLineEdit_AutoRunTime);


	//7
	m_pPushButton_Run = new QPushButton(pDialog);
	m_pPushButton_Run->setObjectName(QString::fromUtf8("ObjectName_PushButton_Run"));
	m_pPushButton_Run->setText(QString::fromUtf8("Run"));
	m_pPushButton_Run->setDefault(true);

	m_pPushButton_Cancel = new QPushButton(pDialog);
	m_pPushButton_Cancel->setObjectName(QString::fromUtf8("ObjectName_PushButton_Cancel"));
	m_pPushButton_Cancel->setText(QString::fromUtf8("Cancel"));
	m_pPushButton_Cancel->setDefault(false);

	m_pHBoxLayout_Buttons->addWidget(m_pPushButton_Run);
	m_pHBoxLayout_Buttons->addWidget(m_pPushButton_Cancel);

	m_pFormLayout->addRow(m_pHBoxLayout_Buttons);

	
	this->setLayout(m_pFormLayout);

	//////////////////////////////////////////////////////////////////////////

	retranslateUi(pDialog);

	QMetaObject::connectSlotsByName(pDialog);
}



void CServerSettingDialog::retranslateUi(QDialog* pDialog)
{
	pDialog->setWindowTitle(QApplication::translate("His Data Processor Setting", "His Data Processor Setting", 0, QApplication::UnicodeUTF8));

} // retranslateUi

void CServerSettingDialog::slotButtonRunClicked( bool checked )
{
	m_pPushButton_Run->setEnabled(false);
	m_pPushButton_Cancel->setEnabled(false);

	m_strValue_HistoryDataDirectory = m_pLineEdit_HisData->text().toStdString();
	m_strValue_SaveDataDirectoryBAR = m_pLineEdit_SaveDataBar->text().toStdString();
	m_strValue_SaveDataDirectoryTIK = m_pLineEdit_SaveDataTik->text().toStdString();
	m_strValue_DbType = m_pComboBox_DBType->currentText().toStdString();
	m_strValue_StartTime = m_pLineEdit_StartTime->text().toStdString();
	m_strValue_AutoRun = m_pComboBox_AutoRun->currentText().toStdString();
	m_strValue_AutoRunTime = m_pLineEdit_AutoRunTime->text().toStdString();


	LOG_INFO<<"CServerSettingDialog::slotButtonRunClicked"
		<<" "<<"m_strValue_HistoryDataDirectory="<<m_strValue_HistoryDataDirectory
		<<" "<<"m_strValue_SaveDataDirectoryBAR="<<m_strValue_SaveDataDirectoryBAR
		<<" "<<"m_strValue_SaveDataDirectoryTIK="<<m_strValue_SaveDataDirectoryTIK
		<<" "<<"m_strValue_DbType="<<m_strValue_DbType
		<<" "<<"m_strValue_StartTime="<<m_strValue_StartTime
		<<" "<<"m_strValue_AutoRun="<<m_strValue_AutoRun
		<<" "<<"m_strValue_AutoRunTime="<<m_strValue_AutoRunTime;



	CConfigInfo::getInstance().setHistoryDataDirectory(m_strValue_HistoryDataDirectory);
	CConfigInfo::getInstance().setSaveDataDirectoryBAR(m_strValue_SaveDataDirectoryBAR);
	CConfigInfo::getInstance().setSaveDataDirectoryTIK(m_strValue_SaveDataDirectoryTIK);
	CConfigInfo::getInstance().setDbType(m_strValue_DbType);
	CConfigInfo::getInstance().setStartTime(m_strValue_StartTime);
	CConfigInfo::getInstance().setAutoRun(m_strValue_AutoRun);
	CConfigInfo::getInstance().setAutoRunTime(m_strValue_AutoRunTime);
	CConfigInfo::getInstance().processorCfgValue();
	CConfigInfo::getInstance().logInfo();


	LOG_INFO<<"CServerSettingDialog::slotButtonRunClicked emit signalPrcessorDoWork";
	emit signalPrcessorDoWork();

}

void CServerSettingDialog::slotButtonCancelClicked( bool checked )
{
	this->setVisible(false);
	this->close();
}

void CServerSettingDialog::slotPrcessorDoWork()
{
	LOG_INFO<<"CServerSettingDialog::slotPrcessorDoWork process signalPrcessorDoWork";

	if (NULL == m_pProcessWorker)
	{
		m_pProcessWorker = new CProcessorWorker();
	}

	LOG_INFO<<"m_pProcessWorker->start()";

	m_pProcessWorker->start();

}



QT_END_NAMESPACE

