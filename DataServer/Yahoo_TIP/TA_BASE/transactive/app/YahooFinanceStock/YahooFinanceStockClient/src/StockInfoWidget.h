#ifndef __CLASS_STOCK_INFO_WIDGET_HH__
#define __CLASS_STOCK_INFO_WIDGET_HH__

#include <QtGui/QWidget>
#include <QtGui/QTableView>

class QSqlTableModel;

class CStockInfoWidget : public QWidget
{ 
	Q_OBJECT
public: 
	CStockInfoWidget(QWidget* parent = 0); 
	~CStockInfoWidget(); 
signals:
public slots:
	void slot_DataChange_StockInfo();
private:
	void _CreateAction();
	void _CreateConnect();
private:
	QTableView* m_pStockInfoTableView;
	QSqlTableModel* m_pStockInfoModel;
}; 



#endif//__CLASS_STOCK_INFO_WIDGET_HH__



