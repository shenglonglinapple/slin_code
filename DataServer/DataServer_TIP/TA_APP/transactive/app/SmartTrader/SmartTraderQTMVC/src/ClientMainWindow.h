#ifndef __CLASS__CLIENT_MAINWINDOW_H__
#define __CLASS__CLIENT_MAINWINDOW_H__



#include <QtGui/QMainWindow>
#include "Bar.h"


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


class CLeftDockWidget;
class CBottomDockWidget;
class CMidSubWidget;
class CMainWindowToolBar;
class CProjectLogHelper;


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
public slots:
	void slotRequestHistoryData( unsigned int nInstrumentID, enum BarType nBarType );
	void slotCurrentInstrumentChanged( unsigned int nInstrumentID );

signals:

public:
	//GUI
	CLeftDockWidget* m_pLeftDockWidget;//top
	CBottomDockWidget* m_pBottomDockWidget;
	CMidSubWidget* m_pEastMidSubWidget;//East West South North
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
	QAction* m_pAction_ReConnect;
	QAction* m_pAction_ChangePassword;
	QAction* m_pAction_Exit;

private:
	CMainWindowToolBar* m_pMainWindowToolBar;
	CProjectLogHelper* m_pProjectLogHelper;
};

//QT_END_NAMESPACE

#endif//__CLASS__CLIENT_MAINWINDOW_H__
