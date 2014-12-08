//#include "vld.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"wldap32.lib")
#pragma comment(lib,"libcurld.lib")
#pragma comment(lib,"log4cppD.lib")
#pragma comment(lib,"ws2_32.lib")//winsock2

#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"QtCored4.lib")
#pragma comment(lib,"QtGuid4.lib")
#pragma comment(lib,"QtSqld4.lib")

//////////////////////////////////////////////////////////////////////////

#include "BaseException.h"

#include "YahuoReqAck.h"
#include "YahuoRealTimeReqAck.h"
#include "YahuoHistoryReqAck.h"
#include "InitDBByYahuoData.h"

#include "ConfigInfo.h"
#include "Log4cppLogger.h"
//////////////////////////////////////////////////////////////////////////

void testCYahuoRealTimeReqAck()
{
	CYahuoRealTimeReqAck objCYahuoRealTimeReqAck;
	objCYahuoRealTimeReqAck.test_CYahuoRealTimeReqAck();

}

void testCYahuoHistoryReqAck()
{
	CYahuoHistoryReqAck objCYahuoHistoryReqAck;
	objCYahuoHistoryReqAck.test_CYahuoHistoryReqAck();
}

void testInitDBByYahuoData()
{
	CConfigInfo::getInstance();
	CInitDBByYahuoData::getInstance();

	CInitDBByYahuoData::getInstance().doWork_initTotalStocksYahuoDataToFile();
	CInitDBByYahuoData::getInstance().doWork_ProcessFileToSQliteDb();

	CInitDBByYahuoData::removeInstance();
	CConfigInfo::removeInstance();	
}


int main()
{
	CLog4cppLogger::getInstance();
	CLog4cppLogger::getInstance().initLog();
	CLog4cppLogger::getInstance().testLog();

	//testCYahuoRealTimeReqAck();
	//testCYahuoHistoryReqAck();
	testInitDBByYahuoData();
	

	CLog4cppLogger::removeInstance();
	return 0;
}