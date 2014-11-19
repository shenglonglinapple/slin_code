#ifndef __CLASS_MAIN_WINDOW_TOOLBAR_HH__
#define __CLASS_MAIN_WINDOW_TOOLBAR_HH__


#include <QtGui/QToolBar>


class CMainWindowToolBar : public QToolBar 
{ 
public: 
	CMainWindowToolBar(const QString &title, QWidget *parent = 0);
	CMainWindowToolBar(QWidget *parent = 0); 
	virtual ~CMainWindowToolBar(); 

private:
	void _CreateActions();
	void _AddAction();
	void translateLanguage();
private:
	QAction* m_pAction_BarInfo_M1;
	QAction* m_pAction_BarInfo_M5;
	QAction* m_pAction_BarInfo_M15;
	QAction* m_pAction_BarInfo_M30;
	QAction* m_pAction_BarInfo_H1;
	QAction* m_pAction_BarInfo_D1;
	QAction* m_pAction_BarInfo_W1;
	QAction* m_pAction_BarInfo_MN;

}; 





#endif//__CLASS_NODE_HH__



