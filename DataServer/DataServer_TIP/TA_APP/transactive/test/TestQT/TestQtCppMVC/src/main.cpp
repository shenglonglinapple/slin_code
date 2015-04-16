//qt app
#include <QtGui/QApplication>
#include "ProjectCommonDef.h"
#include "TestCaseMVC.h"


int main(int argc, char *argv[])
{
	int nFunRes = 0;
	QApplication app(argc, argv);

	//////////////////////////////////////////////////////////////////////////
	//TA_Base_App::CClientTestCase clientTestCase;
	//clientTestCase.test_get_exchange_info();

	TA_Base_App::CTestCaseMVC testCaseMVC;
	testCaseMVC.test_TreeMode_QTDemo();






	//////////////////////////////////////////////////////////////////////////

	nFunRes = app.exec();

	
	return 0;
}




