#include "FileDBOper.h"
#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>

#include "ProjectCommonData.h"
#include "ConfigInfo.h"

static const int DEF_INT_Max_Line_Length = 10240;


CFileDBOper::CFileDBOper()
{
	m_strSaveDataPath = CConfigInfo::getInstance().getFileDBPath().toStdString();

}

CFileDBOper::~CFileDBOper()
{


}

void CFileDBOper::removeFile(const std::string& strFileName)
{
	remove(strFileName.c_str());
}
void CFileDBOper::renameFile(const std::string& strOldFileName, const std::string& strNewFileName)
{
	rename(strOldFileName.c_str(), strNewFileName.c_str());
}


bool CFileDBOper::checkFileExist(const std::string& strFileName)
{
	bool bFunRes = false;

	std::ifstream streamFileName;

	if (strFileName.empty())
	{
		bFunRes = false;
		return bFunRes;
	}

	streamFileName.open(strFileName.c_str(), std::ios::in);
	if (false == streamFileName.good())
	{
		bFunRes = false;
	}
	else
	{
		bFunRes = true;
	}
	streamFileName.close();

	return bFunRes;
}






void CFileDBOper::getAllDataFromFile(const std::string& strFileName, QStringList& strLstLines)
{
	std::ifstream streamDataFileName;
	char* pszLine = NULL;
	int nLineIndex = 0;
	bool bFileExist = false;
	std::string strLineColumnName;

	strLstLines.clear();
	bFileExist = checkFileExist(strFileName);
	if (false == bFileExist)
	{
		strLstLines.clear();
		return;
	}

	if (NULL == pszLine)
	{
		pszLine = new char[DEF_INT_Max_Line_Length];
		memset(pszLine, 0, DEF_INT_Max_Line_Length);
	}

	streamDataFileName.open(strFileName.c_str(), std::ios::in);

	//000002.SZ
	//Date,Open,High,Low,Close,Volume,Adj Close
	//2014-12-03,11.00,11.88,11.00,11.20,340833800,11.20
	//......
	//1991-01-02,15.63,15.63,15.63,15.63,1053200,0.01
	nLineIndex = 0;
	while (false == streamDataFileName.eof())
	{
		memset(pszLine, 0, DEF_INT_Max_Line_Length);
		streamDataFileName.getline(pszLine, DEF_INT_Max_Line_Length);
		
		strLstLines.push_back(pszLine);

		nLineIndex++;
	}//while



	if (NULL != pszLine)
	{
		delete[] pszLine;
		pszLine = NULL;
	}

	if (streamDataFileName.is_open())
	{
		streamDataFileName.close();
	}

}
void CFileDBOper::saveDataToFile(const std::string& strFileName, const QStringList& strListHistoryDataTmp)
{
	std::string			strSaveDataFileName;
	std::ofstream		streamSaveDataFileName;

	strSaveDataFileName = strFileName;
	// Open the file for appending (retain existing entries) 
	streamSaveDataFileName.open(strSaveDataFileName.c_str(), std::ios::out | std::ios::app);

	foreach (const QString& strLine, strListHistoryDataTmp)
	{

		if (streamSaveDataFileName.is_open() && false == strLine.isEmpty())//TODO.
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

std::string CFileDBOper::getSavaDataPath()
{
	return m_strSaveDataPath;
}



QString CFileDBOper::getLastUpdateTime(const std::string& strSymbolUse)
{
	QString strLastUpdateDate;
	QString strLastUpdateDateTime;
	std::string	strDataFileName;
	bool bFileExist = false;

	strLastUpdateDate = DEF_VALUE_STRING_UTC_START_DATE.c_str();
	strLastUpdateDateTime = DEF_VALUE_STRING_UTC_START_DATE_TIME.c_str();

	strDataFileName = getSavaDataPath();
	strDataFileName += strSymbolUse;

	bFileExist = checkFileExist(strDataFileName);
	if (false == bFileExist)
	{
		return strLastUpdateDateTime;			
	}

	QString strLineLastDate;
	QStringList strLstDataTmp;
	getLastUpdateLine(strDataFileName, strLineLastDate);//2014-12-03,11.00,11.88,11.00,11.20,340833800,11.20
	strLstDataTmp = strLineLastDate.split(",");
	if (7 == strLstDataTmp.size())
	{
		strLastUpdateDate = strLstDataTmp[0];//2014-12-03
		strLastUpdateDateTime = strLastUpdateDate + " "+ DEF_VALUE_STRING_UTC_START_TIME.c_str();
	}

	return strLastUpdateDateTime;	
}

void CFileDBOper::getLastUpdateLine(const std::string& strFileName, QString& strLineLastDate)
{
	bool bFileExist = false;
	QStringList strLstData;

	bFileExist = checkFileExist(strFileName);
	if (false == bFileExist)
	{
		strLineLastDate = DEF_VALUE_STRING_UTC_START_DATE.c_str();
		strLineLastDate += ",15.63,15.63,15.63,15.63,1053200,0.01";//1970-01-01
		//strLineLastDate = "1970-01-01,15.63,15.63,15.63,15.63,1053200,0.01";//1970-01-01
		return;
	}

	getAllDataFromFile(strFileName, strLstData);
	if (strLstData.size() >= 1)
	{
		strLineLastDate = strLstData[1];
	}

	//000002.SZ
	//Date,Open,High,Low,Close,Volume,Adj Close
	//2014-12-03,11.00,11.88,11.00,11.20,340833800,11.20
	//......
	//1991-01-02,15.63,15.63,15.63,15.63,1053200,0.01
}