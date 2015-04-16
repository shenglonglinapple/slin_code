#include <iostream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include "TestXMLFileParser.h"


boost::mutex g_mutexMainRun;
boost::condition_variable g_conditionMainRun;


int main( int argc, char* argv[] )
{

	CTestXMLFileParser TestXMLFileParser;
	TestXMLFileParser.doTestConfigConnectionString();

	//sleep
	{	
		boost::mutex::scoped_lock lock(g_mutexMainRun);
		g_conditionMainRun.wait(lock);
	}



	return 0;
}










