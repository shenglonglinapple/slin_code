#ifndef __CLASS__MID_SUB_WIDGET_H__
#define __CLASS__MID_SUB_WIDGET_H__



#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtCore/QList>

#include "Bar.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class CHistoryDataManager;
class QCPStatisticalBox;
class QCustomPlot;
class CMidSubDrawHelper;
class QCPItemTracerCrossHair;
class QCPAxisRect;
class QCPMarginGroup;

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


	void QCPItemTracerCrossHairMouseMove(QMouseEvent *event);

public:
	void setupUi();
	void translateLanguage();
public:
	QSize sizeHint() const;
public:
	void setCurrentInstrumentID(unsigned int nInstrumentID);
	unsigned int getCurrentInstrumentID();
	void setHistoryBarType(enum BarType nBarType);
	enum BarType getHistoryBarType();
private:
	void _CreateAction();
	void _CreateConnect();
private:
	void doTest();
	void _ReSetCustomPlot();
private:
	QVBoxLayout* verticalLayout;
	QCustomPlot* m_pCustomPlot;
	CMidSubDrawHelper* m_pMidSubDrawHelper;
	QCPItemTracerCrossHair* m_pQCPItemTracerCrossHairTop;
	QCPItemTracerCrossHair* m_pQCPItemTracerCrossHairBottom;
	QCPAxisRect* m_pAxisRectTop;
	QCPAxisRect* m_pAxisRectBottom;
	QCPMarginGroup* m_pMarginGroup;
private:
	unsigned int m_nCurrentInstrumentID;
	enum BarType m_nCurrentBarType;

};

//QT_END_NAMESPACE

#endif//__CLASS__MID_SUB_WIDGET_H__
