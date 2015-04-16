//#include "vld.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
//#define CURL_STATICLIB
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"wldap32.lib")
#pragma comment(lib,"libcurld.lib")
#pragma comment(lib,"log4cppD.lib")
#pragma comment(lib,"ws2_32.lib")//winsock2

#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"QtCored4.lib")
#pragma comment(lib,"QtGuid4.lib")
#pragma comment(lib,"QtSqld4.lib")
#pragma comment(lib,"QtNetworkd4.lib")



//////////////////////////////////////////////////////////////////////////

#include "BaseException.h"

#include "YahuoRealTimeReqAck.h"
#include "YahuoHistoryReqAck.h"
#include "YahuoDataToLocalDB.h"

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

void testCYahuoDataToLocalDB()
{
	CConfigInfo::getInstance();
	CYahuoDataToLocalDB::getInstance();

	CYahuoDataToLocalDB::getInstance().doWork_YahuoDataToLocalDB();
	//CYahuoDataToLocalDB::getInstance().doWork_Local_FileDB_To_SQLiteDB();

	CYahuoDataToLocalDB::removeInstance();
	CConfigInfo::removeInstance();	
}


int main()
{
	CLog4cppLogger::getInstance();
	CLog4cppLogger::getInstance().initLog();
	CLog4cppLogger::getInstance().testLog();

	//testCYahuoRealTimeReqAck();
	//testCYahuoHistoryReqAck();
	testCYahuoDataToLocalDB();
	

	CLog4cppLogger::removeInstance();
	return 0;
}