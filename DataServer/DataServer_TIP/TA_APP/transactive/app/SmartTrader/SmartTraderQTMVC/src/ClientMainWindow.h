#ifndef __CLASS__CLIENT_MAINWINDOW_H__
#define __CLASS__CLIENT_MAINWINDOW_H__



#include <QtGui/QMainWindow>



QT_BEGIN_NAMESPACE
class QFormLayout;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;
class QMdiArea;
class QToolBar;
class QAction;
QT_END_NAMESPACE




class CClientDataManagerWorker;
class CLeftDockWidget;

class CClientMainWindow : public QMainWindow
{
    Q_OBJECT


public:
    CClientMainWindow(QWidget* parent = 0);
	~CClientMainWindow();
public:
	void setupUi();
	void translateLanguage();

private:
	void _CreateActions();
	void _CreateMenus();
	void _CreateToolBars();

	void _CreateConnect();
	
public:
	//Data
	CClientDataManagerWorker* m_pClientDataManagerWorker;

public:
	//GUI
	CLeftDockWidget* m_pLeftDockWidget;//top
private:
	QMdiArea* m_pMdiArea;

private:
	QMenu* m_Menu_Files;
	QMenu* m_Menu_View;
	QMenu* m_Menu_Insert;
	QMenu* m_Menu_Tools;
	QMenu* m_Menu_Window;
	QMenu* m_Menu_Help;

private:
	QToolBar* m_ToolBar_BarInfo;
private:
	QAction* m_pAction_BarInfo_M1;
	QAction* m_pAction_BarInfo_M5;
	QAction* m_pAction_BarInfo_M15;
	QAction* m_pAction_BarInfo_M30;
	QAction* m_pAction_BarInfo_H1;
	QAction* m_pAction_BarInfo_D1;
	QAction* m_pAction_BarInfo_W1;
	QAction* m_pAction_BarInfo_MN;
private:
	QAction* m_pAction_ReConnect;
	QAction* m_pAction_ChangePassword;
	QAction* m_pAction_Exit;

	
};

//QT_END_NAMESPACE

#endif//__CLASS__CLIENT_MAINWINDOW_H__
