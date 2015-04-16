#ifndef __CLASS_MY_THREAD_TEST_H__
#define __CLASS_MY_THREAD_TEST_H__

#include <QtCore/QObject>

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QThread>
#include <QtCore/QTimer>

//class CMyThreadTest : public QObject
class CMyThreadTest : public QThread
{
	Q_OBJECT
private:
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_End,
	};
public:
	CMyThreadTest(QObject *parent = 0);
	virtual ~CMyThreadTest();
public:
	void my_start();
	void my_terminateAndWait();
	bool my_isFinishWork();
public:
	void my_msleep(int mseconds);
public slots:
	void slot_my_thread_run();
private:
	void _ThreadJob();
	void _ProcessUserTerminate(); 
private:
	QThread* m_pThread;
	bool m_toTerminate;
	EThreadJobState  m_nThreadJobState;
};



#endif //__CLASS_MY_THREAD_TEST_H__
