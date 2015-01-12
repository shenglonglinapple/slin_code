#ifndef __CLASS__CLIENT_UI_MANAGER_H__
#define __CLASS__CLIENT_UI_MANAGER_H__

#include <QtCore/QObject>

class CClientMainWindow;

class CClientUIManager : public QObject
{
    Q_OBJECT
public:
    CClientUIManager();
	~CClientUIManager();
signals:

public slots:

public:
	void showCClientMainWindow(bool bShow);
private:
	CClientMainWindow* m_pClientMainWindow;
};


#endif//__CLASS__CLIENT_UI_MANAGER_H__
