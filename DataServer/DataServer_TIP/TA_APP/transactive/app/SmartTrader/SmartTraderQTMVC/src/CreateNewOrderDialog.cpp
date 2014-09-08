#include "CreateNewOrderDialog.h"

#include "ProjectQTInclude.h"


#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 300;

static const std::string DEFVALUE_String_CCreateNewOrderDialog_WindowTitle = "Create New Order";
static const std::string DEFVALUE_String_Label_Symbol_Text = "Symbol:";
static const std::string DEFVALUE_String_Label_OrderType_Text = "Order Type:";
	
static const std::string DEFVALUE_String_ComboBox_OrderType_Item_0__Limit = "Limit";
static const std::string DEFVALUE_String_ComboBox_OrderType_Item_1_Market_FAK = "Market-FAK";
static const std::string DEFVALUE_String_ComboBox_OrderType_Item_2__Limit_GTC = "#Limit-GTC";
static const std::string DEFVALUE_String_ComboBox_OrderType_Item_3_Stop_Limit = "#Stop-Limit";
static const std::string DEFVALUE_String_ComboBox_OrderType_Item_4_Stop_Item_Limit_GTC = "#Stop-Limit-GTC";
static const std::string DEFVALUE_String_ComboBox_OrderType_Item_5_Stop_Limit_If_Touched = "#Limit_If-Touched";

static const std::string DEFVALUE_String_ComboBox_OpenClose_Item_0_Open = "Open";
static const std::string DEFVALUE_String_ComboBox_OpenClose_Item_1_Close = "Close";
static const std::string DEFVALUE_String_ComboBox_OpenClose_Item_2_Auto = "Auto";


CCreateNewOrderDialog::CCreateNewOrderDialog(QWidget *parent)
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

	m_pTextEdit_Symbol_Value.clear();
	m_pComboBox_OrderType_Value.clear();
	m_pComboBox_OpenClose_Value.clear();
	m_pSpinBox_Volume_Value = 0;
	m_pSpinBox_Price_Value = 0;


	m_pTextEdit_Symbol_Value = "IF1401";
	m_pComboBox_OrderType_Value = DEFVALUE_String_ComboBox_OrderType_Item_0__Limit.c_str();
	m_pComboBox_OpenClose_Value = DEFVALUE_String_ComboBox_OpenClose_Item_0_Open.c_str();
	m_pSpinBox_Volume_Value = 1;
	m_pSpinBox_Price_Value = 99.9f;//(long double 99.9L)(double 99.9)//printf("%.7g\n", m_pSpinBox_Price_Value); 

	this->setupUi();
	this->translateLanguage();
	this->_CreateConnect();

}


CCreateNewOrderDialog::~CCreateNewOrderDialog()
{

}



void CCreateNewOrderDialog::setupUi()
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


void CCreateNewOrderDialog::translateLanguage()
{
	int nIndex = 0;

	this->setWindowTitle(QObject::tr(DEFVALUE_String_CCreateNewOrderDialog_WindowTitle.c_str()));
	m_pLabel_Symbol->setText(DEFVALUE_String_Label_Symbol_Text.c_str());
	m_pLineEdit_Symbol->setText(m_pTextEdit_Symbol_Value);
	nIndex = 0;
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_ComboBox_OrderType_Item_0__Limit.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_ComboBox_OrderType_Item_1_Market_FAK.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_ComboBox_OrderType_Item_2__Limit_GTC.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_ComboBox_OrderType_Item_3_Stop_Limit.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_ComboBox_OrderType_Item_4_Stop_Item_Limit_GTC.c_str());
	m_pComboBox_OrderType->insertItem(nIndex++, DEFVALUE_String_ComboBox_OrderType_Item_5_Stop_Limit_If_Touched.c_str());

	m_pLabel_OrderType->setText(DEFVALUE_String_Label_OrderType_Text.c_str());

	m_pLabel_Volume->setText(QObject::tr("Volume:"));
	m_pSpinBox_Volume->setValue(m_pSpinBox_Volume_Value);

	m_pLabel_Price->setText(QObject::tr("Price:"));
	m_pSpinBox_Price->setValue(m_pSpinBox_Volume_Value);

	m_pLabel_TagName->setText(QObject::tr("Tag Name:"));
	nIndex = 0;
	m_pComboBox_TagName->insertItem(nIndex++, QObject::tr("Tag Name 1"));

	m_pPushButtonBuy->setText("Buy");
	m_pPushButtonSell->setText("Sell");

	m_pLabel_BuyVolume->setText(QObject::tr("0"));
	m_pLabel_Delimiter->setText(QObject::tr("/"));
	m_pLabel_SellVolume->setText(QObject::tr("0"));
}

