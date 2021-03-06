#ifndef __CLASS_CLIENT_MAIN_WINDOW_MDIAREA_HH__
#define __CLASS_CLIENT_MAIN_WINDOW_MDIAREA_HH__

#include <QtGui/QMdiArea>

class CUserInstrumentTableView;

class CClientMainWindowMdiArea : public QMdiArea
{
    Q_OBJECT

public:
    CClientMainWindowMdiArea(QWidget *parent = 0);
    ~CClientMainWindowMdiArea();
private:
	void _SetupUi();
	void _TranslateLanguage();
private:
	CUserInstrumentTableView* m_pUserInstrumentTableView;

};

#endif // __CLASS_CLIENT_MAIN_WINDOW_MDIAREA_HH__
