#ifndef __CLASS__CONTRACT_INFO_WINDOW_H__
#define __CLASS__CONTRACT_INFO_WINDOW_H__




#include <QtCore/QModelIndex>
#include <QtGui/QMainWindow>


QT_BEGIN_NAMESPACE
class QWidget;
class QVBoxLayout;
class QTreeView;
QT_END_NAMESPACE


class CTreeModelContract;
class CTreeItemContract;


class CContractInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    CContractInfoWindow(QWidget* parent = 0);
	~CContractInfoWindow();
public:
	void setupUi();
	void translateLanguage();


public slots:
	/*
	class: CClientDataManagerWorker
	signals:
	void signalContractInfoChanged(CTreeItemContract* pTreeItem);
	fun send signals: onInstrumentDownloaded()

	class: CContractInfoMainWindow
	public slots: 
	void slotContractInfoChanged(CTreeItemContract* pTreeItem);
	*/
	void slotContractInfoChanged(CTreeItemContract* pTreeItem);

	void slotTreeViewDoubleClick(const QModelIndex & index);

signals: 
	/*
	class: CContractInfoWindow
	signals:
	void signalAddContractToSmartQuotes(unsigned int nInstrumentID);
	fun send signals: slotTreeViewDoubleClick()

	class: CClientDataManagerWorker
	public slots: 
	void slotAddContractToSmartQuotes(unsigned int nInstrumentID);
	*/
	void signalAddContractToSmartQuotes(unsigned int nInstrumentID);
private:
	void _CreateConnect();
private:
	CTreeModelContract* m_pTreeModel;

private:
	QWidget* m_pWidget_Central;
	QVBoxLayout* m_pVBoxLayout;
	QTreeView* m_pTreeView_ContractInfo;

};

//QT_END_NAMESPACE


#endif//__CLASS__CONTRACT_INFO_WINDOW_H__
