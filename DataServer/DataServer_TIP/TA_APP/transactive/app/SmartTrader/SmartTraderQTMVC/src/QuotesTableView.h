#ifndef __CLASS_QUOTES_TABLE_VIEW_HH__
#define __CLASS_QUOTES_TABLE_VIEW_HH__



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
class CContractInfoWindow;
class CQuotesHHeaderView;

class CQuotesTableView : public QTableView
{ 
	Q_OBJECT

public: 
	CQuotesTableView(QWidget* parent = 0); 
	~CQuotesTableView(); 
public slots:

	/*
	class: m_pActionAddHotQuotes
	signals:
	void triggered();
	fun send signals: triggered()

	class: CSmartHotQuotesWindow
	public slots: 
	void slotActionAddHotQuotesTriggered();
	*/
	void slotActionAddHotQuotesTriggered();

	/*
	class: m_pActionRemoveHotQuotes
	signals:
	void triggered();
	fun send signals: triggered()

	class: CSmartHotQuotesWindow
	public slots: 
	void slotActionRemoveHotQuotesTriggered();
	*/
	void slotActionRemoveHotQuotesTriggered();


	/*
	class: m_pActionCustomColumns
	signals:
	void triggered();
	fun send signals: triggered()

	class: CSmartHotQuotesWindow
	public slots: 
	void slotActionCustomColumnsTriggered();
	*/
	void slotActionCustomColumnsTriggered();


	/*
	class: CCustomColumnsDialog
	signals:
	void signalModifySelectedColumns(QStringList lstAllAvailableColums, QStringList lstSelectedColumns);
	fun send signals: slotActionRemoveHotQuotesTriggered()

	class: CQuotesTableView
	public slots: 
	void slotModifySelectedColumns(QStringList lstAllAvailableColums, QStringList lstSelectedColumns);
	*/
	void slotModifySelectedColumns(QStringList lstAllAvailableColums, QStringList lstSelectedColumns);

	
	/*
	class: CQuotesTableViewHHeaderView
	signals:
	void signalMouseRightClickInHHeaderView(QMouseEvent*);
	fun send signals: mousePressEvent(QMouseEvent* e);

	class: CQuotesTableView
	public slots: 
	void slotMouseRightClickInHHeaderView(QMouseEvent* e;
	*/
	void slotMouseRightClickInHHeaderView(QMouseEvent* e);

signals:
	
	/*
	class: CQuotesTableView
	signals:
	void signalRemoveContractFromSmartQuotes(unsigned int nInstrumentID);
	fun send signals: slotActionRemoveHotQuotesTriggered()

	class: CClientDataManagerWorker
	public slots: 
	void slotRemoveContractFromSmartQuotes(unsigned int nInstrumentID);
	*/
	void signalRemoveContractFromSmartQuotes(unsigned int nInstrumentID);



	/*
	class: CQuotesTableView
	signals:
	void signalQuotesTableViewColumnsChanged();
	fun send signals: slotQuotesTableViewColumnsChanged()

	class: CClientDataManagerWorker
	public slots: 
	void slotQuotesTableViewColumnsChanged();
	*/
	void signalQuotesTableViewColumnsChanged();


	/*
	class: CQuotesTableView
	signals:
	void signalContractInfoWindowResetData();
	fun send signals: CQuotesTableView::contextMenuEvent()
	CQuotesTableView::slotMouseRightClickInHHeaderView()

	class: CClientDataManagerWorker
	public slots: 
	void slotContractInfoWindowResetData();
	*/
	void signalContractInfoWindowResetData();

protected:
	//overwite QWight fun
	void contextMenuEvent(QContextMenuEvent* pEvent);

	void mouseDoubleClickEvent(QMouseEvent* pEvent);

private:
	void _CreateConnect();

private:
	bool _CheckIsColumnModified(const QStringList& lstAllAvailableColums, const QStringList& lstSelectedColumns);

public:
	CContractInfoWindow* m_pContractInfoWindow;
	CCreateNewOrderDialog* m_pCreateNewOrderDialog;

private:
	QString m_strSelectedColumnsForCheck;

private:
	QAction* m_pActionAddHotQuotes;
	QAction* m_pActionRemoveHotQuotes;
	QAction* m_pActionCustomColumns;
	IconDelegate* m_pIconDelegate_Column_Change;
	int m_nColumnIndex_Change;
	CCustomColumnsDialog* m_pCustomColumnsDialog;
	CQuotesHHeaderView* m_pHorizontalHeader;
	QHeaderView* m_pVerticalHeader;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_QUOTES_TABLE_VIEW_HH__



