#ifndef __CLASS_MY_QT_THREAD__HH__
#define __CLASS_MY_QT_THREAD__HH__

#include <QtCore/QObject>
#include <QtCore/QThread>

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

	typedef enum enWorkerStates
	{
		WORK_STATE_BEGIN,
		WORK_STATE_WORKING,
		WORK_STATE_END
	}EWorkerStates;
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
	static unsigned int getCurrentThreadId();
public:	
	EThreadStates getCurrentState() const;
private: 
	QThread* m_pQThread; 
private:
	EThreadStates m_ThreadState;	
	unsigned int m_nThreadID;
protected:
	EWorkerStates m_WorkerState;
};

//QT_END_NAMESPACE

#endif  // __CLASS_MY_QT_THREAD__HH__



