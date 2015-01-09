#include "FileDBOperHelper.h"
#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>

#include "QtTimeHelper.h"
#include "ConfigInfo.h"
#include "FileDBOper.h"

#include "Log4cppLogger.h"





CFileDBOperHelper::CFileDBOperHelper( const QString& strSymbolUse )
{
	m_pQtTimeHelper = NULL;
	m_pFileDBOper = NULL;

	m_strSymbolUse = strSymbolUse;
	m_pQtTimeHelper = new CQtTimeHelper();
	m_pFileDBOper = new CFileDBOper(strSymbolUse);

}

CFileDBOperHelper::~CFileDBOperHelper()
{
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}

	if (NULL != m_pFileDBOper)
	{
		delete m_pFileDBOper;
		m_pFileDBOper = NULL;
	}
}



void CFileDBOperHelper::saveData(const QString & strHistoryData)
{
	QString strHistoryDataTmp;
	QStringList strListHistoryDataTmp;

	if (strHistoryData.isEmpty())
	{
		return;
	}

	strHistoryDataTmp = strHistoryData;

	strListHistoryDataTmp.clear();
	strListHistoryDataTmp = strHistoryDataTmp.split("\n");

	_SaveData(strListHistoryDataTmp);


}



void CFileDBOperHelper::_SaveData(const QStringList& strListHistoryDataTmp)
{
	QString 			strSaveDataFileName;
	QString 			strSaveDataFileName_Tmp;
	QStringList  strLstOldData;
	bool bFileExist = false;

	strSaveDataFileName = m_pFileDBOper->getSavaDataPath();
	strSaveDataFileName += m_strSymbolUse;
	
	bFileExist = m_pFileDBOper->checkFileExist(strSaveDataFileName);
	if (false == bFileExist)
	{
		//create new file and save data
		m_pFileDBOper->saveDataToFile(strSaveDataFileName, strListHistoryDataTmp);
		return;
	}
	m_pFileDBOper->getAllDataFromFile(strSaveDataFileName, strLstOldData);
	
	strSaveDataFileName_Tmp = strSaveDataFileName + "_Tmp";
	m_pFileDBOper->renameFile(strSaveDataFileName, strSaveDataFileName_Tmp);
	m_pFileDBOper->saveDataToFile(strSaveDataFileName, strListHistoryDataTmp);

	strLstOldData[0] = "";
	strLstOldData[0].clear();// = "";//column name set null
	m_pFileDBOper->saveDataToFile(strSaveDataFileName, strLstOldData);//append to file

	m_pFileDBOper->removeFile(strSaveDataFileName_Tmp);
}


