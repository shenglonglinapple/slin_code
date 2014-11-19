#include "CustomColumnsDialog.h"


#include "ProjectQTInclude.h"

#include "ConfigInfo.h"


#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE

static const int DEFVALUE_INT_Window_Width = 800;
static const int DEFVALUE_INT_Window_Height = 500;

static const std::string DEFAULT_STRING_VALUE_STRING_SPLIT = ",";


static const std::string DEFVALUE_String_Window_CustomColumnsDialog_Title = "Column Configuration Dialog";//列配置窗口

static const std::string DEFVALUE_String_Group_ColumnConfiguation_Title = "Column Configuration";//可选列
static const std::string DEFVALUE_String_Label_AllAvailableColums = "[All Aaailable Columns]";//自定义列配置

static const std::string DEFVALUE_String_Label_SelectedColumns = "[Selected Columns]";//已选列

static const std::string DEFVALUE_String_Button_Add = "Add";//添加
static const std::string DEFVALUE_String_Button_AddAll = "Add All";//添加所有
static const std::string DEFVALUE_String_Button_Remove = "Remove";//移除
static const std::string DEFVALUE_String_Button_RemoveAll = "Remove All";//移除所有
static const std::string DEFVALUE_String_Button_Default = "Default";//恢复默认
static const std::string DEFVALUE_String_Button_Up = "Up";//上移
static const std::string DEFVALUE_String_Button_Down = "Down";//下移
static const std::string DEFVALUE_String_Button_OK = "OK";//保存
static const std::string DEFVALUE_String_Button_Cancel = "Cancel";//取消



CCustomColumnsDialog::CCustomColumnsDialog(QWidget *parent)
: QDialog(parent)
{
	m_pLayout_Main = NULL;
	m_pGroupBox_ColumnConfiguation = NULL;
	m_pLabel_AllAvailableColums = NULL;
	m_pListWidget_AllAvailableColums = NULL;
	m_pLabel_SelectedColumns = NULL;
	m_pListWidget_SelectedColumns = NULL;
	m_pPushButton_OK = NULL;//保存
	m_pPushButton_Cancel = NULL;//取消

	setupUi();
	translateLanguage();


	{
		//set user config file value
		QStringList strlstData;
		strlstData.clear();
		strlstData = CConfigInfo::getInstance().getLstAllAvailableColums();
		_SetAllDataToListWidget(m_pListWidget_AllAvailableColums, strlstData);
		strlstData.clear();
		strlstData = CConfigInfo::getInstance().getLstSelectedColumns();
		_SetAllDataToListWidget(m_pListWidget_SelectedColumns, strlstData);
	}

	_CreateConnect();
}


CCustomColumnsDialog::~CCustomColumnsDialog()
{

}



