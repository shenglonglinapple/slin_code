#ifndef __CLASS_USER_TRADE_WINDOW_HH__
#define __CLASS_USER_TRADE_WINDOW_HH__

#include <QtGui/QTabWidget>

class CUserOrderTableView;

class CUserTradeWindow : public QTabWidget
{ 
	Q_OBJECT
public: 
	CUserTradeWindow(QWidget* parent = 0); 
	~CUserTradeWindow(); 
signals:

public slots:
private:
	void _SetupUi();
	void _TranslateLanguage();
private:
	CUserOrderTableView* m_pUserOrderTableView;
}; 



#endif//__CLASS_USER_ORDER_TABLE_VIEW_HH__



