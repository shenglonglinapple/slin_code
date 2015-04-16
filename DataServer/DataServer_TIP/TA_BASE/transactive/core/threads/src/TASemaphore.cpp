#include "core/threads/src/TASemaphore.h"

NS_BEGIN(TA_Base_Core)



CTASemaphore::CTASemaphore( unsigned int initial )
:m_sem(initial)
{


}


CTASemaphore::~CTASemaphore()
{

}


void CTASemaphore::wait(void)
{
	m_sem.wait();
}


bool CTASemaphore::tryWait(void)
{
	m_sem.try_wait();
	return true;
}


void CTASemaphore::post(void)
{
	m_sem.post();
}


NS_END(TA_Base_Core)




