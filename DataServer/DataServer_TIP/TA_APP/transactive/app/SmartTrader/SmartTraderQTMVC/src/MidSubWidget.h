#ifndef __CLASS__MID_SUB_WIDGET_H__
#define __CLASS__MID_SUB_WIDGET_H__



#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtCore/QList>
#include "Bar.h"
#include "qcp.h"

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
class CProjectLogHelper;



class CMidSubWidget : public QWidget
{
    Q_OBJECT
public:
	enum EHistoryDataStates
	{
		EHistoryDataStates_Ready,
		EHistoryDataStates_SentReqest,
		EHistoryDataStates_WaitACK,
		EHistoryDataStates_GetACK,		
		EHistoryDataStates_End,
	};

public:
    CMidSubWidget(QWidget* parent = 0);
	~CMidSubWidget();
	
public slots:
	void slotHistoryDataChanged(unsigned int nInstrumentID );
	void QCPItemTracerCrossHairMouseMove(QMouseEvent *event);
	void slotTopxAxisChanged(QCPRange range);
	void slotBottomxAxisChanged(QCPRange range);

public:
	void setupUi();
	void translateLanguage();
public:
	QSize sizeHint() const;
public:
	void setCurrentInstrumentID(unsigned int nInstrumentID);
	unsigned int getCurrentInstrumentID();
	void setHistoryBarType( enum BarType nBarType, const QString& strBarType );

private:
	void _CreateAction();
	void _CreateConnect();
private:
	void _ReSetCustomPlot();
	void _InitUIData();
private:
	QCustomPlot* m_pCustomPlot;
	CMidSubDrawHelper* m_pMidSubDrawHelper;
	QCPItemTracerCrossHair* m_pQCPItemTracerCrossHairTop;
	QCPItemTracerCrossHair* m_pQCPItemTracerCrossHairBottom;
	QCPAxisRect* m_pAxisRectTop;
	QCPAxisRect* m_pAxisRectBottom;
	
private:
	CProjectLogHelper* m_pProjectLogHelper;
	unsigned int m_nInstrumentID;
	enum BarType m_nBarType;
	enum EHistoryDataStates  m_nEHistoryDataStates;
	int m_nPage;
};

//QT_END_NAMESPACE

#endif//__CLASS__MID_SUB_WIDGET_H__
