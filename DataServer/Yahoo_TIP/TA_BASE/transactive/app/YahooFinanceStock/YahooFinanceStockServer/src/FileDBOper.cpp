#include "FileDBOper.h"

#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "ConfigInfo.h"
#include "Log4cppLogger.h"

static const char* DEF_VALUE_STRING_UTC_START_DATE = "1970-01-01";
static const char* DEF_VALUE_STRING_UTC_START_TIME = "08:00:00";
static const char* DEF_VALUE_STRING_UTC_START_DATE_TIME = "1970-01-01 08:00:00";

static const int DEF_INT_MAX_LINE_LENGTH = 1024*10;
static const int DEF_INT_ONE_DAY_SECONDS = 60*60*24;


CFileDBOper::CFileDBOper( const QString& strSymbolUse )
{
	m_strSymbolUse = strSymbolUse;
	m_strSaveDataPath.clear();
	m_strSaveDataPath = CConfigInfo::getInstance().getFileDBPath();
}

CFileDBOper::~CFileDBOper()
{


}

void CFileDBOper::removeFile(const QString & strFileName)
{
	QFile file(strFileName);
	file.remove();
	//remove(strFileName.toStdString().c_str());
}
void CFileDBOper::renameFile(const QString & strOldFileName, const QString & strNewFileName)
{
	QFile file(strOldFileName);
	file.rename(strNewFileName);

	//rename(strOldFileName.toStdString().c_str(), strNewFileName.toStdString().c_str());
}


bool CFileDBOper::checkFileExist(const QString & strFileName)
{
	bool bFunRes = false;

	QFile file(strFileName);
	bFunRes = file.exists();

	return bFunRes;
}






void CFileDBOper::getAllDataFromFile(const QString & strFileName, QStringList& strLstLines)
{
	strLstLines.clear();

	qint32 nLineIndex = 0;

	QFile file(strFileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		strLstLines.clear();
		return;
	}

	QTextStream streamRead(&file);
	nLineIndex = 0;
	while (!streamRead.atEnd()) 
	{
		QString strOneline = streamRead.readLine();
		strLstLines.push_back(strOneline);
		nLineIndex++;
	}


	//000002.SZ
	//Date,Open,High,Low,Close,Volume,Adj Close
	//2014-12-03,11.00,11.88,11.00,11.20,340833800,11.20
	//......
	//1991-01-02,15.63,15.63,15.63,15.63,1053200,0.01

}

void CFileDBOper::createFile(const QString & strFileName)
{
	QFile file(strFileName);
	if (file.exists())
	{
		return;
	}
	//file.open(QIODevice::WriteOnly );
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	//
	file.close();//create file
	return;
	
	/*
	std::ofstream streamSaveDataFileName;
	streamSaveDataFileName.open(strFileName.toStdString().c_str(), std::ios::out | std::ios::app);
	if (streamSaveDataFileName.is_open())
	{
		streamSaveDataFileName.close();
	}
	*/

}

void CFileDBOper::saveDataToFile(const QString & strFileName, const QStringList& strListHistoryDataTmp, bool bAddSymbolUse)
{
	createFile(strFileName);

	QFile file(strFileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))//Append QIODevice::WriteOnly 
	{
		MYLOG4CPP_ERROR<<"not find file strFileName="<<strFileName;
		return;
	}

	QTextStream streamWrite(&file);

	foreach (const QString& strLine, strListHistoryDataTmp)
	{
		if (false == strLine.isEmpty())//TODO.
		{
			if (bAddSymbolUse)
			{
				//000001.SZ,2015-01-09,14.90,15.87,14.71,15.08,250850000,15.08
				streamWrite<<m_strSymbolUse<<","<<strLine<<"\n";
			}
			else
			{
				streamWrite<<strLine<<"\n";
			}
						
		}

	}
}

QString  CFileDBOper::getSavaDataPath()
{
	return m_strSaveDataPath;
}



QString CFileDBOper::getLastUpdateTime()
{
	QString strLastUpdateDate;
	QString strLastUpdateDateTime;
	QString 	strDataFileName;
	bool bFileExist = false;

	strLastUpdateDate = DEF_VALUE_STRING_UTC_START_DATE;
	strLastUpdateDateTime = DEF_VALUE_STRING_UTC_START_DATE_TIME;

	strDataFileName = getSavaDataPath();
	strDataFileName += m_strSymbolUse;

	bFileExist = checkFileExist(strDataFileName);
	if (false == bFileExist)
	{
		return strLastUpdateDateTime;			
	}

	QString strLineLastDate;
	QStringList strLstDataTmp;
	//SymbolUse,Date,Open,High,Low,Close,Volume,Adj Close
	//"XXXXXX.SZ,1970-01-01,15.63,15.63,15.63,15.63,1053200,0.01"
	getLastUpdateLine(strDataFileName, strLineLastDate);
	strLstDataTmp = strLineLastDate.split(",");
	if (8 == strLstDataTmp.size())
	{
		strLastUpdateDate = strLstDataTmp[1];//2014-12-03
		strLastUpdateDateTime = strLastUpdateDate + " "+ DEF_VALUE_STRING_UTC_START_TIME;
	}

	return strLastUpdateDateTime;	
}

void CFileDBOper::getLastUpdateLine(const QString & strFileName, QString& strLineLastDate)
{
	bool bFileExist = false;
	QStringList strLstData;

	bFileExist = checkFileExist(strFileName);
	if (false == bFileExist)
	{
		strLineLastDate = "XXXXXX.SZ,";
		strLineLastDate += DEF_VALUE_STRING_UTC_START_DATE;
		strLineLastDate += ",15.63,15.63,15.63,15.63,1053200,0.01";//1970-01-01
		//strLineLastDate = "XXXXXX.SZ,1970-01-01,15.63,15.63,15.63,15.63,1053200,0.01";//1970-01-01
		return;
	}

	getAllDataFromFile(strFileName, strLstData);
	if (strLstData.size() >= 1)
	{
		strLineLastDate = strLstData[0];
	}

	//000002.SZ
	//SymbolUse,Date,Open,High,Low,Close,Volume,Adj Close
	//XXXXXX.SZ,2014-12-03,11.00,11.88,11.00,11.20,340833800,11.20
	//......
	//XXXXXX.SZ,1991-01-02,15.63,15.63,15.63,15.63,1053200,0.01
}