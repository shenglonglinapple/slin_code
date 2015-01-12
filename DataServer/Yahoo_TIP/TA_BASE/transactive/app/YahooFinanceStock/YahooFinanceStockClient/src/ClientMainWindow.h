#ifndef __CLASS_CLIENT_MAIN_WINDOW_HH__
#define __CLASS_CLIENT_MAIN_WINDOW_HH__

#include <QtGui/QMainWindow>
#include <QtGui/QCloseEvent>

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


class CClientMainWindowMenuBar;
class CClientMainWindowToolBar;
class CClientMainWindowMdiArea;

class CClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CClientMainWindow(QWidget *parent = 0);
    ~CClientMainWindow();
signals:
	void signal_Exit_ClientMainWindow();
public:
	//QWidget virtual void closeEvent(QCloseEvent *);
	void closeEvent(QCloseEvent* pEvent);
private:
	void _SetupUi();

	void _CreateMenuBar();
	void _CreateToolBars();
	void _CreateMdiArea();
	void _TranslateLanguage();
private:
	CClientMainWindowMenuBar* m_pClientMainWindowMenuBar;
	CClientMainWindowToolBar* m_pClientMainWindowToolBar;
	CClientMainWindowMdiArea* m_pClientMainWindowMdiArea;
};

#endif // __CLASS_CLIENT_MAIN_WINDOW_HH__
