#include "NewOrderConfirmWindow.h"

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "OrderData.h"

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
static const int DEFVALUE_INT_Window_Width = 400;
static const int DEFVALUE_INT_Window_Height = 300;

static const std::string DEFVALUE_String_COrderInfoWidget_WindowTitle = "New Order Info";
static const std::string DEFVALUE_String_Label_InstrumentCode_Text = "InstrumentCode:";
static const std::string DEFVALUE_String_Label_OrderType_Text = "Order Type:";


CNewOrderConfirmWindow::CNewOrderConfirmWindow(QWidget *parent)
: QDialog(parent)
{
	m_pLabel_InstrumentCode = NULL;
	m_pLabel_InstrumentCode_Value = NULL;
	m_pLabel_OrderType = NULL;
	m_pLabel_OrderType_Value = NULL;
	m_pLabel_Volume = NULL;
	m_pLabel_Volume_Value = NULL;
	m_pLabel_Price = NULL;
	m_pLabel_Price_Value = NULL;
	m_pPushButtonOK = NULL;
	m_pPushButtonCancel = NULL;
	m_pOrderData = NULL;

	m_str_OrderSide_Value.clear();
	m_str_OrderType_Value.clear();
	m_str_InstrumentCode_Value.clear();
	m_str_Price_Value.clear();//
	m_str_Quantity_Value.clear();//


	m_str_OrderSide_Value = "Buy";
	m_str_OrderType_Value = DEFVALUE_String_OrderType_LIMIT.c_str();
	m_str_InstrumentCode_Value = "IF1401";
	m_str_Quantity_Value = "1";
	m_str_Price_Value = "000000000.00000";//(long double 99.9L)(double 99.9)//printf("%.7g\n", m_pSpinBox_Price_Value); 

	m_pOrderData = new COrderData();
	this->setupUi();
	this->translateLanguage();
	this->_CreateConnect();

}


CNewOrderConfirmWindow::~CNewOrderConfirmWindow()
{
	if (NULL != m_pOrderData)
	{
		delete m_pOrderData;
		m_pOrderData = NULL;
	}
}



void CNewOrderConfirmWindow::setupUi()
{
	//eg: Symbol: IF1401
	m_pLabel_InstrumentCode = new QLabel(this);
	m_pLabel_InstrumentCode_Value = new QLabel(this);

	//eg: Order Type: Limit
	m_pLabel_OrderType = new QLabel(this);
	m_pLabel_OrderType_Value = new QLabel(this);

	//Volume: 1
	m_pLabel_Volume = new QLabel(this);
	m_pLabel_Volume_Value = new QLabel(this);

	//eg: Price: 0.00
	m_pLabel_Price = new QLabel(this);
	m_pLabel_Price_Value = new QLabel(this);

	//Buy  Sell
	m_pPushButtonOK = new QPushButton(this);
	m_pPushButtonCancel = new QPushButton(this);

	m_pGridLayout = new QGridLayout(this);
	m_pGridLayout->addWidget(m_pLabel_InstrumentCode, 0, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_InstrumentCode_Value, 0, 1, 1, 2);
	m_pGridLayout->addWidget(m_pLabel_OrderType, 1, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_OrderType_Value, 1, 1, 1, 2);
	m_pGridLayout->addWidget(m_pLabel_Volume, 2, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_Volume_Value, 2, 1, 1, 2);
	m_pGridLayout->addWidget(m_pLabel_Price, 3, 0, 1, 1);
	m_pGridLayout->addWidget(m_pLabel_Price_Value, 3, 1, 1, 2);
	m_pGridLayout->addWidget(m_pPushButtonOK, 4, 0, 1, 1);
	m_pGridLayout->addWidget(m_pPushButtonCancel, 4, 1, 1, 1);

	this->setLayout(m_pGridLayout);

	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	
	QMetaObject::connectSlotsByName(this);
}


void CNewOrderConfirmWindow::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_COrderInfoWidget_WindowTitle.c_str()));

	m_pLabel_InstrumentCode->setText(QObject::tr(DEFVALUE_String_Label_InstrumentCode_Text.c_str()));
	m_pLabel_InstrumentCode_Value->setText(m_str_InstrumentCode_Value);


	m_pLabel_OrderType->setText(QObject::tr(DEFVALUE_String_Label_OrderType_Text.c_str()));
	m_pLabel_OrderType_Value->setText(m_str_OrderType_Value);

	m_pLabel_Volume->setText(QObject::tr("Volume:"));
	m_pLabel_Volume_Value->setText(m_str_Quantity_Value);

	m_pLabel_Price->setText(QObject::tr("Price:"));
	m_pLabel_Price_Value->setText(m_str_Price_Value);


	m_pPushButtonOK->setText(QObject::tr("OK"));
	m_pPushButtonCancel->setText(QObject::tr("Cancel"));
}




void CNewOrderConfirmWindow::slotPushButtonOKClicked( bool checked )
{
	m_pOrderData->m_nOrderConfirm = COrderData::OrderConfirm_OK;

	//emit
	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CNewOrderConfirmWindow"
			<<" "<<"fun:"<<"slotPushButtonOKClicked()"
			<<" "<<"emit"
			<<" "<<"signalConfirmOrder()"
			<<" "<<"param:"
			<<" "<<"COrderData::EOrderConfirm="<<COrderData::OrderConfirm_OK;

		emit signalConfirmOrder(COrderData::OrderConfirm_OK);
	}
}

void CNewOrderConfirmWindow::slotPushButtonCancelClicked( bool checked )
{
	m_pOrderData->m_nOrderConfirm = COrderData::OrderConfirm_Cancel;

	//emit
	//emit
	{
		MYLOG4CPP_DEBUG<<" "<<"emit"
			<<" "<<"class:"<<"CNewOrderConfirmWindow"
			<<" "<<"fun:"<<"slotPushButtonCancelClicked()"
			<<" "<<"emit"
			<<" "<<"signalConfirmOrder()"
			<<" "<<"param:"
			<<" "<<"COrderData::EOrderConfirm="<<COrderData::OrderConfirm_Cancel;

		emit signalConfirmOrder(COrderData::OrderConfirm_Cancel);
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


void CNewOrderConfirmWindow::resetData( COrderData* pOrderData )
{
	(*m_pOrderData) = (*pOrderData);

	m_str_OrderSide_Value = m_pOrderData->getESide(m_pOrderData->m_nSide);
	m_str_OrderType_Value = m_pOrderData->getEOrderType(m_pOrderData->m_nOrderType);
	m_str_InstrumentCode_Value = m_pOrderData->m_strInstrumentCode;
	m_str_Price_Value = QVariant(m_pOrderData->m_fLastPrice).toString();
	m_str_Quantity_Value = QVariant(m_pOrderData->m_nQuantity).toString();

	this->translateLanguage();
	//this->show();

}




//QT_END_NAMESPACE

