#include "NewOrderWindow.h"

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"

#include "SignalSlotManager.h"
#include "ClientDataManager.h"
#include "OrderData.h"
#include "NewOrderConfirmWindow.h"
#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 300;

static const std::string DEFVALUE_String_Window_WindowTitle = "New Order";
static const std::string DEFVALUE_String_Label_Symbol_Text = "Symbol:";
static const std::string DEFVALUE_String_Label_OrderType_Text = "Order Type:";
	

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
	m_pLabel_TagName = NULL;
	m_pComboBox_TagName = NULL;
	m_pPushButtonBuy = NULL;
	m_pPushButtonSell = NULL;
	m_pNewOrderConfirmWindow = NULL;
	m_pOrderData = NULL;

	m_pTextEdit_Symbol_Value.clear();
	m_pComboBox_OrderType_Value.clear();
	m_pSpinBox_Volume_Value = 0;
	m_pSpinBox_Price_Value = 0;

	_InitData();
	m_pOrderData = new COrderData();

	this->setupUi();
	this->translateLanguage();
	this->_CreateConnect();

}


CNewOrderWindow::~CNewOrderWindow()
{
	if (NULL != m_pOrderData)
	{
		delete m_pOrderData;
		m_pOrderData = NULL;
	}
}

void CNewOrderWindow::_InitData()
{
	m_pTextEdit_Symbol_Value = "";
	m_pComboBox_OrderType_Value = DEFVALUE_String_OrderType_MARKET.c_str();
	m_pSpinBox_Volume_Value = 1;
	m_pSpinBox_Price_Value = 000000000.00000f;//(long double 99.9L)(double 99.9)//printf("%.7g\n", m_pSpinBox_Price_Value); 

}

void CNewOrderWindow::setupUi()
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

	m_pLabel_TagName = new QLabel(this);
	m_pComboBox_TagName = new QComboBox(this);

	//0 / 0
	m_pLabel_BuyVolume = new QLabel(this);
	m_pLabel_Delimiter = new QLabel(this);
	m_pLabel_SellVolume = new QLabel(this);

	//Buy  Sell
	m_pPushButtonBuy = new QPushButton(this);
	//m_pPushButtonBuy->setMinimumSize(qSizeButtonBuy);


	m_pPushButtonSell = new QPushButton(this);
	//m_pPushButtonSell->setMinimumSize(qSizeButtonSell);

	m_pGridLayout = new QGridLayout(this);
	m_pGridLayout->addWidget(m_pLabel_Symbol, 0, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLineEdit_Symbol, 0, 1, 1, 2);
	m_pGridLayout->addWidget(m_pLabel_OrderType, 1, 0, 1, 1);
	m_pGridLayout->addWidget(m_pComboBox_OrderType, 1, 1, 1, 2);
	m_pGridLayout->addWidget(m_pLabel_Volume, 2, 0, 1, 1);
	m_pGridLayout->addWidget(m_pSpinBox_Volume, 2, 1, 1, 2);
	m_pGridLayout->addWidget(m_pLabel_Price, 3, 0, 1, 1);
	m_pGridLayout->addWidget(m_pSpinBox_Price, 3, 1, 1, 2);
	m_pGridLayout->addWidget(m_pLabel_TagName, 4, 0, 1, 1);
	m_pGridLayout->addWidget(m_pComboBox_TagName, 4, 1, 1, 2);
	m_pGridLayout->addWidget(m_pLabel_BuyVolume, 5, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_Delimiter, 5, 1, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_SellVolume, 5, 2, 1, 1);
	m_pGridLayout->addWidget(m_pPushButtonBuy, 6, 0, 1, 2);
	m_pGridLayout->addWidget(m_pPushButtonSell, 6, 2, 1, 1);

	this->setLayout(m_pGridLayout);

	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	
	QMetaObject::connectSlotsByName(this);
}


