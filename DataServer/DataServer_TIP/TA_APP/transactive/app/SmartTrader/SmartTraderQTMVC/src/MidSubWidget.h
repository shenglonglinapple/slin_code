#ifndef __CLASS__MID_SUB_WIDGET_H__
#define __CLASS__MID_SUB_WIDGET_H__

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QScrollBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>

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
	void slotHistoryDataChanged(CHistoryDataManager* pHistoryDataManager);
	void QCPItemTracerCrossHairMouseMove(QMouseEvent *event);
private slots:
	void slotHorzScrollBarChanged(int value);
	void slotVertScrollBarChanged(int value);
	void slotQCustomPlotxAxisChanged(QCPRange range);
	void slotQCustomPlotyAxisChanged(QCPRange range);
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
	QCustomPlot* m_pCustomPlot;
	QScrollBar* m_ScrollBar_Vertical;
	QScrollBar* m_ScrollBar_Horizontal;
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
