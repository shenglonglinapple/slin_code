#include "NewOrderWindow.h"

#include <QtGui/QtGui>
#include <QtGui/QCalendarWidget>
#include <QtGui/QDateTimeEdit>

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"

#include "SignalSlotManager.h"
#include "ClientDataManager.h"
#include "ClientDBManager.h"
#include "UserTradeInfo.h"
#include "HistoryData.h"
#include "NewOrderConfirmWindow.h"
#include "TcpComProtocol.h"
#include "QtTimeHelper.h"

#include "Log4cppLogger.h"

//QT_BEGIN_NAMESPACE
static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 400;

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
	//m_pCalendarWidget = NULL;
	m_pQtTimeHelper = NULL;

	m_strSymbolUse.clear();
	m_strOrderType.clear();
	m_nVolume = 0;
	m_fPrice = 0;

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
	m_strSymbolUse = "";
	m_strOrderType = DEFVALUE_String_OrderType_MARKET.c_str();
	m_nVolume = 100;
	m_fPrice = 000000000.00000f;//(long double 99.9L)(double 99.9)//printf("%.7g\n", m_pSpinBox_Price_Value); 

}

void CNewOrderWindow::_SetupUi()
{
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
	m_pSpinBox_Volume->setRange(0, 10000000);
	//m_pSpinBox_Volume->setMinimumSize(qSizeRightAreaOne);

	//eg: Price: 0.00
	m_pLabel_Price = new QLabel(this);
	//m_pLabel_Price->setMinimumSize(qSizeLeftAreaOne);

	m_pSpinBox_Price = new QDoubleSpinBox(this);
	m_pSpinBox_Price->setRange(0, 100000000);
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
	m_pDateTimeEdit->setDisplayFormat(DEFVALUE_String_Data_Format);
	m_pDateTimeEdit->setDate(QDate::currentDate());

// 	m_pCalendarWidget = new QCalendarWidget(this);
// 	m_pCalendarWidget->setGridVisible(true);
// 	m_pCalendarWidget->setMinimumDate(QDate::currentDate().addDays(-365));
// 	m_pCalendarWidget->setMaximumDate(QDate::currentDate().addDays(365));
// 	m_pCalendarWidget->setSelectedDate(QDate::currentDate());


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
	//m_pGridLayout->addWidget(m_pCalendarWidget, nRowIndex, 0, 2, 2);

	this->setLayout(m_pGridLayout);

	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	
	QMetaObject::connectSlotsByName(this);
}


void CNewOrderWindow::_TranslateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_WindowTitle.c_str()));

	m_pLabel_Symbol->setText(DEFVALUE_String_Label_Symbol_Text.c_str());
	m_pLineEdit_Symbol->setText(m_strSymbolUse);

	if (m_pComboBox_OrderType->count() <= 0)
	{
		m_pComboBox_OrderType->insertItem(0, DEFVALUE_String_OrderType_MARKET.c_str());
	}
	else
	{
		m_pComboBox_OrderType->setItemText(0, DEFVALUE_String_OrderType_MARKET.c_str());
	}

	m_pLabel_OrderType->setText(DEFVALUE_String_Label_OrderType_Text.c_str());

	m_pLabel_Volume->setText(QObject::tr("Volume:"));
	m_pSpinBox_Volume->setValue(m_nVolume);
	m_pSpinBox_Volume->setRange(0, 10000000);

	m_pLabel_Price->setText(QObject::tr("Price:"));
	m_pSpinBox_Price->setValue(m_fPrice);
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

	m_strSymbolUse = strSymbolUse;
	m_nVolume = 100;
	//m_pSpinBox_Price_Value;

	m_pDateTimeEdit->setMinimumDate(dateTimeFrom.date());
	m_pDateTimeEdit->setMaximumDate(dateTimeTo.date());
	m_pDateTimeEdit->setDisplayFormat(DEFVALUE_String_Data_Format);
	m_pDateTimeEdit->setDate(dateTimeTo.date());//QDateTime::currentDateTime()

// 	m_pCalendarWidget->setMinimumDate(dateTimeFrom.date());
// 	m_pCalendarWidget->setMaximumDate(dateTimeTo.date());
// 	m_pCalendarWidget->setSelectedDate(dateTimeTo.date());//QDate::currentDate()

	this->_TranslateLanguage();
}

