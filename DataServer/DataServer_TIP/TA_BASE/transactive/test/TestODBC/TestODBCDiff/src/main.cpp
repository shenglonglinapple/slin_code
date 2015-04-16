
#include <iostream>

#include "BaseLogger.h"
#include "TestManager.h"

int main()
{
	int nFunRes = 0;

	CBaseLogger::getInstance();
	std::string strLogFile = "logFile.log";
	CBaseLogger::getInstance().setlogFile(strLogFile);
	CBaseLogger::getInstance().setlogLevel(DebugInfo);

	_BaseLog(BaseLogSourceFLInfo, DebugTrace, "test log main");

	_BaseLog(BaseLogSourceFLInfo, DebugTrace, "begin do Test Manager");

	CTestManager*  pTestManager = NULL;
	pTestManager = new CTestManager();
	if (NULL != pTestManager)
	{
		delete pTestManager;
		pTestManager = NULL;
	}
	
	_BaseLog(BaseLogSourceFLInfo, DebugTrace, "end do Test Manager");

	CBaseLogger::removeInstance();

	return nFunRes;
}

