#ifndef __CLASS__TEST_MY_THREAD_MANAGER_H__
#define __CLASS__TEST_MY_THREAD_MANAGER_H__

#include <QtCore/QObject>

class CTestMyThreadManager : public QObject
{
    Q_OBJECT
public:
    CTestMyThreadManager();
	~CTestMyThreadManager();
public:
	void do_test_mythread_1();
	void do_test_mythread_2();
	void _InitLog();
	void _UnInitLog();
};


#endif//__CLASS__TEST_MY_THREAD_MANAGER_H__
