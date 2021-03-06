#ifndef __CLASS__CLIENT_MANAGER_H__
#define __CLASS__CLIENT_MANAGER_H__



#include <QtCore/QObject>




//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CClientLoginDialog;
class CClientMainWindow;

class CClientManager : public QObject
{
    Q_OBJECT
public:
    CClientManager();
	~CClientManager();
public slots:
	void slotLoginToServerResult(int nLoginResust);
private:
	void _CreateConnect();
private:
	CClientLoginDialog* m_pClientLoginDialog;
	CClientMainWindow* m_pClientMainWindow;
};

//QT_END_NAMESPACE

#endif//__CLASS__CLIENT_WINDOW_H__
