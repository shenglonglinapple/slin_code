#ifndef __CLASS_FILE_DB_OPER_H__
#define __CLASS_FILE_DB_OPER_H__

#include <string>

#include <QtCore/QString>
#include <QtCore/QStringList>


class CFileDBOper 
{
public:
	CFileDBOper();
	virtual ~CFileDBOper();
public:
	bool checkFileExist(const std::string& strFileName);
	void getAllDataFromFile(const std::string& strFileName, QStringList& strLstLines);
	void saveDataToFile(const std::string& strFileName, const QStringList& strListHistoryDataTmp);
	void removeFile(const std::string& strFileName);
	void renameFile(const std::string& strOldFileName, const std::string& strNewFileName);
public:
	std::string getSavaDataPath();
	QString getLastUpdateTime(const std::string& strSymbolUse);
	void getLastUpdateLine(const std::string& strFileName, QString& strLineLastDate);
private:
	std::string m_strSaveDataPath;
};


#endif //__CLASS_FILE_DB_OPER_H__
