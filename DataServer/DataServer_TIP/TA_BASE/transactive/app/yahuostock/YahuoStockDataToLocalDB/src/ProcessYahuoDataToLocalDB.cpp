#include "ProcessYahuoDataToLocalDB.h"

#include "BaseException.h"

#include "YahuoHistoryReqAck.h"
#include "RequestYahuoDataHelper.h"
#include "FileDBOperHelper.h"
#include "SqliteDbOperHelper.h"

#include "Log4cppLogger.h"




CProcessYahuoDataToLocalDB::CProcessYahuoDataToLocalDB()
{

}

CProcessYahuoDataToLocalDB::~CProcessYahuoDataToLocalDB()
{	
}


void CProcessYahuoDataToLocalDB::processStock(const std::string& strSymbolUse)
{
	int nFunRes = 0;
	unsigned int startYear = 0;
	unsigned int startMonth = 0;
	unsigned int startDay = 0;
	unsigned int endYear = 0;
	unsigned int endMonth = 0;
	unsigned int endDay = 0;
	std::string petr4HistoricalPrices;

	CYahuoHistoryReqAck myYahuoHistoryReqAck;
	CRequestYahuoDataHelper myRequestYahuoDataHelper;
	myRequestYahuoDataHelper.getStartEndTimeValue(
		strSymbolUse, startYear, startMonth, startDay, 
		endYear, endMonth, endDay);

	try
	{
		//petr4HistoricalPrices = classCYahuoHistoryReqAck.getHistoricalQuotesCsv(
		//	strSymbolUse, 1970, 1, 1, 2014, 12, 4, YahuoReqAck::daily);
		petr4HistoricalPrices = myYahuoHistoryReqAck.getHistoricalQuotesCsv(
			strSymbolUse, startYear, startMonth, startDay, endYear, endMonth, endDay, YahuoReqAck::daily);
	}
	catch(CBaseException& e)
	{
		nFunRes = -1;
	}
	catch(...)
	{
		nFunRes = -1;
	}

	if (0 == nFunRes)
	{
		_SaveDataToLocalDB(strSymbolUse, petr4HistoricalPrices);
	}


	
}

void CProcessYahuoDataToLocalDB::_SaveDataToLocalDB(const std::string& strSymbolUse, const std::string& strData)
{
	CFileDBOperHelper    myFileDBOperHelper;
	myFileDBOperHelper.saveData(strSymbolUse, strData);

	CSqliteDbOperHelper mySqliteDbOperHelper;
	mySqliteDbOperHelper.saveData(strSymbolUse, strData);
}