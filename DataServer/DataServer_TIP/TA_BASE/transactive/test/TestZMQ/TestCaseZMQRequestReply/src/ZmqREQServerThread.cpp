#include "ZmqREQServerThread.h"

#include "zmq.h"
#include <string.h>


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;



NS_BEGIN(TA_Base_Test) 




//////////////////////////////////////////////////////////////////////////
CZmqREQServerThread::CZmqREQServerThread(void)
{	
	BOOST_LOG_FUNCTION();	
	m_toTerminate = false;
	m_nThreadJobState = JobState_Begin;

}

CZmqREQServerThread::~CZmqREQServerThread(void)
{
	BOOST_LOG_FUNCTION();

}


void CZmqREQServerThread::run()
{
	BOOST_LOG_FUNCTION();

	m_nThreadJobState = JobState_Begin;


	while (false == m_toTerminate)
	{
		_ThreadJob();
		TA_Base_Core::CBoostThread::sleep(1000);
	}

	_ProcessUserTerminate();
}

void CZmqREQServerThread::terminate()
{
	BOOST_LOG_FUNCTION();

	m_toTerminate = true;
}


int CZmqREQServerThread::_ProcessUserTerminate()
{
	BOOST_LOG_FUNCTION();

	int nFunRes = 0;
	m_toTerminate = true;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CZmqREQServerThread::isFinishWork()
{
	BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CZmqREQServerThread::_ThreadJob()
{
	BOOST_LOG_FUNCTION();

	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		m_nThreadJobState = JobState_DoTest_01;
		break;
	case  JobState_DoTest_01:
		_DoTest_01();
		m_nThreadJobState = JobState_End;
		break;
	case JobState_End:
		break;
		TA_Base_Core::CBoostThread::sleep(1000);
	default:
		TA_Base_Core::CBoostThread::sleep(1000);
		break;

	}//switch
}

void CZmqREQServerThread::_DoTest_01()
{
 //  Socket to talk to clients  
	std::string Def_END = "EXIT";
	std::string strRecvStr;
	printf ("Server--zmq_ctx_new\n");	
	void *context = zmq_ctx_new();  
    printf ("Server--zmq_socket ZMQ_REP\n");
	void *responder = zmq_socket(context, ZMQ_REP);  
	printf ("Server--zmq_bind tcp://*:5555 \n");
    int rc = zmq_bind (responder, "tcp://*:5555");  
    
	if (0 != rc)
	{
		return;
	}
	int nIndex = 0;
    while (1) 
	{  
		TA_Base_Core::CBoostThread::sleep(1000);

        char buffer [10]; 
		memset(buffer, 0, 10);
        zmq_recv (responder, buffer, 10, 0); 
		strRecvStr = buffer;
		nIndex++;
		printf ("Server--zmq_recv:%s\n", buffer);  
        TA_Base_Core::CBoostThread::sleep(1);          //  Do some 'work'  
		printf ("Server--zmq_send:%s\n", "World");  
        zmq_send (responder, "World", 5, 0); 

		if (strRecvStr == Def_END)
		{
			break;
		}
    }  

	zmq_close (responder);  
	zmq_ctx_destroy (context);  
	context = NULL; 


}

NS_END(TA_Base_Test) 



