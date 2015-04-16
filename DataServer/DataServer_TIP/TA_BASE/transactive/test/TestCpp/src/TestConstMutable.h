#ifndef  __CLASS_TEST_CONST_MUTABLE__HH__
#define  __CLASS_TEST_CONST_MUTABLE__HH__

#include <iostream>
#include <string>
#include <stdio.h>

class CTestConstMutable
{
public:
	CTestConstMutable(int nValue);
	~CTestConstMutable();

	int incr() const;//use const
	int decr() const;//use const

private:
	mutable int m_Count;
	//int m_Count;//error C2166: l-value specifies const object
};

class RunTest_CTestConstMutable
{
//public:
//	RunTest_CTestConstMutable();
//	~RunTest_CTestConstMutable();
//	RunTest_CTestConstMutable(const RunTest_CTestConstMutable& object);
//	RunTest_CTestConstMutable& operator=(const RunTest_CTestConstMutable& object);



public:
	void do_Test();
};

#endif//__CLASS_TEST_CONST_MUTABLE__HH__