#include "InitYahuoDataToFile.h"

#include "BaseException.h"

#include "YahuoHistoryReqAck.h"
#include "HistoryDataProcssHelper.h"


#include "Log4cppLogger.h"




CInitYahuoDataToFile::CInitYahuoDataToFile()
{

}

CInitYahuoDataToFile::~CInitYahuoDataToFile()
{	
}


void CInitYahuoDataToFile::getAndSaveHistoryData(const std::string& strSymbolUse)
{
	int nFunRes = 0;
	CYahuoHistoryReqAck classCYahuoHistoryReqAck;
	std::string petr4HistoricalPrices;

	unsigned int startYear = 0;
	unsigned int startMonth = 0;
	unsigned int startDay = 0;
	unsigned int endYear = 0;
	unsigned int endMonth = 0;
	unsigned int endDay = 0;

	CHistoryDataProcessHelper    objHelper;
	objHelper.getStartEndTimeValue(strSymbolUse, startYear, startMonth, startDay, endYear, endMonth, endDay);


	try
	{
		//petr4HistoricalPrices = classCYahuoHistoryReqAck.getHistoricalQuotesCsv(
		//	strSymbolUse, 1970, 1, 1, 2014, 12, 4, YahuoReqAck::daily);
		petr4HistoricalPrices = classCYahuoHistoryReqAck.getHistoricalQuotesCsv(
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
		_SaveDataToFile(strSymbolUse, petr4HistoricalPrices);
	}


	
}

void CInitYahuoDataToFile::_SaveDataToFile(const std::string& strSymbolUse, const std::string& strData)
{
	CHistoryDataProcessHelper    objHelper;
	objHelper.saveData(strSymbolUse, strData);
}