void CCustomColumnsDialog::setupUi()
{
	QHBoxLayout* pHBoxLayout_Ok_Cancel = NULL;
	QHBoxLayout* pHBoxLayout_GroupBox_ColumnConfiguation = NULL;
	QVBoxLayout* pVBoxLayout_GroupBox_ColumnConfiguation_Left = NULL;
	QVBoxLayout* pVBoxLayout_GroupBox_ColumnConfiguation_Mid = NULL;
	QVBoxLayout* pVBoxLayout_GroupBox_ColumnConfiguation_Right = NULL;


	//main
	m_pGroupBox_ColumnConfiguation = new QGroupBox(this);
	m_pPushButton_OK = new QPushButton(this);//保存
	m_pPushButton_Cancel = new QPushButton(this);//取消
	//left
	m_pLabel_AllAvailableColums = new QLabel(m_pGroupBox_ColumnConfiguation);//"[All Aaailable Columns]";//自定义列配置
	m_pListWidget_AllAvailableColums = new QListWidget(m_pGroupBox_ColumnConfiguation);
	//mid
	m_pPushButton_Add = new QPushButton(this);
	m_pPushButton_AddAll = new QPushButton(this);
	m_pPushButton_Remove = new QPushButton(this);
	m_pPushButton_RemoveAll = new QPushButton(this);
	m_pPushButton_Default = new QPushButton(this);
	m_pPushButton_Up = new QPushButton(this);
	m_pPushButton_Down = new QPushButton(this);
	//right
	m_pLabel_SelectedColumns = new QLabel(m_pGroupBox_ColumnConfiguation);//"[Selected Columns]";//已选列
	m_pListWidget_SelectedColumns = new QListWidget(m_pGroupBox_ColumnConfiguation);


	//main
	m_pLayout_Main = new QVBoxLayout(NULL);
	pHBoxLayout_Ok_Cancel = new QHBoxLayout(NULL);
	//Column Configuration
	pHBoxLayout_GroupBox_ColumnConfiguation = new QHBoxLayout(m_pGroupBox_ColumnConfiguation);
	pVBoxLayout_GroupBox_ColumnConfiguation_Left = new QVBoxLayout(m_pGroupBox_ColumnConfiguation);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid = new QVBoxLayout(m_pGroupBox_ColumnConfiguation);
	pVBoxLayout_GroupBox_ColumnConfiguation_Right = new QVBoxLayout(m_pGroupBox_ColumnConfiguation);
	pHBoxLayout_GroupBox_ColumnConfiguation->addLayout(pVBoxLayout_GroupBox_ColumnConfiguation_Left);
	pHBoxLayout_GroupBox_ColumnConfiguation->addLayout(pVBoxLayout_GroupBox_ColumnConfiguation_Mid);
	pHBoxLayout_GroupBox_ColumnConfiguation->addLayout(pVBoxLayout_GroupBox_ColumnConfiguation_Right);

	//left
	pVBoxLayout_GroupBox_ColumnConfiguation_Left->addWidget(m_pLabel_AllAvailableColums);
	pVBoxLayout_GroupBox_ColumnConfiguation_Left->addWidget(m_pListWidget_AllAvailableColums);
	//mid
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addStretch(1);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addWidget(m_pPushButton_Add);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addWidget(m_pPushButton_AddAll);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addStretch(1);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addWidget(m_pPushButton_Remove);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addWidget(m_pPushButton_RemoveAll);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addStretch(1);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addWidget(m_pPushButton_Default);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addStretch(2);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addWidget(m_pPushButton_Up);
	pVBoxLayout_GroupBox_ColumnConfiguation_Mid->addWidget(m_pPushButton_Down);
	//right
	pVBoxLayout_GroupBox_ColumnConfiguation_Right->addWidget(m_pLabel_SelectedColumns);
	pVBoxLayout_GroupBox_ColumnConfiguation_Right->addWidget(m_pListWidget_SelectedColumns);


	m_pGroupBox_ColumnConfiguation->setLayout(pHBoxLayout_GroupBox_ColumnConfiguation);

	pHBoxLayout_Ok_Cancel->addStretch(3);
	pHBoxLayout_Ok_Cancel->addWidget(m_pPushButton_OK);
	pHBoxLayout_Ok_Cancel->addWidget(m_pPushButton_Cancel);

	m_pLayout_Main->addWidget(m_pGroupBox_ColumnConfiguation);
	m_pLayout_Main->addLayout(pHBoxLayout_Ok_Cancel);
	//m_pLayout_Main->addSpacing(2);
	//m_pLayout_Main->addStretch(1);

	this->setLayout(m_pLayout_Main);
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);



	QMetaObject::connectSlotsByName(this);
}



void CCustomColumnsDialog::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_CustomColumnsDialog_Title.c_str()));//"Column Configuration Dialog";//列配置窗口
	m_pGroupBox_ColumnConfiguation->setTitle(QObject::tr(DEFVALUE_String_Group_ColumnConfiguation_Title.c_str()));//"Column Configuration";//可选列
	m_pPushButton_OK->setText(QObject::tr(DEFVALUE_String_Button_OK.c_str()));//"OK";//保存
	m_pPushButton_Cancel->setText(QObject::tr(DEFVALUE_String_Button_Cancel.c_str()));//"Cancel";//取消

	m_pLabel_AllAvailableColums->setText(QObject::tr(DEFVALUE_String_Label_AllAvailableColums.c_str()));

	m_pPushButton_Add->setText(QObject::tr(DEFVALUE_String_Button_Add.c_str()));//"Add";//添加
	m_pPushButton_AddAll->setText(QObject::tr(DEFVALUE_String_Button_AddAll.c_str()));//"Add All";//添加所有
	m_pPushButton_Remove->setText(QObject::tr(DEFVALUE_String_Button_Remove.c_str()));//"Remove";//移除
	m_pPushButton_RemoveAll->setText(QObject::tr(DEFVALUE_String_Button_RemoveAll.c_str()));//"Remove All";//移除所有
	m_pPushButton_Default->setText(QObject::tr(DEFVALUE_String_Button_Default.c_str()));//"Default";//恢复默认
	m_pPushButton_Up->setText(QObject::tr(DEFVALUE_String_Button_Up.c_str()));//"Up";//上移
	m_pPushButton_Down->setText(QObject::tr(DEFVALUE_String_Button_Down.c_str()));//"Down";//下移

	m_pLabel_SelectedColumns->setText(QObject::tr(DEFVALUE_String_Label_SelectedColumns.c_str()));//"[Selected Columns]";//已选列



}

