#ifndef __CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__
#define __CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__

#include <QtGui/QTableView>

class CItemModelUserInstrument;
class CWaitingInstrumentTreeView;
class CNewOrderWindow;

class CUserInstrumentTableView : public QTableView
{ 
	Q_OBJECT
public: 
	CUserInstrumentTableView(QWidget* parent = 0); 
	~CUserInstrumentTableView(); 
public slots:
	void slotActionAddUserInstrument();
	void slotActionRemoveUserInstrument();
	void slotActionCustomColumns();
	void slotActionNewOrder();
signals:
	void signalParpareWaitingInstrument();
protected:
	//overwite QWight fun
	void contextMenuEvent(QContextMenuEvent* pEvent);
public:
	void slot_DataChange_UserInstrument();
private:
	void _CreateAction();
	void _CreateConnect();
private:
	CItemModelUserInstrument* m_pItemModel;
private:
	QAction* m_pActionAddUserInstrument;
	QAction* m_pActionRemoveUserInstrument;
	QAction* m_pActionCustomColumns;
	QAction* m_pActionNewOrder;

private:
	CWaitingInstrumentTreeView* m_pWaitingInstrumentTreeView;
	CNewOrderWindow* m_pNewOrderWindow;
}; 



#endif//__CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__



