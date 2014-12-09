#include "ProcessFileDataToDB.h"

#include "BaseException.h"

#include "HistoryData.h"
#include "SqliteDbOper.h"
#include "FileDBOper.h"
#include "Log4cppLogger.h"




CProcessFileDataToDB::CProcessFileDataToDB()
{
	m_pFileDBOper = NULL;
	m_pFileDBOper = new CFileDBOper();
	m_pSqliteDbOper = NULL;
	m_pSqliteDbOper = new CSqliteDbOper();
}

CProcessFileDataToDB::~CProcessFileDataToDB()
{	
	if (NULL != m_pFileDBOper)
	{
		delete m_pFileDBOper;
		m_pFileDBOper = NULL;
	}

	if (NULL != m_pSqliteDbOper)
	{
		delete m_pSqliteDbOper;
		m_pSqliteDbOper = NULL;
	}

}

void CProcessFileDataToDB::proceeFileData(const std::string& strSymbolUse)
{
	std::string	 strDataFileName;
	bool bFileExist = false;
	QStringList strLstLines;
	LstHistoryDataT lstData;

	strDataFileName = m_pFileDBOper->getSavaDataPath();
	strDataFileName += strSymbolUse;

	bFileExist = m_pFileDBOper->checkFileExist(strDataFileName);
	if (false == bFileExist)
	{
		MYLOG4CPP_ERROR<<"error! not find file="<<strDataFileName;
		return;
	}
	m_pFileDBOper->getAllDataFromFile(strDataFileName, strLstLines);

	if (strLstLines.size() >= 1)
	{
		strLstLines[0] = "";
		strLstLines[0].clear();// = "";//column name set null
	}

	_AnalysisData(strLstLines, lstData);

	m_pSqliteDbOper->resetDataBaseValue(strSymbolUse.c_str());
	m_pSqliteDbOper->saveData(&lstData);

	strLstLines.clear();
	_FreeData(&lstData);
	lstData.clear();
	
}
void CProcessFileDataToDB::_AnalysisData(QStringList& strLstLines, LstHistoryDataT& lstData)
{
	CHistoryData* pHistoryData = NULL;

	foreach (const QString& strLine, strLstLines)
	{
		if (false == strLine.isEmpty())
		{
			pHistoryData = new CHistoryData();
			pHistoryData->resetValue(strLine);

			lstData.push_back(pHistoryData);
		}

		pHistoryData = NULL;
	}//foreach

	if (NULL != pHistoryData)
	{
		delete pHistoryData;
		pHistoryData = NULL;
	}
}

void CProcessFileDataToDB::_FreeData(LstHistoryDataT* pLstData)
{
	LstHistoryDataIterT iterLst;
	CHistoryData* pDataTmp = NULL;

	if (pLstData->empty())
	{
		return;
	}

	iterLst = pLstData->begin();
	while (iterLst != pLstData->end())
	{
		pDataTmp = (*iterLst);

		delete pDataTmp;
		pDataTmp = NULL;

		iterLst++;
	}//while

	pLstData->clear();
	return;
}
