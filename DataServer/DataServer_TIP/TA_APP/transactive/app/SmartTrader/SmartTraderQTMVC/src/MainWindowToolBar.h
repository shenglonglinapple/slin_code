#ifndef __CLASS_MAIN_WINDOW_TOOLBAR_HH__
#define __CLASS_MAIN_WINDOW_TOOLBAR_HH__

#include <QtCore/QObject>
#include <QtGui/QToolBar>
#include <QtGui/QActionGroup>
#include "Bar.h"

class CProjectLogHelper;

class CMainWindowToolBar : public QToolBar 
{ 
	Q_OBJECT
public: 
	CMainWindowToolBar(const QString &title, QWidget *parent = 0);
	CMainWindowToolBar(QWidget *parent = 0); 
	virtual ~CMainWindowToolBar(); 

public slots:
	void slotActionS5Triggered();
	void slotActionM1Triggered();
	void slotActionM5Triggered();
	void slotActionM15Triggered();
	void slotActionM30Triggered();
	void slotActionH1Triggered();
	void slotActionD1Triggered();
	void slotActionW1Triggered();
	void slotActionMNTriggered();
signals:
	void signalRequestHistoryData( unsigned int nInstrumentID, enum BarType nBarType );
public:
	void setCurrentInstrumentID(unsigned int nInstrumentID);
	unsigned int getCurrentInstrumentID();
	void setHistoryBarType( enum BarType nBarType, const QString& strBarType );
	enum BarType getHistoryBarType();
private:
	void _CreateActions();
	void _AddAction();
	void _CreateConnect();
	void translateLanguage();
private:
	QActionGroup* m_pAction_Group_BarType;
private:
	QAction* m_pAction_BarInfo_S5;
	QAction* m_pAction_BarInfo_M1;
	QAction* m_pAction_BarInfo_M5;
	QAction* m_pAction_BarInfo_M15;
	QAction* m_pAction_BarInfo_M30;
	QAction* m_pAction_BarInfo_H1;
	QAction* m_pAction_BarInfo_D1;
	QAction* m_pAction_BarInfo_W1;
	QAction* m_pAction_BarInfo_MN;
private:
	CProjectLogHelper* m_pProjectLogHelper;
private:
	unsigned int m_nCurrentInstrumentID;
	enum BarType m_nCurrentBarType;

}; 





#endif//__CLASS_NODE_HH__



