#ifndef __CLASS_HISTORY_DATA_PROCESS_HELPER_H__
#define __CLASS_HISTORY_DATA_PROCESS_HELPER_H__

#include <string>
#include <QtCore/QString>
#include <QtCore/QStringList>

class CHistoryDataProcessHelper 
{
public:
	CHistoryDataProcessHelper();
	virtual ~CHistoryDataProcessHelper();
public:
	void saveDataToFile(const std::string& strSymbolUse, const std::string& strHistoryData);
private:
	void _SaveDataToFile();
	void _AnalysisData();
private:
	QString m_strSymbolUse;
	QString m_strHistoryData;
	QStringList m_strListHistoryData;


};


#endif //__CLASS_HISTORY_DATA_PROCESS_HELPER_H__
