#ifndef __CLASS_STOCK_HISTORY_DATA_TABLE_VIEW_HH__
#define __CLASS_STOCK_HISTORY_DATA_TABLE_VIEW_HH__

#include <QtGui/QTableView>

class QSqlTableModel;

class CStockHistoryDataTableView : public QTableView
{ 
	Q_OBJECT
public: 
	CStockHistoryDataTableView(QWidget* parent = 0); 
	~CStockHistoryDataTableView(); 
signals:
public slots:
	void slot_DataChange_StockHistoryData();
private:
	QSqlTableModel* m_pItemModel;
}; 



#endif//__CLASS_STOCK_HISTORY_DATA_TABLE_VIEW_HH__



