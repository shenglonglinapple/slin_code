#ifndef __CLASS_STOCK_MIN_TIME_MAX_TIME_TABLE_VIEW_HH__
#define __CLASS_STOCK_MIN_TIME_MAX_TIME_TABLE_VIEW_HH__

#include <QtGui/QTableView>

class QSqlTableModel;
class CNewOrderWindow;
class CHistoryData;

class CStockMinTimeMaxTimeTableView : public QTableView
{ 
	Q_OBJECT
public: 
	CStockMinTimeMaxTimeTableView(QWidget* parent = 0); 
	~CStockMinTimeMaxTimeTableView(); 
signals:
private slots:
	void slotActionReqHistoryData();
	void slotActionNewOrder();

public slots:
	void slot_DataChange_StockMinTimeMaxTime();
	void slot_DataChange_NewOrderData( CHistoryData* pData );

protected:
	//overwite QWight fun
	void contextMenuEvent(QContextMenuEvent* pEvent);
private:
	void _SetupUI();//_SetupUi
	void _CreateAction();
	void _CreateConnect();
private:
	QSqlTableModel* m_pItemModel;
private:
	QAction* m_pActionReqHistoryData;
	QAction* m_pActionNewOrder;
private:
	CNewOrderWindow* m_pNewOrderWindow;

}; 



#endif//__CLASS_STOCK_MIN_TIME_MAX_TIME_TABLE_VIEW_HH__



