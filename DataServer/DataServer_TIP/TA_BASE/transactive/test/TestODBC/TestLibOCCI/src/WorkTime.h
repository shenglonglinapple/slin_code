#if !defined(__C_WORKTIME_HH__)
#define __C_WORKTIME_HH__

#include <iostream>
#include <fstream>
#include <list> 

 
#include <stdio.h>
#include <sys/timeb.h>
#include <stdlib.h>






/*
BigInt64
UBigInt64

BigInt32
UBigInt32
*/

//
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64		BigInt64;//%I64d
typedef signed __int64			UBigInt64;// %I64u ¡¢ %I64o ¡¢ %I64x

#else
typedef unsigned long long		BigInt64;
typedef signed long long		UBigInt64;
#endif



#ifndef __linux__
typedef long long				BigInt32;//LLONG_MAX LLONG_MIN
typedef unsigned long long		UBigInt32;//ULLONG_MAX 0 
#else 
typedef long					BigInt32;//LONG_MIN LONG_MAX
typedef unsigned long			UBigInt32;//0   ULONG_MAX
#endif



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
	virtual UBigInt64 workEnd()= 0; 

	//WorkTime valuse is end work time - begin work time
	virtual UBigInt64 getWorkTime()= 0;//for log time sprintf("%llu or %lld")

	//NotWorkTime valuse is now time - begin work time
	virtual UBigInt64 getNotworkTime()= 0;//for monitor 


public:
	virtual std::string getCurrentTime(struct timeb* pfbtime);
	virtual UBigInt64 getDiffTime(struct timeb* pfbtimeBegin, struct timeb* pfbtimeEnd);//ms

protected:
	int  m_nWorkTimeCode;
	//begin work time
	struct timeb m_fTimeWorkBegin;	
	//end work time
	struct timeb m_fTimeWorkEnd;		
	//WorkTime valuse is end work time - begin work time
	UBigInt64		 m_nWorkTime;//millsecs	 
	//NotWorkTime valuse is now time - begin work time
	UBigInt64         m_nNotWorkTime;
	//set begin work 
	bool         m_bSetWorkBegin;
	//set end work 
	bool         m_bSetWorkEnd;


};


class CWorkTimeNoLock	: public  CAWorkTime
{
public:
	CWorkTimeNoLock(int nWorkTimeCode);
	~CWorkTimeNoLock(void); 
public:	
	virtual void workBegin(); 
	virtual UBigInt64 workEnd();
	virtual UBigInt64 getWorkTime();   //for log time 
	virtual UBigInt64 getNotworkTime(); //for monitor	
};





#endif//__C_WORKTIME_HH__



