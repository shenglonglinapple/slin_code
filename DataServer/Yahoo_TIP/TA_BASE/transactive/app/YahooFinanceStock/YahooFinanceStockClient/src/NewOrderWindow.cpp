#include "NewOrderWindow.h"

#include <QtGui/QCalendarWidget>
#include <QtGui/QDateTimeEdit>

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"

#include "SignalSlotManager.h"
#include "ClientDataManager.h"
#include "UserTradeInfo.h"
#include "NewOrderConfirmWindow.h"
#include "TcpComProtocol.h"
#include "QtTimeHelper.h"
#include "Log4cppLogger.h"

//QT_BEGIN_NAMESPACE
static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 500;

static const std::string DEFVALUE_String_Window_WindowTitle = "New Order";
static const std::string DEFVALUE_String_Label_Symbol_Text = "Symbol:";
static const std::string DEFVALUE_String_Label_OrderType_Text = "Order Type:";

static const std::string DEFVALUE_String_OrderType_MARKET = "MARKET";

CNewOrderWindow::CNewOrderWindow(QWidget *parent)
: QDialog(parent)
{
	m_pLabel_Symbol = NULL;
	m_pLineEdit_Symbol = NULL;
	m_pLabel_OrderType = NULL;
	m_pComboBox_OrderType = NULL;
	m_pLabel_Volume = NULL;
	m_pSpinBox_Volume = NULL;
	m_pLabel_Price = NULL;
	m_pSpinBox_Price = NULL;
	m_pPushButtonBuy = NULL;
	m_pPushButtonSell = NULL;
	m_pLabel_DateTime = NULL;
	m_pNewOrderConfirmWindow = NULL;
	m_pUserTradeInfo = NULL;
	m_pDateTimeEdit = NULL;
	m_pCalendarWidget = NULL;
	m_pQtTimeHelper = NULL;

	m_pTextEdit_Symbol_Value.clear();
	m_pComboBox_OrderType_Value.clear();
	m_pSpinBox_Volume_Value = 0;
	m_pSpinBox_Price_Value = 0;

	m_pQtTimeHelper = new CQtTimeHelper();

	_InitData();
	m_pUserTradeInfo = new CUserTradeInfo();

	this->_SetupUi();
	this->_TranslateLanguage();
	this->_CreateConnect();

}


CNewOrderWindow::~CNewOrderWindow()
{
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}

	if (NULL != m_pUserTradeInfo)
	{
		delete m_pUserTradeInfo;
		m_pUserTradeInfo = NULL;
	}
}

void CNewOrderWindow::_InitData()
{
	m_pTextEdit_Symbol_Value = "";
	m_pComboBox_OrderType_Value = DEFVALUE_String_OrderType_MARKET.c_str();
	m_pSpinBox_Volume_Value = 1;
	m_pSpinBox_Price_Value = 000000000.00000f;//(long double 99.9L)(double 99.9)//printf("%.7g\n", m_pSpinBox_Price_Value); 

}

