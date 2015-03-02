#ifndef  __DEF__PROJECT_COMMON_DEF_H_
#define  __DEF__PROJECT_COMMON_DEF_H_

/*
typedef signed char qint8;  
typedef unsigned char quint8;
typedef short qint16;        
typedef unsigned short quint16;
typedef int qint32;            
typedef unsigned int quint32;  
typedef __int64 qint64;        
typedef unsigned __int64 quint64;
typedef qint64 qlonglong;
typedef quint64 qulonglong;
*/



enum TimeBaseSecond
{	
	TIME_BASE_S_1S          = 1,
	TIME_BASE_S_5S          = 5 * TIME_BASE_S_1S,

	TIME_BASE_S_1MIN		= 60   * TIME_BASE_S_1S,
	TIME_BASE_S_5MIN		= 5   * TIME_BASE_S_1MIN,
	TIME_BASE_S_15MIN		= 15   * TIME_BASE_S_1MIN,
	TIME_BASE_S_30MIN		= 30   * TIME_BASE_S_1MIN,

	TIME_BASE_S_1HOUR		= 60   * TIME_BASE_S_1MIN,
	TIME_BASE_S_1DAY		= 24   * TIME_BASE_S_1HOUR,
	TIME_BASE_S_1MON		= 30   * TIME_BASE_S_1DAY,
	TIME_BASE_S_1YEAR		= 365   * TIME_BASE_S_1DAY,

};

#endif  // __DEF__PROJECT_COMMON_DEF_H_











