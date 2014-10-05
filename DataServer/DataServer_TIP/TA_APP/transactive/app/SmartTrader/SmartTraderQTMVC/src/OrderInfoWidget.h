#ifndef __CLASS__ORDER_INFO_WIDGET_H__
#define __CLASS__ORDER_INFO_WIDGET_H__



#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QModelIndex>

#include <QtGui/QDialog>
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

class COrderInfoWidget : public QDialog
{
    Q_OBJECT

public:
    COrderInfoWidget(QWidget *parent = 0);
	~COrderInfoWidget();
signals:
	/*
	class: COrderInfoWidget
	signals:
	void signalOrderCheck(CUserOrderInfo* pUserOrderInfo);
	fun send signals: slotPushButtonOKClicked() slotPushButtonCancelClicked()

	class: CCreateNewOrderDialog
	public slots: 
	void slotOrderCheck(CUserOrderInfo* pUserOrderInfo);
	*/
	void signalOrderCheck(CUserOrderInfo* pUserOrderInfo);


public:
	void setOrderInfo(CUserOrderInfo* pUserOrderInfo);

private slots:
	void slotPushButtonOKClicked(bool checked);
	void slotPushButtonCancelClicked(bool checked);

public:
	void setupUi();
	void translateLanguage();

private:
	void _CreateConnect();
private:
	COrderInfo* m_pOrderInfo;
	CUserOrderInfo* m_pUserOrderInfo ;
private:
	QString m_str_OrderSide_Value;
	QString m_str_OrderType_Value;
	QString m_str_InstrumentCode_Value;
	QString m_str_Price_Value;
	QString m_str_Quantity_Value;
	



private:
	QGridLayout* m_pGridLayout;

	QLabel* m_pLabel_InstrumentCode;
	QLabel* m_pLabel_InstrumentCode_Value;

	QLabel* m_pLabel_OrderType;
	QLabel* m_pLabel_OrderType_Value;

	QLabel* m_pLabel_Volume;
	QLabel* m_pLabel_Volume_Value;

	QLabel* m_pLabel_Price;
	QLabel* m_pLabel_Price_Value;


	QPushButton* m_pPushButtonOK;
	QPushButton* m_pPushButtonCancel;


};

//QT_END_NAMESPACE


#endif//__CLASS__ORDER_INFO_WIDGET_H__