void CNewOrderWindow::translateLanguage()
{
	int nIndex = 0;

	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_WindowTitle.c_str()));
	m_pLabel_Symbol->setText(DEFVALUE_String_Label_Symbol_Text.c_str());
	m_pLineEdit_Symbol->setText(m_pTextEdit_Symbol_Value);
	nIndex = 0;

	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_OrderType_MARKET.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_OrderType_MARKET_FAK.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_OrderType_MARKET_FOK.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_OrderType_LIMIT.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_OrderType_LIMIT_FAK.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_OrderType_LIMIT_FOK.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_OrderType_STOP.c_str());

	m_pLabel_OrderType->setText(DEFVALUE_String_Label_OrderType_Text.c_str());

	m_pLabel_Volume->setText(QObject::tr("Volume:"));
	m_pSpinBox_Volume->setValue(m_pSpinBox_Volume_Value);

	m_pLabel_Price->setText(QObject::tr("Price:"));
	m_pSpinBox_Price->setValue(m_pSpinBox_Price_Value);
	m_pSpinBox_Price->setRange(0, 100000000);

	m_pLabel_TagName->setText(QObject::tr("Tag Name:"));
	nIndex = 0;
	m_pComboBox_TagName->insertItem(nIndex++, QObject::tr("Tag Name 1"));

	m_pPushButtonBuy->setText("Buy");
	m_pPushButtonSell->setText("Sell");

	m_pLabel_BuyVolume->setText(QObject::tr("0"));
	m_pLabel_Delimiter->setText(QObject::tr("/"));
	m_pLabel_SellVolume->setText(QObject::tr("0"));
}



void CNewOrderWindow::resetData( COrderData* pData )
{
	_InitData();
	m_pOrderData->clearData();

	m_pTextEdit_Symbol_Value = pData->m_strInstrumentCode;
	//m_pComboBox_OrderType_Value = DEFVALUE_String_OrderType_MARKET.c_str();
	m_pSpinBox_Volume_Value = pData->m_nVolume;
	m_pSpinBox_Price_Value = pData->m_fCurrentPrice;

	(*m_pOrderData) = (*pData);

	this->translateLanguage();

}


void CNewOrderWindow::slotPushButtonBuyClicked( bool checked )
{
	int nCurrentIndex = 0;
	QString strOrderType;

	nCurrentIndex = m_pComboBox_OrderType->currentIndex();
	strOrderType = m_pComboBox_OrderType->itemText(nCurrentIndex);


	m_pOrderData->m_nSide = COrderData::BUY;
	m_pOrderData->m_nOrderType = m_pOrderData->getEOrderType(strOrderType);
	m_pOrderData->m_nOrderStatus = COrderData::NEW;
	m_pOrderData->m_fTransactPrice = m_pSpinBox_Price->value();
	m_pOrderData->m_nVolume = m_pSpinBox_Volume->value();
	m_pOrderData->m_nTransactTime = 0;
	
	//
	m_pNewOrderConfirmWindow->resetData(m_pOrderData);
	m_pNewOrderConfirmWindow->move(this->pos().x()+this->width()+10, this->pos().y());
	m_pNewOrderConfirmWindow->show();

}

void CNewOrderWindow::slotPushButtonSellClicked( bool checked )
{
	int nCurrentIndex = 0;
	QString strOrderType;

	nCurrentIndex = m_pComboBox_OrderType->currentIndex();
	strOrderType = m_pComboBox_OrderType->itemText(nCurrentIndex);


	m_pOrderData->m_nSide = COrderData::SELL;
	m_pOrderData->m_nOrderType = m_pOrderData->getEOrderType(strOrderType);
	m_pOrderData->m_fCurrentPrice = m_pSpinBox_Price->value();
	m_pOrderData->m_nVolume = m_pSpinBox_Volume->value();

	//
	m_pNewOrderConfirmWindow->resetData(m_pOrderData);
	m_pNewOrderConfirmWindow->move(this->pos().x()+this->width()+10, this->pos().y());
	m_pNewOrderConfirmWindow->show();


}

void CNewOrderWindow::_CreateConnect()
{

	QObject::connect(m_pPushButtonBuy, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotPushButtonBuyClicked(bool)));

	QObject::connect(m_pPushButtonSell, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotPushButtonSellClicked(bool)));

	QObject::connect(m_pNewOrderConfirmWindow, 
		SIGNAL(signalConfirmOrder(COrderData::EOrderConfirm)),
		this, 
		SLOT(slotConfirmOrder(COrderData::EOrderConfirm)));

	
}

void CNewOrderWindow::slotConfirmOrder(COrderData::EOrderConfirm nEOrderConfirm)
{
	m_pNewOrderConfirmWindow->hide();

	if (NULL == m_pOrderData)
	{
		return;
	}

	//emit
	if (COrderData::OrderConfirm_OK == nEOrderConfirm)
	{
		CClientDataManager::getInstance().newOrder(*m_pOrderData);
	}
	else if (COrderData::OrderConfirm_Cancel ==  nEOrderConfirm)
	{
		MYLOG4CPP_DEBUG<<" "<<"user Cancel new order";
	}
}


//QT_END_NAMESPACE

