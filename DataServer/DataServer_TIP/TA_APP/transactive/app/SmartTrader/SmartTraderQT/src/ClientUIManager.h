#ifndef __CLASS__CLIENT_UI_MANAGER_H__
#define __CLASS__CLIENT_UI_MANAGER_H__



#include <QtCore/QObject>




//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CClientLoginWindow;
class CClientMainWindow;

class CClientUIManager : public QObject
{
    Q_OBJECT
public:
    CClientUIManager();
	~CClientUIManager();
public slots:
	void slotLoginToServerRes(int nLoginToServerRes);

public:
	void showClientLoginWindow(bool bShow);

private:
	void _CreateConnect();

private:
	CClientLoginWindow* m_pClientLoginDialog;
	CClientMainWindow* m_pClientMainWindow;

};

//QT_END_NAMESPACE

#endif//__CLASS__CLIENT_UI_MANAGER_H__
