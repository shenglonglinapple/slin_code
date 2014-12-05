#include "HistoryDataProcssHelper.h"
#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>


#include "Log4cppLogger.h"


static const std::string DEF_STRING_Path_SaveData="./SaveData/";


CHistoryDataProcessHelper::CHistoryDataProcessHelper()
{

}

CHistoryDataProcessHelper::~CHistoryDataProcessHelper()
{

}

void CHistoryDataProcessHelper::saveDataToFile(const std::string& strSymbolUse, const std::string& strHistoryData)
{
	m_strSymbolUse = strSymbolUse.c_str();
	m_strHistoryData = strHistoryData.c_str();

	_AnalysisData();
	_SaveDataToFile();


}
void CHistoryDataProcessHelper::_AnalysisData()
{
	m_strListHistoryData.clear();
	m_strListHistoryData = m_strHistoryData.split("\n");
	
}

void CHistoryDataProcessHelper::_SaveDataToFile()
{
	std::string			strSaveDataFileName;
	std::ofstream		streamSaveDataFileName;

	strSaveDataFileName = DEF_STRING_Path_SaveData;
	strSaveDataFileName += m_strSymbolUse.toStdString();
	// Open the file for appending (retain existing entries) 
	streamSaveDataFileName.open(strSaveDataFileName.c_str(), std::ios::out | std::ios::app);

	foreach (const QString& strLine, m_strListHistoryData)
	{

		if (streamSaveDataFileName.is_open())
		{
			streamSaveDataFileName<<strLine.toStdString()<<std::endl;
			//streamSaveDataFileName.flush();
		}

	}


	if (streamSaveDataFileName.is_open())
	{
		streamSaveDataFileName.flush();
		streamSaveDataFileName.close();
	}


}

