#include "FileDBOperHelper.h"
#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>

#include "ProjectCommonData.h"
#include "QtTimeHelper.h"
#include "ConfigInfo.h"
#include "FileDBOper.h"

#include "Log4cppLogger.h"




CFileDBOperHelper::CFileDBOperHelper()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	m_pFileDataProcessHelper = NULL;
	m_pFileDataProcessHelper = new CFileDBOper();

}

CFileDBOperHelper::~CFileDBOperHelper()
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



void CFileDBOperHelper::saveData(const std::string& strSymbolUse, const std::string& strHistoryData)
{
	QString strSymbolUseTmp;
	QString strHistoryDataTmp;
	QStringList strListHistoryDataTmp;

	strSymbolUseTmp = strSymbolUse.c_str();
	strHistoryDataTmp = strHistoryData.c_str();

	strListHistoryDataTmp.clear();
	strListHistoryDataTmp = strHistoryDataTmp.split("\n");

	_SaveData(strSymbolUseTmp, strListHistoryDataTmp);


}



void CFileDBOperHelper::_SaveData(const QString& strSymbolUseTmp, const QStringList& strListHistoryDataTmp)
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


