#ifndef __CLASS__SIGNALE_SLOT_MANAGER_H__
#define __CLASS__SIGNALE_SLOT_MANAGER_H__


#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>


class CClientDataManager;
class CUserInstrumentTableView;

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
	CClientDataManager* m_pRefSignal_DataChange_UserInstrument;
	CUserInstrumentTableView* m_pRefSlot_DataChange_UserInstrument;
public:
	void set_Signal_DataChange_UserInstrument( CClientDataManager* pRefSignal);
	void set_Slot_DataChange_UserInstrument(CUserInstrumentTableView* pRefSlot);
signals:
	void signal_DataChange_UserInstrument();
public slots:
	void slot_DataChange_UserInstrument();
public:
	void emit_DataChange_UserInstrument();
	//////////////////////////////////////////////////////

};

//QT_END_NAMESPACE

#endif//__CLASS__SIGNALE_SLOT_MANAGER_H__
