#ifndef __CLASS__CREATE_NEW_ORDER_DIALOG_H__
#define __CLASS__CREATE_NEW_ORDER_DIALOG_H__



#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QModelIndex>

#include <QtGui/QDialog>
#include "OrderInfoWidget.h"
#include "Order.h"


QT_BEGIN_NAMESPACE
class QFormLayout;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;
class QMdiArea;
class QToolBar;
class QAction;
class QCheckBox;
class QSpinBox;
class QDoubleSpinBox;
class QGridLayout;
QT_END_NAMESPACE

class COrderInfo;
class CUserOrderInfo;

class CCreateNewOrderDialog : public QDialog
{
    Q_OBJECT

public:
    CCreateNewOrderDialog(QWidget *parent = 0);
	~CCreateNewOrderDialog();

signals:
	/*
	class: CCreateNewOrderDialog
	signals:
	void signalNewOrder(CUserOrderInfo* pUserOrderInfo);
	fun send signals: slotOrderCheck()

	class: CClientDataManagerWorker
	public slots: 
	void slotNewOrder(CUserOrderInfo* pUserOrderInfo);
	*/
	void signalNewOrder(CUserOrderInfo* pUserOrderInfo);
public slots:
	/*
	class: COrderInfoWidget
	signals:
	void signalOrderCheck(CUserOrderInfo* pUserOrderInfo);
	fun send signals: slotPushButtonOKClicked() slotPushButtonCancelClicked()

	class: CCreateNewOrderDialog
	public slots: 
	void slotOrderCheck(CUserOrderInfo* pUserOrderInfo);
	*/
	void slotOrderCheck(CUserOrderInfo* pUserOrderInfo);



private slots:
	void slotPushButtonBuyClicked(bool checked);
	void slotPushButtonSellClicked(bool checked);

public:
	void setupUi();
	void translateLanguage();


public:
	void resetData(CUserOrderInfo* pUserOrderInfo);
private:
	void _CreateConnect();
private:
	QString m_pTextEdit_Symbol_Value;
	QString m_pComboBox_OrderType_Value;
	QString m_pComboBox_OpenClose_Value;
	int m_pSpinBox_Volume_Value;
	float m_pSpinBox_Price_Value;

private:
	//QPushButton* m_pPushButtonBuy;
	//QPushButton* m_pPushButtonSell;

private:
	QGridLayout* m_pGridLayout;

	QLabel* m_pLabel_Symbol;
	QLineEdit* m_pLineEdit_Symbol;

	QLabel* m_pLabel_OrderType;
	QComboBox* m_pComboBox_OrderType;

	QLabel* m_pLabel_Volume;
	QSpinBox* m_pSpinBox_Volume;

	QLabel* m_pLabel_Price;
	QDoubleSpinBox* m_pSpinBox_Price;

	QLabel* m_pLabel_TagName;
	QComboBox* m_pComboBox_TagName;

	QLabel* m_pLabel_BuyVolume;
	QLabel* m_pLabel_Delimiter;//"/"
	QLabel* m_pLabel_SellVolume;


	QPushButton* m_pPushButtonBuy;
	QPushButton* m_pPushButtonSell;

public:
	COrderInfoWidget* m_pOrderInfoWidget;
	COrderInfo* m_pOrderInfo;
	CUserOrderInfo* m_pUserOrderInfo;
};

//QT_END_NAMESPACE


#endif//__CLASS__CREATE_NEW_ORDER_DIALOG_H__