void CNewOrderWindow::_SetupUi()
{
	int nSpacing = 10;
	int nMargin = 10;
	int nFromRow = 0;
	int nFromColumn = 0;
	int nRowSpan = 0;
	int nColumnSpan = 0;
	Qt::Alignment nAlignment;

	QSize qSizeLeftAreaOne(100, 20);
	QSize qSizeRightAreaOne(200, 20);	
	QSize qSizeCheckBoxOpenClose(80, 20);
	QSize qSizeButtonBuy(200, 20);
	QSize qSizeButtonSell(80, 20);

	m_pNewOrderConfirmWindow = new CNewOrderConfirmWindow(this);
	m_pNewOrderConfirmWindow->hide();

	//eg: Symbol: IF1401
	m_pLabel_Symbol = new QLabel(this);
	//m_pLabel_Symbol->setMinimumSize(qSizeLeftAreaOne);
	
	m_pLineEdit_Symbol = new QLineEdit(this);
	m_pLineEdit_Symbol->setReadOnly(true);
	//m_pLineEdit_Symbol->setMinimumSize(qSizeRightAreaOne);

	//eg: Order Type: Limit
	m_pLabel_OrderType = new QLabel(this);
	//m_pLabel_OrderType->setMinimumSize(qSizeLeftAreaOne);

	m_pComboBox_OrderType = new QComboBox(this);
	//m_pComboBox_OrderType->setMinimumSize(qSizeRightAreaOne);

	//Volume: 1
	m_pLabel_Volume = new QLabel(this);
	//m_pLabel_Volume->setMinimumSize(qSizeLeftAreaOne);

	m_pSpinBox_Volume = new QSpinBox(this);
	//m_pSpinBox_Volume->setMinimumSize(qSizeRightAreaOne);

	//eg: Price: 0.00
	m_pLabel_Price = new QLabel(this);
	//m_pLabel_Price->setMinimumSize(qSizeLeftAreaOne);

	m_pSpinBox_Price = new QDoubleSpinBox(this);
	//m_pSpinBox_Price->setMinimumSize(qSizeRightAreaOne);

	//Buy  Sell
	m_pPushButtonBuy = new QPushButton(this);
	//m_pPushButtonBuy->setMinimumSize(qSizeButtonBuy);

	m_pPushButtonSell = new QPushButton(this);
	//m_pPushButtonSell->setMinimumSize(qSizeButtonSell);

	m_pLabel_DateTime = new QLabel(this);
	m_pDateTimeEdit = new QDateTimeEdit(this);
	m_pDateTimeEdit->setMinimumDate(QDate::currentDate().addDays(-365));
	m_pDateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
	m_pDateTimeEdit->setDisplayFormat(DEFVALUE_String_DataTime_Format);
	m_pDateTimeEdit->setDateTime(QDateTime::currentDateTime());

	m_pCalendarWidget = new QCalendarWidget(this);
	m_pCalendarWidget->setGridVisible(true);
	m_pCalendarWidget->setMinimumDate(QDate::currentDate().addDays(-365));
	m_pCalendarWidget->setMaximumDate(QDate::currentDate().addDays(365));
	m_pCalendarWidget->setSelectedDate(QDate::currentDate());


	int nRowIndex = 0;
	m_pGridLayout = new QGridLayout(this);
	m_pGridLayout->addWidget(m_pLabel_Symbol, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLineEdit_Symbol, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pLabel_OrderType, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pComboBox_OrderType, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pLabel_Volume, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pSpinBox_Volume, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pLabel_Price, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pSpinBox_Price, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pPushButtonBuy, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pPushButtonSell, nRowIndex, 2, 1, 1);
	nRowIndex++;	
	m_pGridLayout->addWidget(m_pLabel_DateTime, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pDateTimeEdit, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pCalendarWidget, nRowIndex, 0, 3, 3);

	this->setLayout(m_pGridLayout);

	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	
	QMetaObject::connectSlotsByName(this);
}


void CNewOrderWindow::_TranslateLanguage()
{
	int nIndex = 0;

	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_WindowTitle.c_str()));
	m_pLabel_Symbol->setText(DEFVALUE_String_Label_Symbol_Text.c_str());
	m_pLineEdit_Symbol->setText(m_pTextEdit_Symbol_Value);
	nIndex = 0;

	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_OrderType_MARKET.c_str());

	m_pLabel_OrderType->setText(DEFVALUE_String_Label_OrderType_Text.c_str());

	m_pLabel_Volume->setText(QObject::tr("Volume:"));
	m_pSpinBox_Volume->setValue(m_pSpinBox_Volume_Value);

	m_pLabel_Price->setText(QObject::tr("Price:"));
	m_pSpinBox_Price->setValue(m_pSpinBox_Price_Value);
	m_pSpinBox_Price->setRange(0, 100000000);

	m_pLabel_DateTime->setText(QObject::tr("DataTime:"));

	m_pPushButtonBuy->setText("Buy");
	m_pPushButtonSell->setText("Sell");




}

void CNewOrderWindow::resetData(const QString& strSymbolUse, const QString& strTimeFrom, const QString& strTimeTo)
{
	QDateTime dateTimeFrom;
	QDateTime dateTimeTo;

	dateTimeFrom = m_pQtTimeHelper->getDateTimeValue(strTimeFrom);
	dateTimeTo = m_pQtTimeHelper->getDateTimeValue(strTimeTo);

	_InitData();

	m_pUserTradeInfo->clear();

	m_pTextEdit_Symbol_Value = strSymbolUse;
	m_pSpinBox_Volume_Value = 1;
	//m_pSpinBox_Price_Value;

	m_pDateTimeEdit->setMinimumDateTime(dateTimeFrom);
	m_pDateTimeEdit->setMaximumDateTime(dateTimeTo);
	m_pDateTimeEdit->setDisplayFormat(DEFVALUE_String_DataTime_Format);
	m_pDateTimeEdit->setDateTime(dateTimeTo);//QDateTime::currentDateTime()

	m_pCalendarWidget->setMinimumDate(dateTimeFrom.date());
	m_pCalendarWidget->setMaximumDate(dateTimeTo.date());
	m_pCalendarWidget->setSelectedDate(dateTimeTo.date());//QDate::currentDate()

	this->_TranslateLanguage();
}


