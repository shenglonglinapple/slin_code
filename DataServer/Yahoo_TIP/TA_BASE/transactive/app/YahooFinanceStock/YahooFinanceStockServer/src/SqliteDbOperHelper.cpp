#include "SqliteDbOperHelper.h"

#include "BaseException.h"

#include "HistoryData.h"
#include "SqliteDbOper.h"
#include "Log4cppLogger.h"





CSqliteDbOperHelper::CSqliteDbOperHelper( const QString & strSymbolUse )
{
	m_strSymbolUse = strSymbolUse;

	QMutexLocker lock(&m_mutex_SqliteDbOper);
	m_pSqliteDbOper = NULL;
	m_pSqliteDbOper = new CSqliteDbOper(strSymbolUse);
}

CSqliteDbOperHelper::~CSqliteDbOperHelper()
{	

	QMutexLocker lock(&m_mutex_SqliteDbOper);	
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

void CSqliteDbOperHelper::_RemoveEmptyString(QStringList& strList)
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

void CSqliteDbOperHelper::saveData(const QString & strHistoryData)
{
	if (strHistoryData.isEmpty())
	{
		return;
	}
	QMutexLocker lock(&m_mutex_SqliteDbOper);	

	QString strHistoryDataTmp;
	QStringList strListHistoryDataTmp;
	LstHistoryDataT lstHistoryData;
	QStringList::iterator iterLst;
	QString strFirstLine;

	strHistoryDataTmp = strHistoryData;

	strListHistoryDataTmp.clear();
	strListHistoryDataTmp = strHistoryDataTmp.split("\n");

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
		_AnalysisData(strListHistoryDataTmp, lstHistoryData);
		m_pSqliteDbOper->saveData(&lstHistoryData);
	}

	MYLOG4CPP_DEBUG<<"save data to SQLite"
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"strHistoryData.size()="<<strHistoryData.size()
		<<" "<<"strListHistoryDataTmp.size()="<<strListHistoryDataTmp.size();

	strListHistoryDataTmp.clear();
	_FreeData(&lstHistoryData);
	lstHistoryData.clear();
}

int CSqliteDbOperHelper::selectData(
	const QString & strFrom, 
	const QString & strTo, 
	LstHistoryDataT& lstData )
{
	QMutexLocker lock(&m_mutex_SqliteDbOper);	
	return m_pSqliteDbOper->selectData(strFrom, strTo, lstData);
}

QString  CSqliteDbOperHelper::getSymbolUse()
{
	return m_strSymbolUse;
}

int CSqliteDbOperHelper::selectData_MinTime( QString& strValueGet )
{
	QMutexLocker lock(&m_mutex_SqliteDbOper);	
	return m_pSqliteDbOper->selectData_MinTime(strValueGet);

}

int CSqliteDbOperHelper::selectData_MaxTime( QString& strValueGet )
{
	QMutexLocker lock(&m_mutex_SqliteDbOper);	
	return m_pSqliteDbOper->selectData_MaxTime(strValueGet);

}

int CSqliteDbOperHelper::selectData_Count( int& nValueGet )
{
	QMutexLocker lock(&m_mutex_SqliteDbOper);	
	return m_pSqliteDbOper->selectData_Count(nValueGet);

}



