#include "NewOrderConfirmWindow.h"

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "UserTradeInfo.h"

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 300;

static const std::string DEFVALUE_String_COrderInfoWidget_WindowTitle = "New Order Info";
static const std::string DEFVALUE_String_Label_SymbolUse_Text = "SymbolUse:";
static const std::string DEFVALUE_String_Label_OrderType_Text = "Order Type:";

static const std::string DEFVALUE_String_OrderType_MARKET = "MARKET";


CNewOrderConfirmWindow::CNewOrderConfirmWindow(QWidget *parent)
: QDialog(parent)
{
	m_pLabel_SymbolUse = NULL;
	m_pLabel_SymbolUse_Value = NULL;
	m_pLabel_Volume = NULL;
	m_pLabel_Volume_Value = NULL;
	m_pLabel_Price = NULL;
	m_pLabel_Price_Value = NULL;
	
	m_pPushButtonOK = NULL;
	m_pPushButtonCancel = NULL;
	m_pLabel_TradeDataTime = NULL;
	m_pLabel_TradeDataTime_Value = NULL;

	m_str_OrderSide_Value.clear();
	m_str_SymbolUse_Value.clear();
	m_str_Price_Value.clear();//
	m_str_Volume_Value.clear();//
	m_str_TradeDataTime_Value.clear();

	m_str_OrderSide_Value = "";
	m_str_SymbolUse_Value = "";
	m_str_Volume_Value = "1";
	m_str_Price_Value = "000000000.00000";//(long double 99.9L)(double 99.9)//printf("%.7g\n", m_pSpinBox_Price_Value); 
	m_str_TradeDataTime_Value = "";

	this->_SetupUi();
	this->_TranslateLanguage();
	this->_CreateConnect();

}


CNewOrderConfirmWindow::~CNewOrderConfirmWindow()
{

}



void CNewOrderConfirmWindow::_SetupUi()
{
	//eg: Symbol: IF1401
	m_pLabel_SymbolUse = new QLabel(this);
	m_pLabel_SymbolUse_Value = new QLabel(this);

	//Volume: 1
	m_pLabel_Volume = new QLabel(this);
	m_pLabel_Volume_Value = new QLabel(this);

	//eg: Price: 0.00
	m_pLabel_Price = new QLabel(this);
	m_pLabel_Price_Value = new QLabel(this);

	m_pLabel_TradeDataTime = new QLabel(this);
	m_pLabel_TradeDataTime_Value = new QLabel(this);


	//Buy  Sell
	m_pPushButtonOK = new QPushButton(this);
	m_pPushButtonCancel = new QPushButton(this);

	m_pGridLayout = new QGridLayout(this);
	int nRowIndex = 0;
	m_pGridLayout->addWidget(m_pLabel_SymbolUse, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_SymbolUse_Value, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pLabel_Volume, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_Volume_Value, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pLabel_Price, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_Price_Value, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pLabel_TradeDataTime, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_TradeDataTime_Value, nRowIndex, 1, 1, 2);
	nRowIndex++;
	m_pGridLayout->addWidget(m_pPushButtonOK, nRowIndex, 0, 1, 1);
	m_pGridLayout->addWidget(m_pPushButtonCancel, nRowIndex, 1, 1, 1);

	this->setLayout(m_pGridLayout);

	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	
	QMetaObject::connectSlotsByName(this);
}


void CNewOrderConfirmWindow::_TranslateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_COrderInfoWidget_WindowTitle.c_str()));

	m_pLabel_SymbolUse->setText(QObject::tr(DEFVALUE_String_Label_SymbolUse_Text.c_str()));
	m_pLabel_SymbolUse_Value->setText(m_str_SymbolUse_Value);

	m_pLabel_Volume->setText(QObject::tr("Volume:"));
	m_pLabel_Volume_Value->setText(m_str_Volume_Value);

	m_pLabel_Price->setText(QObject::tr("Price:"));
	m_pLabel_Price_Value->setText(m_str_Price_Value);

	m_pLabel_TradeDataTime->setText(QObject::tr("TradeDataTime:"));
	m_pLabel_TradeDataTime_Value->setText(m_str_TradeDataTime_Value);

	m_pPushButtonOK->setText(QObject::tr("OK"));
	m_pPushButtonCancel->setText(QObject::tr("Cancel"));
}




void CNewOrderConfirmWindow::slotPushButtonOKClicked( bool checked )
{
	//emit
	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CNewOrderConfirmWindow"
			<<" "<<"fun:"<<"slotPushButtonOKClicked()"
			<<" "<<"emit"
			<<" "<<"signalConfirmOrder()"
			<<" "<<"param:"
			<<" "<<"COrderData::EOrderConfirm="<<0;

		emit signalConfirmOrder(0);
	}
}

void CNewOrderConfirmWindow::slotPushButtonCancelClicked( bool checked )
{
	//emit
	//emit
	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CNewOrderConfirmWindow"
			<<" "<<"fun:"<<"slotPushButtonCancelClicked()"
			<<" "<<"emit"
			<<" "<<"signalConfirmOrder()"
			<<" "<<"param:"
			<<" "<<"COrderData::EOrderConfirm="<<-1;

		emit signalConfirmOrder(-1);
	}
}

void CNewOrderConfirmWindow::_CreateConnect()
{

	QObject::connect(m_pPushButtonOK, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotPushButtonOKClicked(bool)));

	QObject::connect(m_pPushButtonCancel, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotPushButtonCancelClicked(bool)));
}


void CNewOrderConfirmWindow::resetData( const CUserTradeInfo* pInfo)
{
	m_str_SymbolUse_Value = pInfo->m_strSymbolUse;
	m_str_OrderSide_Value = CTcpComProtocol::getStringValue(CTcpComProtocol::EDataType(pInfo->m_nTradeType));
	m_str_Price_Value = QVariant(pInfo->m_fTradePrice).toString();
	m_str_Volume_Value = QVariant(pInfo->m_nTradeVolume).toString();
	m_str_TradeDataTime_Value = pInfo->m_strTradeTime;

	this->_TranslateLanguage();
	//this->show();

}



