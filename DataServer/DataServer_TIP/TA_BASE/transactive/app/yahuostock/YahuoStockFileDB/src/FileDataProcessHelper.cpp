#include "FileDataProcessHelper.h"
#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include "ConfigInfo.h"

static const int DEF_INT_Max_Line_Length = 10240;


CFileDataProcessHelper::CFileDataProcessHelper()
{
	m_strSaveDataPath = CConfigInfo::getInstance().getFileDBPath().toStdString();

}

CFileDataProcessHelper::~CFileDataProcessHelper()
{


}

void CFileDataProcessHelper::removeFile(const std::string& strFileName)
{
	remove(strFileName.c_str());
}
void CFileDataProcessHelper::renameFile(const std::string& strOldFileName, const std::string& strNewFileName)
{
	rename(strOldFileName.c_str(), strNewFileName.c_str());
}


bool CFileDataProcessHelper::checkFileExist(const std::string& strFileName)
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






void CFileDataProcessHelper::getAllDataFromFile(const std::string& strFileName, QStringList& strLstLines)
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
void CFileDataProcessHelper::saveDataToFile(const std::string& strFileName, const QStringList& strListHistoryDataTmp)
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

std::string CFileDataProcessHelper::getSavaDataPath()
{
	return m_strSaveDataPath;
}
