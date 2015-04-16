#ifndef __CLASS_MY_QT_THREAD__HH__
#define __CLASS_MY_QT_THREAD__HH__

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QTimer>

class CMyQtThread : public QThread
{
	Q_OBJECT
public:
	typedef enum enThreadStates
	{
		THREAD_STATE_NEW,

		THREAD_STATE_RUNNING,
		THREAD_STATE_TERMINATED,

		THREAD_STATE_FINISH,
		THREAD_STATE_UNKNOWN                                     
	}EThreadStates;
public:
	CMyQtThread(); 
	virtual ~CMyQtThread();
	virtual void run() = 0;	
	virtual void terminate() = 0;

public slots:
	void  runThread(); 
public:
	void start();
	void terminateAndWait();
  

public:	
	unsigned int getId() const;
	void my_msleep(unsigned int milliSeconds);
	static unsigned int getCurrentThreadId();
public:	
	EThreadStates getCurrentState() const;
private: 
	QThread*  m_thread; 

public:
	EThreadStates    m_ThreadState;
	int             m_nThreadID;
};

//QT_END_NAMESPACE

#endif  // __CLASS_MY_QT_THREAD__HH__



