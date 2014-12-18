#ifndef __CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__
#define __CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__

#include <QtGui/QTableView>

class CItemModelUserInstrument;
class CWaitingInstrumentTreeView;

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
	CItemModelUserInstrument* m_pItemModelUserInstrument;
private:
	QAction* m_pActionAddUserInstrument;
	QAction* m_pActionRemoveUserInstrument;
	QAction* m_pActionCustomColumns;
private:
	CWaitingInstrumentTreeView* m_pWaitingInstrumentTreeView;
}; 



#endif//__CLASS_USER_INSTRUMENT_TABLE_VIEW_HH__



