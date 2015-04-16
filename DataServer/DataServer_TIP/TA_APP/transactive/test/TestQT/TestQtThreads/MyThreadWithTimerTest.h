#ifndef __CLASS_MY_THREAD_WITH_TIMER_TEST_H__
#define __CLASS_MY_THREAD_WITH_TIMER_TEST_H__

#include <QtCore/QObject>

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QThread>
#include <QtCore/QTimer>

class CMyThreadWithTimerTest : public QObject
{
	Q_OBJECT
public:
	CMyThreadWithTimerTest(QObject *parent = 0);
	virtual ~CMyThreadWithTimerTest();
signals:
	void signalDoSomething();
public slots:
	void trigger();
	void slotDoSomething();
private:
	QTimer m_Timer;
	QThread* m_pThread;
};



#endif //__CLASS_MY_THREAD_WITH_TIMER_TEST_H__
