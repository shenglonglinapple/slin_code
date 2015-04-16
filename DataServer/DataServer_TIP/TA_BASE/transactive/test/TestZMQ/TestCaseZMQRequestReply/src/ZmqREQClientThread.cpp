#include "ZmqREQClientThread.h"

#include "zmq.h"
#include <string.h>


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;



NS_BEGIN(TA_Base_Test) 




//////////////////////////////////////////////////////////////////////////
CZmqREQClientThread::CZmqREQClientThread(void)
{	
	BOOST_LOG_FUNCTION();	
	m_toTerminate = false;
	m_nThreadJobState = JobState_Begin;

}

CZmqREQClientThread::~CZmqREQClientThread(void)
{
	BOOST_LOG_FUNCTION();

}


void CZmqREQClientThread::run()
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

void CZmqREQClientThread::terminate()
{
	BOOST_LOG_FUNCTION();

	m_toTerminate = true;
}


int CZmqREQClientThread::_ProcessUserTerminate()
{
	BOOST_LOG_FUNCTION();

	int nFunRes = 0;
	m_toTerminate = true;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CZmqREQClientThread::isFinishWork()
{
	BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CZmqREQClientThread::_ThreadJob()
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

void CZmqREQClientThread::_DoTest_01()
{
	//printf ("Connecting to hello world server...\n");  
	std::string Def_END = "EXIT";
	std::string strRecvStr;

	printf ("Client--zmq_ctx_new\n");	
	void *context = zmq_ctx_new ();  
	printf ("Client--zmq_socket ZMQ_REQ\n");	
	void *requester = zmq_socket (context, ZMQ_REQ);  
	printf ("Client--zmq_connect tcp://localhost:5555\n");	
	zmq_connect (requester, "tcp://localhost:5555");  

	int request_nbr = 0;  
	while (1)
	{
		TA_Base_Core::CBoostThread::sleep(1000);

		char buffer [10];  
		memset(buffer, 0, 10);
		printf ("Client--zmq_send:%s request_nbr=%d\n", "Hello", request_nbr);	
		zmq_send (requester, "Hello", 5, 0);  
		request_nbr++;
		zmq_recv (requester, buffer, 10, 0);  
		printf ("Client--zmq_recv:%s request_nbr=%d\n",buffer, request_nbr);
		if (request_nbr == 10)
		{
			zmq_send (requester, Def_END.c_str(), Def_END.length(), 0);  
			break;
		}
	}  
	zmq_close (requester);  
	zmq_ctx_destroy (context);  

}

NS_END(TA_Base_Test) 



