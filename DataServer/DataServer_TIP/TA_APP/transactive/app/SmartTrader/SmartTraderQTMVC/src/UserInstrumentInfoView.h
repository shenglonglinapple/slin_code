#ifndef __CLASS_USER_INSTRUMENT_INFO_VIEW_HH__
#define __CLASS_USER_INSTRUMENT_INFO_VIEW_HH__



#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QModelIndex>
#include <QtCore/QStringList>

#include <QtGui/QMainWindow>
#include <QtGui/QTreeView>
#include <QtGui/QTableView>
#include <QtGui/QHeaderView>




//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class IconDelegate;
class CCreateNewOrderDialog;
class CCustomColumnsDialog;
class CInstrumentInfoView;
class CUserInstrumentInfoHeaderView;
class CUserOrderInfo;

class CUserInstrumentInfoView : public QTableView
{ 
	Q_OBJECT

public: 
	CUserInstrumentInfoView(QWidget* parent = 0); 
	~CUserInstrumentInfoView(); 
public slots:
	void slotActionAddHotQuotesTriggered();
	void slotActionRemoveHotQuotesTriggered();
	void slotActionCustomColumnsTriggered();
	void slotModifySelectedColumns(QStringList lstAllAvailableColums, QStringList lstSelectedColumns);
	void slotMouseRightClickInHHeaderView(QMouseEvent* e);
signals:
	void signalCurrentInstrumentChanged(unsigned int nInstrumentID);
protected:
	//overwite QWight fun
	void contextMenuEvent(QContextMenuEvent* pEvent);
	void mouseDoubleClickEvent(QMouseEvent* pEvent);
	void currentChanged(const QModelIndex & current, const QModelIndex & previous);
private:
	void _CreateConnect();
	void _SetCurrentInstrumentID(unsigned int nInstrumentID);

private:
	bool _CheckIsColumnModified(const QStringList& lstAllAvailableColums, const QStringList& lstSelectedColumns);

public:
	CInstrumentInfoView* m_pInstrumentInfoView;
	CCreateNewOrderDialog* m_pCreateNewOrderDialog;
	CUserOrderInfo* m_pUserOrderInfo;

private:
	QString m_strSelectedColumnsForCheck;

private:
	QAction* m_pActionAddUserInstrument;
	QAction* m_pActionRemoveUserInstrument;
	QAction* m_pActionCustomColumns;
	IconDelegate* m_pIconDelegate_Column_Change;
	int m_nColumnIndex_Change;
	CCustomColumnsDialog* m_pCustomColumnsDialog;
	CUserInstrumentInfoHeaderView* m_pHorizontalHeader;
	QHeaderView* m_pVerticalHeader;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_USER_INSTRUMENT_INFO_VIEW_HH__



