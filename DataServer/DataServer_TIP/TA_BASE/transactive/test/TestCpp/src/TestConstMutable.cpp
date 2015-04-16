#include "TestConstMutable.h"


CTestConstMutable::CTestConstMutable( int nValue ):m_Count(nValue)
{

}

CTestConstMutable::~CTestConstMutable()
{

}

int CTestConstMutable::incr() const
{
	return ++m_Count;
}

int CTestConstMutable::decr() const
{
	return --m_Count;
}




void RunTest_CTestConstMutable::do_Test()
{
	CTestConstMutable  CTestObject(10);
	int nIncrRes = 0;
	int nDecrRes = 0;

	nIncrRes = CTestObject.incr();
	nDecrRes = CTestObject.decr();

	printf("nIncrRes=%d \n", nIncrRes);
	printf("nDecrRes=%d \n", nDecrRes);
}