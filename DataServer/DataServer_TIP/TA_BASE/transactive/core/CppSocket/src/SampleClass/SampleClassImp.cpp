#include "SampleClassImp.h"





CSampleClassImp::CSampleClassImp()
{
	m_nTotal = 0;

}

CSampleClassImp::~CSampleClassImp()
{

}

int CSampleClassImp::testFun( int nParamOne )
{
	m_nTotal += nParamOne;
	return m_nTotal;
}