void CCustomColumnsDialog::_SetAllDataToListWidget(QListWidget* pListWidget, QStringList& strlstData)
{
	//CTreeItemQuotes::getLstClumnName(QStringList& strlstClumnName )
	if (NULL != pListWidget)
	{
		pListWidget->clear();
		pListWidget->addItems(strlstData);
		pListWidget->setCurrentRow(0);
	}

}

void CCustomColumnsDialog::_CreateConnect()
{
	//clicked(bool checked = false)
	QObject::connect(m_pPushButton_Remove, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonRemoveClick(bool)));

	QObject::connect(m_pPushButton_RemoveAll, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonRemoveAllClick(bool)));

	QObject::connect(m_pPushButton_Add, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonAddClick(bool)));

	QObject::connect(m_pPushButton_AddAll, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonAddAllClick(bool)));

	QObject::connect(m_pPushButton_Up, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonUpClick(bool)));

	QObject::connect(m_pPushButton_Down, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonDownClick(bool)));

	QObject::connect(m_pPushButton_OK, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonOKClick(bool)));

	QObject::connect(m_pPushButton_Cancel, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonCancelClick(bool)));

	QObject::connect(m_pPushButton_Default, SIGNAL(clicked(bool)),	this, SLOT(slotPushButtonDefaultClick(bool)));


}

void CCustomColumnsDialog::slotPushButtonRemoveClick(bool checked)
{
	if (NULL == m_pListWidget_SelectedColumns || m_pListWidget_SelectedColumns->count() < 1)
	{
		return;
	}

	QListWidgetItem* pCurrentItem = NULL;
	QString strCurrentItemText;
	int nRowValue = 0;
	int nRowValueForCurrentItem = 0;


	pCurrentItem = m_pListWidget_SelectedColumns->currentItem();
	if (NULL == pCurrentItem)
	{
		return;
	}

	strCurrentItemText = pCurrentItem->text();

	nRowValue = m_pListWidget_SelectedColumns->row(pCurrentItem);
	//remove
	m_pListWidget_SelectedColumns->takeItem(nRowValue);
	//check empty
	if (m_pListWidget_SelectedColumns->count() < 1)
	{
		nRowValueForCurrentItem = 0;
	}
	else if (nRowValue >= m_pListWidget_SelectedColumns->count())
	{
		nRowValueForCurrentItem = m_pListWidget_SelectedColumns->count() - 1;
	}
	else
	{
		nRowValueForCurrentItem = nRowValue;
	}

	m_pListWidget_SelectedColumns->setCurrentRow(nRowValueForCurrentItem);
	//add
	m_pListWidget_AllAvailableColums->addItem(strCurrentItemText);
	m_pListWidget_AllAvailableColums->setCurrentRow(m_pListWidget_AllAvailableColums->count() - 1);
}