void CCreateNewOrderDialog::resetData(const QString& strInstrumentCode, int nVolume, float fPrice)
{
	m_pTextEdit_Symbol_Value = strInstrumentCode;
	m_pSpinBox_Volume_Value = nVolume;
	m_pSpinBox_Price_Value = fPrice;

	m_pLineEdit_Symbol->setText(m_pTextEdit_Symbol_Value);
	m_pSpinBox_Volume->setValue(m_pSpinBox_Volume_Value);
	m_pSpinBox_Price->setValue(m_pSpinBox_Price_Value);

}

Order::OrderType CCreateNewOrderDialog::_GetOrderType(const QString& strOrderType)
{
	if (strOrderType.isEmpty())
	{
		return Order::UNKNOWN;
	}
	else if (0 == strOrderType.compare(QString(DEFVALUE_String_ComboBox_OrderType_Item_0__Limit.c_str())))
	{
		return Order::LIMIT;
	}
	else if (0 == strOrderType.compare(QString(DEFVALUE_String_ComboBox_OrderType_Item_1_Market_FAK.c_str())))
	{
		return Order::MARKET_FAK;
	}
	else
	{
		return Order::MARKET;
	}

}

void CCreateNewOrderDialog::slotPushButtonBuyClicked( bool checked )
{
	//int nOrderType = 0;
	QString strOrderType;
	int quantity = 0;
	double fPrice = 0;

	Order::Side nGetSide = Order::BUY;
	Order::OrderType nGetOrderType = Order::UNKNOWN;
	QString strInstrumentCode;

	//nOrderType = m_pComboBox_OrderType->currentIndex();
	strOrderType = m_pComboBox_OrderType->currentText();
	nGetSide = Order::BUY;
	nGetOrderType = _GetOrderType(strOrderType);
	strInstrumentCode = m_pLineEdit_Symbol->text();
	fPrice = m_pSpinBox_Price->value();
	quantity = m_pSpinBox_Volume->value();
	


	//emit
	{
		LOG_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CCreateNewOrderDialog"
			<<" "<<"fun:"<<"slotPushButtonBuyClicked(bool checked)"
			<<" "<<"emit"
			<<" "<<"signalNewOrder()"
			<<" "<<"param:"
			<<" "<<"nGetSide="<<nGetSide
			<<" "<<"nGetOrderType="<<nGetOrderType
			<<" "<<"strInstrumentCode="<<strInstrumentCode.toStdString().c_str()
			<<" "<<"fPrice="<<fPrice
			<<" "<<"quantity="<<quantity;

		emit signalNewOrder(nGetSide, nGetOrderType, strInstrumentCode, fPrice, quantity);	
	}

}

void CCreateNewOrderDialog::slotPushButtonSellClicked( bool checked )
{

}

void CCreateNewOrderDialog::_CreateConnect()
{

	QObject::connect(m_pPushButtonBuy, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotPushButtonBuyClicked()));

	QObject::connect(m_pPushButtonSell, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotPushButtonSellClicked()));
}


//QT_END_NAMESPACE

