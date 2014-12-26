#ifndef __CLASS_USER_ORDER_TABLE_VIEW_HH__
#define __CLASS_USER_ORDER_TABLE_VIEW_HH__

#include <QtGui/QTableView>

class CItemModelUserOrder;

class CUserOrderTableView : public QTableView
{ 
	Q_OBJECT
public: 
	CUserOrderTableView(QWidget* parent = 0); 
	~CUserOrderTableView(); 
public slots:
signals:
public:
	void slot_DataChange_UserOrder();
private:
private:
	CItemModelUserOrder* m_pItemModel;

}; 



#endif//__CLASS_USER_ORDER_TABLE_VIEW_HH__



