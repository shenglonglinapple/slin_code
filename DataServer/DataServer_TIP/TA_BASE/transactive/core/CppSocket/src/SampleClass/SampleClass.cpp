#include "SampleClass.h"
#include "SampleClassImp.h"



CSampleClass::CSampleClass()
{
	m_pImp = NULL;
	m_pImp = new CSampleClassImp();

}

CSampleClass::~CSampleClass()
{
	if (NULL != m_pImp)
	{
		delete m_pImp;
		m_pImp = NULL;
	}
}

int CSampleClass::testFun( int nParamOne )
{
	return m_pImp->testFun(nParamOne);
}

