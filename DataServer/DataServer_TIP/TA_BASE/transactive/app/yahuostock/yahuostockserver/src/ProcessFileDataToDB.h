#ifndef __CLASS_PROCESS_FILE_DATA_TO_DB_H__
#define __CLASS_PROCESS_FILE_DATA_TO_DB_H__


#include <string>
#include <list>

#include <QtCore/QStringList>

class CFileDBOper;
class CHistoryData;
class CSqliteDbOper;

class CProcessFileDataToDB
{
public:
	typedef std::list<CHistoryData*>	LstHistoryDataT;
	typedef std::list<CHistoryData*>::iterator	LstHistoryDataIterT;
public:
	CProcessFileDataToDB();
	virtual ~CProcessFileDataToDB();
public:
	void proceeFileData(const std::string& strSymbolUse);
private:
	void _AnalysisData(QStringList& strLstLines, LstHistoryDataT& lstData);
	void _FreeData(LstHistoryDataT* pLstData);
private:
	CFileDBOper* m_pFileDBOper;
	CSqliteDbOper* m_pSqliteDbOper;

};


#endif //__CLASS_PROCESS_FILE_DATA_TO_DB_H__
