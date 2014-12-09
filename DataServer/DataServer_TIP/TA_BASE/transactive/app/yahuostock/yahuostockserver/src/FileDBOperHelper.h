#ifndef __CLASS_FILE_DB_OPER_HELPER_H__
#define __CLASS_FILE_DB_OPER_HELPER_H__

#include <string>
#include <time.h>

#include <QtCore/QString>
#include <QtCore/QStringList>

class CQtTimeHelper;
class CFileDBOper;

class CFileDBOperHelper 
{
public:
	CFileDBOperHelper();
	virtual ~CFileDBOperHelper();
public:
	void saveData(const std::string& strSymbolUse, const std::string& strHistoryData);
private:
	void _SaveData(const QString& strSymbolUseTmp, const QStringList& strListHistoryDataTmp);
private:
	CQtTimeHelper* m_pQtTimeHelper;
	CFileDBOper* m_pFileDataProcessHelper;
};


#endif //__CLASS_FILE_DB_OPER_HELPER_H__
