#ifndef __CLASS__BOTTOM_DOCK_WIDGET_H__
#define __CLASS__BOTTOM_DOCK_WIDGET_H__



#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>


QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class CTreeModelQuotes;
class CTreeItemQuotes;

class CBottomDockWidget : public QWidget
{
    Q_OBJECT


public:
    CBottomDockWidget(QWidget* parent = 0);
	~CBottomDockWidget();
public:
	void setupUi();
	void translateLanguage();
public:
	QSize sizeHint() const;

protected:

	
public slots:
	/*
	class: CClientDataManagerWorker
	signals:
	void signalQuotesInfoChanged(CTreeItemQuotes* pTreeItem);
	fun send signals: slotAddContractToSmartQuotes()

	class: CSmartHotQuotesWindow
	public slots: 
	void slotQuotesInfoChanged(CTreeItemQuotes* pTreeItem);
	*/
	void slotQuotesInfoChanged(CTreeItemQuotes* pTreeItem);

signals:


private:
	void _CreateAction();
	void _CreateConnect();
private:
	QVBoxLayout* m_pVBoxLayout;
	QTabWidget* m_pTabWidget;
private:
	CTreeModelQuotes* m_pTreeModelQuotes;
public:
	QTableView* m_pTableView_Order;

};

//QT_END_NAMESPACE

#endif//__CLASS__BOTTOM_DOCK_WIDGET_H__
