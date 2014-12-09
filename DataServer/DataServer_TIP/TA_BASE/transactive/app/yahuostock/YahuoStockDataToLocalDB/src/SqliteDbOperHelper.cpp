#include "SqliteDbOperHelper.h"

#include "BaseException.h"

#include "HistoryData.h"
#include "SqliteDbOper.h"
#include "Log4cppLogger.h"




CSqliteDbOperHelper::CSqliteDbOperHelper()
{
	m_pSqliteDbOper = NULL;
	m_pSqliteDbOper = new CSqliteDbOper();
}

CSqliteDbOperHelper::~CSqliteDbOperHelper()
{	

	if (NULL != m_pSqliteDbOper)
	{
		delete m_pSqliteDbOper;
		m_pSqliteDbOper = NULL;
	}

}

void CSqliteDbOperHelper::_AnalysisData(QStringList& strLstLines, LstHistoryDataT& lstData)
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

void CSqliteDbOperHelper::_FreeData(LstHistoryDataT* pLstData)
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

void CSqliteDbOperHelper::saveData(const std::string& strSymbolUse, const std::string& strHistoryData)
{
	QString strHistoryDataTmp;
	QStringList strListHistoryDataTmp;
	LstHistoryDataT lstHistoryData;

	strHistoryDataTmp = strHistoryData.c_str();

	strListHistoryDataTmp.clear();
	strListHistoryDataTmp = strHistoryDataTmp.split("\n");

	if (strListHistoryDataTmp.size() >= 1)
	{
		strListHistoryDataTmp[0] = "";
		strListHistoryDataTmp[0].clear();// = "";//column name set null
	}
	_AnalysisData(strListHistoryDataTmp, lstHistoryData);

	m_pSqliteDbOper->setDataBaseValue(strSymbolUse.c_str());
	m_pSqliteDbOper->saveData(&lstHistoryData);

	strListHistoryDataTmp.clear();
	_FreeData(&lstHistoryData);
	lstHistoryData.clear();
}



