#ifndef __CLASS__SMART_HOT_QUOTES_WINDOW_H__
#define __CLASS__SMART_HOT_QUOTES_WINDOW_H__



#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>
#include <QtGui/QTabWidget>


QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QTabWidget;

QT_END_NAMESPACE

class CTreeModelQuotes;
class CQuotesTableView;
class CTreeItemQuotes;

//class IconDelegate;
class CLeftDockWidget : public QWidget
{
    Q_OBJECT


public:
    CLeftDockWidget(QWidget* parent = 0);
	~CLeftDockWidget();
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
	//IconDelegate* m_pIconDelegate;
	CQuotesTableView* m_pTableView_Quotes;

};

//QT_END_NAMESPACE

#endif//__CLASS__SMART_HOT_QUOTES_WINDOW_H__
