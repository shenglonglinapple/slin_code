#ifndef __CLASS__NEW_ORDER_WINDOW_H__
#define __CLASS__NEW_ORDER_WINDOW_H__

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
class QCalendarWidget;
QT_END_NAMESPACE

class CUserTradeInfo;
class CNewOrderConfirmWindow;
class QDateTimeEdit;
class CQtTimeHelper;

class CNewOrderWindow : public QDialog
{
    Q_OBJECT

public:
    CNewOrderWindow(QWidget *parent = 0);
	~CNewOrderWindow();

signals:

public slots:
	void slotConfirmOrder(qint32 nEOrderConfirm);
private slots:
	void slotPushButtonBuyClicked(bool checked);
	void slotPushButtonSellClicked(bool checked);
	void slotCalendarWidgetClicked (const QDate & date);
	void slotDateChanged ( const QDate & date );
public:
	void _SetupUi();
	void _TranslateLanguage();


public:
	void resetData(const QString& strSymbolUse, const QString& strTimeFrom, const QString& strTimeTo);
private:
	void _CreateConnect();
	void _InitData();
private:
	QString m_pTextEdit_Symbol_Value;
	QString m_pComboBox_OrderType_Value;
	int m_pSpinBox_Volume_Value;
	double m_pSpinBox_Price_Value;
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

	QPushButton* m_pPushButtonBuy;
	QPushButton* m_pPushButtonSell;

	QLabel* m_pLabel_DateTime;
	QDateTimeEdit* m_pDateTimeEdit;
	//QCalendarWidget* m_pCalendarWidget;
public:
	CNewOrderConfirmWindow* m_pNewOrderConfirmWindow;
	CUserTradeInfo* m_pUserTradeInfo;
	CQtTimeHelper* m_pQtTimeHelper;
};

//QT_END_NAMESPACE


#endif//__CLASS__NEW_ORDER_WINDOW_H__
