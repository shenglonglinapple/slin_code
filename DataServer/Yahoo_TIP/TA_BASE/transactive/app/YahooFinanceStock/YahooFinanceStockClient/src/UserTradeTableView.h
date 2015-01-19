#ifndef __CLASS_USER_TRADE_TABLE_VIEW_HH__
#define __CLASS_USER_TRADE_TABLE_VIEW_HH__

#include <QtGui/QTableView>

class QSqlTableModel;

class CUserTradeTableView : public QTableView
{ 
	Q_OBJECT
public: 
	CUserTradeTableView(QWidget* parent = 0); 
	~CUserTradeTableView(); 
signals:
public slots:
	void slot_DataChange_UserTrade();
private:
	void _CreateAction();
	void _CreateConnect();
private:
	QSqlTableModel* m_pItemModel;

}; 



#endif//__CLASS_USER_TRADE_TABLE_VIEW_HH__



