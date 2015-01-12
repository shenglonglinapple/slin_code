#ifndef __CLASS_CLIENT_MAIN_WINDOW_TOOLBAR_HH__
#define __CLASS_CLIENT_MAIN_WINDOW_TOOLBAR_HH__

#include <QtCore/QObject>
#include <QtGui/QToolBar>
#include <QtGui/QActionGroup>

class CMyBarTypeHeler;

class CClientMainWindowToolBar : public QToolBar 
{ 
	Q_OBJECT
public: 
	CClientMainWindowToolBar(QWidget *parent = 0); 
	virtual ~CClientMainWindowToolBar(); 
signals:
public slots:

public:

}; 





#endif//__CLASS_CLIENT_MAIN_WINDOW_TOOLBAR_HH__



