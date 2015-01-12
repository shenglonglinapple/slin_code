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

void CFileDBOperHelper::_RemoveEmptyString(QStringList& strList)
{
	QStringList::iterator iterLst;

	iterLst = strList.begin();
	while (iterLst != strList.end())
	{
		if ((*iterLst).isEmpty())
		{
			//strList.removeAt(0);
			strList.removeOne((*iterLst));
			iterLst = strList.begin();
		}
		else
		{
			iterLst++;
		}
	}//while
}

void CFileDBOperHelper::saveData(const QString & strHistoryData)
{
	QString strHistoryDataTmp;
	QStringList strListHistoryDataTmp;
	QString strFirstLine;
	QStringList::iterator iterLst;

	if (strHistoryData.isEmpty())
	{
		return;
	}

	strHistoryDataTmp = strHistoryData;

	strListHistoryDataTmp.clear();
	strListHistoryDataTmp = strHistoryDataTmp.split("\n");

	//000002.SZ
	//Date,Open,High,Low,Close,Volume,Adj Close
	//2014-12-03,11.00,11.88,11.00,11.20,340833800,11.20
	//......
	//1991-01-02,15.63,15.63,15.63,15.63,1053200,0.01

	//check and clean first line
	iterLst = strListHistoryDataTmp.begin();
	if (iterLst != strListHistoryDataTmp.end())
	{
		strFirstLine.clear();
		strFirstLine = (*iterLst);
		if (strFirstLine.contains("Date"))
		{
			(*iterLst).clear();// = "";//column name set null
			//strListHistoryDataTmp.removeAt(0);
		}
	}
	_RemoveEmptyString(strListHistoryDataTmp);
	if (!strListHistoryDataTmp.isEmpty())
	{
		_SaveData(strListHistoryDataTmp);
	}

	MYLOG4CPP_DEBUG<<"save data to file"
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"strHistoryData.size()="<<strHistoryData.size()
		<<" "<<"strListHistoryDataTmp.size()="<<strListHistoryDataTmp.size();

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

	m_pFileDBOper->saveDataToFile(strSaveDataFileName, strLstOldData);//append old data to file

	m_pFileDBOper->removeFile(strSaveDataFileName_Tmp);
}