void CCustomColumnsDialog::slotPushButtonRemoveAllClick( bool checked /*= false*/ )
{
	if (NULL == m_pListWidget_SelectedColumns || m_pListWidget_SelectedColumns->count() < 1)
	{
		return;
	}

	QListWidgetItem* pCurrentItem = NULL;
	QString strCurrentItemText;
	int nRowValue = 0;

	while (m_pListWidget_SelectedColumns->count() > 0)
	{
		m_pListWidget_SelectedColumns->setCurrentRow(0);
		pCurrentItem = m_pListWidget_SelectedColumns->currentItem();
		if (NULL == pCurrentItem)
		{
			return;
		}
		strCurrentItemText = pCurrentItem->text();
		nRowValue = m_pListWidget_SelectedColumns->row(pCurrentItem);
		//remove
		m_pListWidget_SelectedColumns->takeItem(nRowValue);
		m_pListWidget_SelectedColumns->setCurrentRow(nRowValue);

		//add
		m_pListWidget_AllAvailableColums->addItem(strCurrentItemText);
		m_pListWidget_AllAvailableColums->setCurrentRow(m_pListWidget_AllAvailableColums->count() - 1);

	}//while

}


void CCustomColumnsDialog::slotPushButtonAddClick(bool checked)
{
	if (NULL == m_pListWidget_AllAvailableColums || m_pListWidget_AllAvailableColums->count() < 1)
	{
		return;
	}

	QListWidgetItem* pCurrentItem = NULL;
	QString strCurrentItemText;
	int nRowValue = 0;

	pCurrentItem = m_pListWidget_AllAvailableColums->currentItem();
	if (NULL == pCurrentItem)
	{
		return;
	}

	strCurrentItemText = pCurrentItem->text();

	nRowValue = m_pListWidget_AllAvailableColums->row(pCurrentItem);
	//remove
	m_pListWidget_AllAvailableColums->takeItem(nRowValue);
	if (nRowValue > 0)
	{
		m_pListWidget_AllAvailableColums->setCurrentRow(nRowValue - 1);
	}

	//add
	m_pListWidget_SelectedColumns->addItem(strCurrentItemText);
	m_pListWidget_SelectedColumns->setCurrentRow(m_pListWidget_SelectedColumns->count() - 1);

}



void CCustomColumnsDialog::slotPushButtonAddAllClick( bool checked /*= false*/ )
{
	if (NULL == m_pListWidget_AllAvailableColums || m_pListWidget_AllAvailableColums->count() < 1)
	{
		return;
	}

	QListWidgetItem* pCurrentItem = NULL;
	QString strCurrentItemText;
	int nRowValue = 0;

	while (m_pListWidget_AllAvailableColums->count() > 0)
	{
		m_pListWidget_AllAvailableColums->setCurrentRow(0);
		pCurrentItem = m_pListWidget_AllAvailableColums->currentItem();
		if (NULL == pCurrentItem)
		{
			return;
		}
		strCurrentItemText = pCurrentItem->text();
		nRowValue = m_pListWidget_AllAvailableColums->row(pCurrentItem);
		//remove
		m_pListWidget_AllAvailableColums->takeItem(nRowValue);
		if (nRowValue > 0)
		{
			m_pListWidget_AllAvailableColums->setCurrentRow(nRowValue - 1);
		}

		//add
		m_pListWidget_SelectedColumns->addItem(strCurrentItemText);
		m_pListWidget_SelectedColumns->setCurrentRow(m_pListWidget_SelectedColumns->count() - 1);
	}//while

}


void CCustomColumnsDialog::slotPushButtonUpClick(bool checked)
{
	if (NULL == m_pListWidget_SelectedColumns || m_pListWidget_SelectedColumns->count() < 1)
	{
		return;
	}

	QListWidgetItem* pCurrentItem = NULL;
	QString strCurrentItemText;
	int nRowValue = 0;

	pCurrentItem = m_pListWidget_SelectedColumns->currentItem();
	if (NULL == pCurrentItem)
	{
		return;
	}

	strCurrentItemText = pCurrentItem->text();

	nRowValue = m_pListWidget_SelectedColumns->row(pCurrentItem);

	//check if current item is first item
	if (0 == nRowValue)
	{
		return;
	}

	//remove
	m_pListWidget_SelectedColumns->takeItem(nRowValue);
	//insert
	m_pListWidget_SelectedColumns->insertItem(nRowValue - 1, strCurrentItemText);	
	m_pListWidget_SelectedColumns->setCurrentRow(nRowValue - 1);

}


