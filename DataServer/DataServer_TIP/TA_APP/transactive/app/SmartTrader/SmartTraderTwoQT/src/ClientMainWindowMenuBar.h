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


class CClientMainWindowMenuBar : public QMenuBar
{
    Q_OBJECT

public:
    CClientMainWindowMenuBar(QWidget *parent = 0);
    ~CClientMainWindowMenuBar();
private:
	void _CreateMenus();
	void _CreateActions();
	void _TranslateLanguage();

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

};

#endif // __CLASS_CLIENT_MAIN_WINDOW_MENUBAR_HH__
