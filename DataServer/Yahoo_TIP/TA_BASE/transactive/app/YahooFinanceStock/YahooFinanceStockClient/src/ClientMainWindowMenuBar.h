#ifndef __CLASS_CLIENT_MAIN_WINDOW_MENUBAR_HH__
#define __CLASS_CLIENT_MAIN_WINDOW_MENUBAR_HH__

#include <QtGui/QMenuBar>

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

class CClientLoginWindow;

class CClientMainWindowMenuBar : public QMenuBar
{
    Q_OBJECT

public:
    CClientMainWindowMenuBar(QWidget *parent = 0);
    ~CClientMainWindowMenuBar();
private slots:
	void slotActionConnectToServerTriggered();
private:
	void _CreateMenus();
	void _CreateActions();
	void _TranslateLanguage();
	void _CreateConnect();
private:
	QMenu* m_Menu_Files;
private:
	QAction* m_pAction_ConnectToServer;
private:
	CClientLoginWindow* m_pClientLoginWindow;
};

#endif // __CLASS_CLIENT_MAIN_WINDOW_MENUBAR_HH__
