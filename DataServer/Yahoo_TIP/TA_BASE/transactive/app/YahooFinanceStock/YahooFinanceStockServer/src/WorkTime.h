#ifndef __CLASS_WORK_TIME_H__
#define __CLASS_WORK_TIME_H__

#include <time.h>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CAWorkTime
{
public:
	CAWorkTime();
	virtual ~CAWorkTime(void); 
public:
	//set begin work 
	virtual void workBegin()= 0; 
	//set end work
	//return WorkTime : end work time - begin work time  (millsecs)
	virtual qint64 workEnd()= 0; 

	//WorkTime valuse is end work time - begin work time
	virtual qint64 getWorkTime()= 0;//for log time sprintf("%llu or %lld")

	//NotWorkTime valuse is now time - begin work time
	virtual qint64 getNotworkTime()= 0;//for monitor 


public:
	virtual qint64 getDiffTime(const QDateTime& timeBegin, const QDateTime& timeEnd);

protected:
	qint32  m_nWorkTimeCode;
	//begin work time
	QDateTime m_fTimeWorkBegin;	
	//end work time
	QDateTime m_fTimeWorkEnd;		
	//WorkTime valuse is end work time - begin work time
	qint64		 m_nWorkTime;//millsecs	 
	//NotWorkTime valuse is now time - begin work time
	qint64         m_nNotWorkTime;
	//set begin work 
	bool         m_bSetWorkBegin;
	//set end work 
	bool         m_bSetWorkEnd;


};

class CWorkTimeLock	: public  CAWorkTime
{
public:
	CWorkTimeLock(qint32 nWorkTimeCode);
	~CWorkTimeLock(void); 
public:	
	virtual void workBegin(); 
	virtual qint64 workEnd();
	virtual qint64 getWorkTime();   //for log time 
	virtual qint64 getNotworkTime(); //for monitor	
private:
	QMutex m_lockWorkTime;
};

class CWorkTimeNoLock	: public  CAWorkTime
{
public:
	CWorkTimeNoLock(qint32 nWorkTimeCode);
	~CWorkTimeNoLock(void); 
public:	
	virtual void workBegin(); 
	virtual qint64 workEnd();
	virtual qint64 getWorkTime();   //for log time 
	virtual qint64 getNotworkTime(); //for monitor	
};



#endif//__CLASS_WORK_TIME_H__