void CCustomColumnsDialog::slotPushButtonDownClick(bool checked)
{
	if (NULL == m_pListWidget_SelectedColumns || m_pListWidget_SelectedColumns->count() < 1)
	{
		return;
	}

	QListWidgetItem* pCurrentItem = NULL;
	QString strCurrentItemText;
	int nRowValue = 0;
	int nLastRowValue = 0;

	nLastRowValue = m_pListWidget_SelectedColumns->count() - 1;

	pCurrentItem = m_pListWidget_SelectedColumns->currentItem();
	if (NULL == pCurrentItem)
	{
		return;
	}

	strCurrentItemText = pCurrentItem->text();

	nRowValue = m_pListWidget_SelectedColumns->row(pCurrentItem);

	//check if current item is Last item
	if (nLastRowValue == nRowValue)
	{
		return;
	}

	//remove
	m_pListWidget_SelectedColumns->takeItem(nRowValue);
	//insert
	m_pListWidget_SelectedColumns->insertItem(nRowValue + 1, strCurrentItemText);	
	m_pListWidget_SelectedColumns->setCurrentRow(nRowValue + 1);

}

void CCustomColumnsDialog::slotPushButtonOKClick( bool checked /*= false*/ )
{
	QStringList strAllData_AllAvailableColums;
	QStringList strAllData_SelectedColumns;

	strAllData_AllAvailableColums = _GetAllDataFormListWidget(m_pListWidget_AllAvailableColums);
	strAllData_SelectedColumns = _GetAllDataFormListWidget(m_pListWidget_SelectedColumns);

	//write to config and refush memory data
	CConfigInfo::getInstance().setLstSelectedColumns(strAllData_SelectedColumns);
	CConfigInfo::getInstance().setLstAllAvailableColums(strAllData_AllAvailableColums);


	//emit
	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CCustomColumnsDialog"
			<<" "<<"fun:"<<"slotPushButtonOKClick()"
			<<" "<<"emit"
			<<" "<<"signalModifySelectedColumns(QStringList,QStringList)"
			<<" "<<"param:"
			<<" "<<"AllAvailableColums.count="<<strAllData_AllAvailableColums.count()
			<<" "<<"SelectedColumns.count="<<strAllData_SelectedColumns.count();

		emit signalModifySelectedColumns(strAllData_AllAvailableColums, strAllData_SelectedColumns);
	}
	
	this->setVisible(false);

}

void CCustomColumnsDialog::slotPushButtonCancelClick( bool checked /*= false*/ )
{
	this->setVisible(false);
}

QStringList CCustomColumnsDialog::_GetAllDataFormListWidget(QListWidget* pListWidget)
{
	QStringList strAllData;
	strAllData.clear();
	if (NULL == pListWidget || pListWidget->count() < 1)
	{
		return strAllData;
	}

	QListWidgetItem* pCurrentItem = NULL;
	QString strCurrentItemText;
	int nIndex = 0;
	QListWidgetItem* pCurrentItemOldValue = NULL;
	int nRowValueOldValue = 0;


	pCurrentItemOldValue = pListWidget->currentItem();
	if (NULL != pCurrentItemOldValue)
	{
		nRowValueOldValue = pListWidget->row(pCurrentItemOldValue);
	}


	for (nIndex = 0; nIndex < pListWidget->count(); nIndex++)
	{
		pListWidget->setCurrentRow(nIndex);
		pCurrentItem = pListWidget->currentItem();
		if (NULL == pCurrentItem)
		{
			return strAllData;
		}
		strCurrentItemText = pCurrentItem->text();

		strAllData.push_back(strCurrentItemText);
	}//while

	pListWidget->setCurrentRow(nRowValueOldValue);

	return strAllData;
}

void CCustomColumnsDialog::slotPushButtonDefaultClick( bool checked /*= false*/ )
{
	//set user config file value
	QStringList strlstData;
	strlstData.clear();
	strlstData = CConfigInfo::getInstance().getLstAllAvailableColumsDefault();
	_SetAllDataToListWidget(m_pListWidget_AllAvailableColums, strlstData);
	strlstData.clear();
	strlstData = CConfigInfo::getInstance().getLstSelectedColumnsDefault();
	_SetAllDataToListWidget(m_pListWidget_SelectedColumns, strlstData);

}


//QT_END_NAMESPACE

