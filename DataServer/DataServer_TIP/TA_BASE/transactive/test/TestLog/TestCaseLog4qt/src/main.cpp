//#include "vld.h"
#include <iostream>

#include "ProjectTestManager.h"

#pragma comment(lib, "Ws2_32.lib")//winsock2
//Ws2_32.lib

int main( int argc, char* argv[] )
{

	CProjectTestManager* pTestManager = new CProjectTestManager();
	
	pTestManager->doTest();

	
	if (NULL != pTestManager)
	{
		delete pTestManager;
		pTestManager = NULL;
	}

	return 0;
}










