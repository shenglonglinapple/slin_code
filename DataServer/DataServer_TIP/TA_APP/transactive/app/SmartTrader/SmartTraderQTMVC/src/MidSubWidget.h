#ifndef __CLASS__MID_SUB_WIDGET_H__
#define __CLASS__MID_SUB_WIDGET_H__



#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class CHistoryDataManager;
class QCPStatisticalBox;
class QCustomPlot;
class CMidSubDrawHelper;

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
	void signalHistoryDataChanged(CHistoryDataManager* pHistoryDataManager);
	fun send signals: onHistoryDataDownloaded()

	class: CMidSubWidget
	public slots: 
	void slotHistoryDataChanged(CHistoryDataManager* pHistoryDataManager);
	*/
	void slotHistoryDataChanged(CHistoryDataManager* pHistoryDataManager);
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
	CMidSubDrawHelper* m_pMidSubDrawHelper;
};

//QT_END_NAMESPACE

#endif//__CLASS__MID_SUB_WIDGET_H__