void CNewOrderWindow::resetPrice( const QString& strDate, const QString& strSymbolUse, double fPrice )
{
	if (m_strData == strDate)
	{
		m_fPrice = fPrice;
		m_pSpinBox_Price->setValue(m_fPrice);
		QString strMesg = QString("get fPrice=%1\n strSymbolUse=%2\n strData=%3\n").arg(m_fPrice).arg(m_strSymbolUse).arg(m_strData);
		QMessageBox msgBox;
		msgBox.setText(strMesg);
		msgBox.exec();
	}
	else
	{
		m_fPrice = fPrice;
		m_pSpinBox_Price->setValue(m_fPrice);
		QString strMesg = QString("not fPrice for strSymbolUse=%1\n strData=%2\n").arg(m_strSymbolUse).arg(m_strData);
		QMessageBox msgBox;
		msgBox.setText(strMesg);
		msgBox.exec();
	}
}


void CNewOrderWindow::slotPushButtonBuyClicked( bool checked )
{
	int nCurrentIndex = 0;
	QString strOrderType;
	QDate nTradeDate;
	QString strTime;;
	QString strSymbolUse;
	double fbuyPrice = 0;
	qint32 nBuyVolume = 0;

	nCurrentIndex = m_pComboBox_OrderType->currentIndex();
	strOrderType = m_pComboBox_OrderType->itemText(nCurrentIndex);

	nTradeDate = m_pDateTimeEdit->date();
	strTime = m_pQtTimeHelper->getStringValue(nTradeDate);
	strSymbolUse = m_strSymbolUse;
	fbuyPrice = m_pSpinBox_Price->value();
	nBuyVolume = m_pSpinBox_Volume->value();

	m_pUserTradeInfo->setValue_Buy(strTime, strSymbolUse, fbuyPrice, nBuyVolume);

	//
	m_pNewOrderConfirmWindow->resetData(m_pUserTradeInfo);
	m_pNewOrderConfirmWindow->move(this->pos().x()+this->width()+10, this->pos().y());
	m_pNewOrderConfirmWindow->show();

}

void CNewOrderWindow::slotPushButtonSellClicked( bool checked )
{
	int nCurrentIndex = 0;
	QString strOrderType;
	QDate nTradeDate;
	QString strTime;;
	QString strSymbolUse;
	double fbuyPrice = 0;
	qint32 nBuyVolume = 0;

	nCurrentIndex = m_pComboBox_OrderType->currentIndex();
	strOrderType = m_pComboBox_OrderType->itemText(nCurrentIndex);

	nTradeDate = m_pDateTimeEdit->date();
	strTime = m_pQtTimeHelper->getStringValue(nTradeDate);
	strSymbolUse = m_strSymbolUse;
	fbuyPrice = m_pSpinBox_Price->value();
	nBuyVolume = m_pSpinBox_Volume->value();

	m_pUserTradeInfo->setValue_Sell(strTime, strSymbolUse, fbuyPrice, nBuyVolume);

	//
	m_pNewOrderConfirmWindow->resetData(m_pUserTradeInfo);
	m_pNewOrderConfirmWindow->move(this->pos().x()+this->width()+10, this->pos().y());
	m_pNewOrderConfirmWindow->show();


}


void CNewOrderWindow::slotCalendarWidgetClicked( const QDate & date )
{
	m_pDateTimeEdit->setDate(date);
}

void CNewOrderWindow::slotDateChanged ( const QDate & date )
{
	QDate nDateTmp;
	nDateTmp = date;
	m_strData = m_pQtTimeHelper->getStringValue(nDateTmp);
	//CClientDBManager::getInstance().selectDataHistory_DataTime(m_pTextEdit_Symbol_Value, m_strData, &pHistoryData);
	CClientDataManager::getInstance().send_req_ReqStockHistoryData(m_strSymbolUse, m_strData, m_strData);//1

}

void CNewOrderWindow::_CreateConnect()
{	
	//QObject::connect(m_pCalendarWidget, SIGNAL(clicked(const QDate &)), this, SLOT(slotCalendarWidgetClicked(const QDate &)));
	QObject::connect(m_pDateTimeEdit, SIGNAL(dateChanged(const QDate &)), this, SLOT(slotDateChanged(const QDate &)));
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
		CClientDataManager::getInstance().send_req_NewOrder(m_pUserTradeInfo);
	}
	else// if (-1 ==  nEOrderConfirm)
	{
		MYLOG4CPP_DEBUG<<" "<<"user Cancel new order";
	}
}


//QT_END_NAMESPACE

