#ifndef __CLASS__MID_SUB_WIDGET_H__
#define __CLASS__MID_SUB_WIDGET_H__



#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class QCustomPlot;
class CHistoryDataManager;

class CMidSubWidget : public QWidget
{
    Q_OBJECT


public:
    CMidSubWidget(QWidget* parent = 0);
	~CMidSubWidget();

	
public slots:
	/*
	class: CClientDataManagerWorker
	signals:
	void signalHistoryDataChanged(CHistoryDataManager* pMyBarSumary);
	fun send signals: onHistoryDataDownloaded()

	class: CMidSubWidget
	public slots: 
	void slotHistoryDataChanged(CHistoryDataManager* pMyBarSumary);
	*/
	void slotHistoryDataChanged(CHistoryDataManager* pMyBarSumary);
public:
	void setupUi();
	void translateLanguage();
public:
	QSize sizeHint() const;
private:
	void _CreateAction();
	void _CreateConnect();
private:
	void doTest();
private:
	QVBoxLayout* verticalLayout;
	QCustomPlot* m_pCustomPlot;
};

//QT_END_NAMESPACE

#endif//__CLASS__MID_SUB_WIDGET_H__
