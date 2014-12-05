#ifndef __CLASS_HISTORY_DATA_PROCESS_HELPER_H__
#define __CLASS_HISTORY_DATA_PROCESS_HELPER_H__

#include <string>
#include <time.h>

#include <QtCore/QString>
#include <QtCore/QStringList>

class CQtTimeHelper;
class CFileDataProcessHelper;

class CHistoryDataProcessHelper 
{
public:
	CHistoryDataProcessHelper();
	virtual ~CHistoryDataProcessHelper();
public:
	void saveData(const std::string& strSymbolUse, const std::string& strHistoryData);
	void getStartEndTimeValue( const std::string& strSymbolUse, 
		unsigned int& startYear, unsigned int& startMonth, unsigned int& startDay, 
		unsigned int& endYear, unsigned int& endMonth, unsigned int& endDay );

private:
	void _AnalysisData(const QString& strHistoryDataTmp, QStringList& strListHistoryDataTmp);
	void _SaveData(const QString& strSymbolUseTmp, const QStringList& strListHistoryDataTmp);
	void _GetStartEndTimeValueFromFile(const std::string& strFileName, time_t& time_Last_local);
	void _GetLastDataFromFile(const std::string& strFileName, std::string& strLineLastDate);
private:
	CQtTimeHelper* m_pQtTimeHelper;
	CFileDataProcessHelper* m_pFileDataProcessHelper;
};


#endif //__CLASS_HISTORY_DATA_PROCESS_HELPER_H__