void CNewOrderWindow::slotPushButtonBuyClicked( bool checked )
{
	int nCurrentIndex = 0;
	QString strOrderType;
	QDateTime nTradeDateTime;

	nCurrentIndex = m_pComboBox_OrderType->currentIndex();
	strOrderType = m_pComboBox_OrderType->itemText(nCurrentIndex);

	m_pUserTradeInfo->m_strUseID.clear();
	m_pUserTradeInfo->m_strTradeUUID = CTcpComProtocol::getUUID();
	m_pUserTradeInfo->m_strSymbolUse = m_pTextEdit_Symbol_Value;
	m_pUserTradeInfo->m_nTradeType = CTcpComProtocol::DataType_Buy;
	m_pUserTradeInfo->m_fTradePrice = m_pSpinBox_Price->value();
	m_pUserTradeInfo->m_fTradeAmount = m_pSpinBox_Volume->value();
	m_pUserTradeInfo->m_nTradeVolume = m_pSpinBox_Volume_Value;
	m_pUserTradeInfo->m_fTradeFees = 0.07;
	m_pUserTradeInfo->m_fTradeAmount = m_pUserTradeInfo->m_fTradePrice * m_pUserTradeInfo->m_nTradeVolume;
	m_pUserTradeInfo->m_fTotalTradeFee = m_pUserTradeInfo->m_fTradeAmount * m_pUserTradeInfo->m_fTradeFees;
	m_pUserTradeInfo->m_fTotalTradeAmount = m_pUserTradeInfo->m_fTradeAmount + m_pUserTradeInfo->m_fTotalTradeFee;
	nTradeDateTime = m_pDateTimeEdit->dateTime();
	m_pUserTradeInfo->m_strTradeTime = m_pQtTimeHelper->getStringValue(nTradeDateTime);

	//
	m_pNewOrderConfirmWindow->resetData(m_pUserTradeInfo);
	m_pNewOrderConfirmWindow->move(this->pos().x()+this->width()+10, this->pos().y());
	m_pNewOrderConfirmWindow->show();

}

void CNewOrderWindow::slotPushButtonSellClicked( bool checked )
{
	int nCurrentIndex = 0;
	QString strOrderType;

	nCurrentIndex = m_pComboBox_OrderType->currentIndex();
	strOrderType = m_pComboBox_OrderType->itemText(nCurrentIndex);


	//
	m_pNewOrderConfirmWindow->resetData(m_pUserTradeInfo);
	m_pNewOrderConfirmWindow->move(this->pos().x()+this->width()+10, this->pos().y());
	m_pNewOrderConfirmWindow->show();


}


void CNewOrderWindow::slotCalendarWidgetClicked( const QDate & date )
{
	m_pDateTimeEdit->setDate(date)
}


void CNewOrderWindow::_CreateConnect()
{	
	QObject::connect(m_pCalendarWidget, SIGNAL(clicked(const QDate &)), this, SLOT(slotCalendarWidgetClicked(const QDate &)));

	QObject::connect(m_pPushButtonBuy, SIGNAL(clicked(bool)), this, SLOT(slotPushButtonBuyClicked(bool)));

	QObject::connect(m_pPushButtonSell, SIGNAL(clicked(bool)), this, SLOT(slotPushButtonSellClicked(bool)));

	QObject::connect(m_pNewOrderConfirmWindow, 	SIGNAL(signalConfirmOrder(qint32)),	this, SLOT(slotConfirmOrder(qint32)));

	
}

void CNewOrderWindow::slotConfirmOrder(qint32 nEOrderConfirm)
{
	m_pNewOrderConfirmWindow->hide();

	if (NULL == m_pUserTradeInfo)
	{
		return;
	}

	//emit
	if (0 == nEOrderConfirm)
	{
		//CClientDataManager::getInstance().re.req_newOrder(*m_pOrderData);
	}
	else// if (-1 ==  nEOrderConfirm)
	{
		MYLOG4CPP_DEBUG<<" "<<"user Cancel new order";
	}
}


//QT_END_NAMESPACE

