#ifndef __CLASS__SIGNALE_SLOT_MANAGER_H__
#define __CLASS__SIGNALE_SLOT_MANAGER_H__


#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CClientWorkerManager;
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



};

//QT_END_NAMESPACE

#endif//__CLASS__SIGNALE_SLOT_MANAGER_H__
