#ifndef __CLASS__NEW_ORDER_CONFIRM_WINDOW_HH__
#define __CLASS__NEW_ORDER_CONFIRM_WINDOW_HH__

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QModelIndex>

#include <QtGui/QDialog>


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

class CUserTradeInfo;

class CNewOrderConfirmWindow : public QDialog
{
    Q_OBJECT

public:
    CNewOrderConfirmWindow(QWidget *parent = 0);
	~CNewOrderConfirmWindow();
signals:
	//COrderData::EOrderConfirm
	void signalConfirmOrder(qint32 nEOrderConfirm);


public:
	void resetData(const CUserTradeInfo* pInfo);

private slots:
	void slotPushButtonOKClicked(bool checked);
	void slotPushButtonCancelClicked(bool checked);

public:
	void _SetupUi();
	void _TranslateLanguage();

private:
	void _CreateConnect();
private:
	QString m_str_SymbolUse_Value;
	QString m_str_TradeType_Value;
	QString m_str_Price_Value;
	QString m_str_Volume_Value;
	QString m_str_TradeDataTime_Value;
	
private:
	QGridLayout* m_pGridLayout;

	QLabel* m_pLabel_SymbolUse;
	QLabel* m_pLabel_SymbolUse_Value;

	QLabel* m_pLabel_TradeType;
	QLabel* m_pLabel_TradeType_Value;

	QLabel* m_pLabel_Volume;
	QLabel* m_pLabel_Volume_Value;

	QLabel* m_pLabel_Price;
	QLabel* m_pLabel_Price_Value;

	QLabel* m_pLabel_TradeDataTime;
	QLabel* m_pLabel_TradeDataTime_Value;

	QPushButton* m_pPushButtonOK;
	QPushButton* m_pPushButtonCancel;


};

//QT_END_NAMESPACE


#endif//__CLASS__NEW_ORDER_CONFIRM_WINDOW_HH__
