#ifndef __CLASS__SIGNALE_SLOT_MANAGER_H__
#define __CLASS__SIGNALE_SLOT_MANAGER_H__


#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CClientDataManager;
class CClientMainWindow;

class CSignalSlotManager : public QObject
{
	Q_OBJECT
public:
	static CSignalSlotManager& getInstance();
	static void removeInstance();

private:
	static CSignalSlotManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CSignalSlotManager(void);
	~CSignalSlotManager(void);

//////////////////////////////////////////////////////
private:
	CClientDataManager* m_pRefSignal_ShownMessage;
	CClientMainWindow* m_pRefSlot_ShownMessage;
public:
	void set_Signal_ShownMessage( CClientDataManager* pRefSignal);
	void set_Slot_ShownMessage(CClientMainWindow* pRefSlot);
signals:
	void signal_ShownMessage(QString strMessage);
public slots:
	void slot_ShownMessage(QString strMessage);
public:
	void emit_ShownMessage(QString strMessage);
//////////////////////////////////////////////////////


};

//QT_END_NAMESPACE

#endif//__CLASS__SIGNALE_SLOT_MANAGER_H__
