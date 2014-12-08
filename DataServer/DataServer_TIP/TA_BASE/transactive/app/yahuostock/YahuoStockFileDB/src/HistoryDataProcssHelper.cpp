#include "HistoryDataProcssHelper.h"
#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>

#include "QtTimeHelper.h"
#include "HistoryDataProcssHelper.h"
#include "FileDataProcessHelper.h"

#include "Log4cppLogger.h"


static const int DEF_INT_One_Day_Seconds = 60*60*24;


CHistoryDataProcessHelper::CHistoryDataProcessHelper()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	m_pFileDataProcessHelper = NULL;
	m_pFileDataProcessHelper = new CFileDataProcessHelper();

}

CHistoryDataProcessHelper::~CHistoryDataProcessHelper()
{
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}

	if (NULL != m_pFileDataProcessHelper)
	{
		delete m_pFileDataProcessHelper;
		m_pFileDataProcessHelper = NULL;
	}
}



void CHistoryDataProcessHelper::saveData(const std::string& strSymbolUse, const std::string& strHistoryData)
{
	QString strSymbolUseTmp;
	QString strHistoryDataTmp;
	QStringList strListHistoryDataTmp;

	strSymbolUseTmp = strSymbolUse.c_str();
	strHistoryDataTmp = strHistoryData.c_str();

	_AnalysisData(strHistoryDataTmp, strListHistoryDataTmp);
	_SaveData(strSymbolUseTmp, strListHistoryDataTmp);


}
void CHistoryDataProcessHelper::_AnalysisData(const QString& strHistoryDataTmp, QStringList& strListHistoryDataTmp)
{
	strListHistoryDataTmp.clear();
	strListHistoryDataTmp = strHistoryDataTmp.split("\n");
	
}



void CHistoryDataProcessHelper::_SaveData(const QString& strSymbolUseTmp, const QStringList& strListHistoryDataTmp)
{
	std::string			strSaveDataFileName;
	std::string			strSaveDataFileName_Tmp;
	QStringList  strLstOldData;
	bool bFileExist = false;

	strSaveDataFileName = m_pFileDataProcessHelper->getSavaDataPath();
	strSaveDataFileName += strSymbolUseTmp.toStdString();
	
	bFileExist = m_pFileDataProcessHelper->checkFileExist(strSaveDataFileName);
	if (false == bFileExist)
	{
		//create new file and save data
		m_pFileDataProcessHelper->saveDataToFile(strSaveDataFileName, strListHistoryDataTmp);
		return;
	}
	m_pFileDataProcessHelper->getAllDataFromFile(strSaveDataFileName, strLstOldData);
	
	strSaveDataFileName_Tmp = strSaveDataFileName + "_Tmp";
	m_pFileDataProcessHelper->renameFile(strSaveDataFileName, strSaveDataFileName_Tmp);
	m_pFileDataProcessHelper->saveDataToFile(strSaveDataFileName, strListHistoryDataTmp);

	strLstOldData[0] = "";
	strLstOldData[0].clear();// = "";//column name set null
	m_pFileDataProcessHelper->saveDataToFile(strSaveDataFileName, strLstOldData);//append to file

	m_pFileDataProcessHelper->removeFile(strSaveDataFileName_Tmp);
}



void CHistoryDataProcessHelper::getStartEndTimeValue( 
	const std::string& strSymbolUse, 
	unsigned int& startYear, unsigned int& startMonth, unsigned int& startDay, 
	unsigned int& endYear, unsigned int& endMonth, unsigned int& endDay )
{
	std::string	strDataFileName;
	time_t time_end_local;
	time_t time_start_local;
	bool bFileExist = false;

	strDataFileName = m_pFileDataProcessHelper->getSavaDataPath();
	strDataFileName += strSymbolUse;
	
	bFileExist = m_pFileDataProcessHelper->checkFileExist(strDataFileName);
	if (false == bFileExist)
	{
		time_end_local = m_pQtTimeHelper->getTimeNow_Qt();
		time_start_local = 0;
	}
	else
	{
		time_end_local = m_pQtTimeHelper->getTimeNow_Qt();
		_GetStartEndTimeValueFromFile(strDataFileName, time_start_local);
	}

	m_pQtTimeHelper->getTimeInfo_Qt(time_end_local, endYear, endMonth, endDay);
	m_pQtTimeHelper->getTimeInfo_Qt(time_start_local, startYear, startMonth, startDay);

	return;	
}


void CHistoryDataProcessHelper::_GetStartEndTimeValueFromFile(const std::string& strFileName, time_t& time_Last_local)
{
	std::string strLineLastDate;
	QString strLastDate;
	QStringList strListData;
	bool bFileExist = false;
	int nFindIndex = 0;

	bFileExist = m_pFileDataProcessHelper->checkFileExist(strFileName);
	if (false == bFileExist)
	{
		time_Last_local = 0;
		return;
	}

	_GetLastDataFromFile(strFileName, strLineLastDate);//2014-12-03,11.00,11.88,11.00,11.20,340833800,11.20
	strLastDate = strLineLastDate.c_str();
	nFindIndex = strLastDate.indexOf(",");
	if (-1 == nFindIndex)
	{
		strLastDate = "1970-01-01";
	}
	else
	{
		strListData = strLastDate.split(",");
		strLastDate = strListData[0];//2014-12-03
	}

	strLastDate += " 01:00:00";//" 23:00:00" " 01:00:00"
	time_Last_local = m_pQtTimeHelper->strToDateTime_Qt(strLastDate.toStdString());
	time_Last_local += DEF_INT_One_Day_Seconds;
	return;
}

void CHistoryDataProcessHelper::_GetLastDataFromFile(const std::string& strFileName, std::string& strLineLastDate)
{
	bool bFileExist = false;
	QStringList strLstData;

	bFileExist = m_pFileDataProcessHelper->checkFileExist(strFileName);
	if (false == bFileExist)
	{
		strLineLastDate = "1970-01-01,15.63,15.63,15.63,15.63,1053200,0.01";//1970-01-01
		return;
	}

	m_pFileDataProcessHelper->getAllDataFromFile(strFileName, strLstData);
    if (strLstData.size() >= 1)
	{
		strLineLastDate = strLstData[1].toStdString();
	}

	//000002.SZ
	//Date,Open,High,Low,Close,Volume,Adj Close
	//2014-12-03,11.00,11.88,11.00,11.20,340833800,11.20
	//......
	//1991-01-02,15.63,15.63,15.63,15.63,1053200,0.01
}

