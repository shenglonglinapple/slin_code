#ifndef __CLASS_FILE_DB_OPER_H__
#define __CLASS_FILE_DB_OPER_H__

#include <string>

#include <QtCore/QString>
#include <QtCore/QStringList>


class CFileDBOper 
{
public:
	CFileDBOper(const QString& strSymbolUse);
	virtual ~CFileDBOper();
public:
	bool checkFileExist(const QString & strFileName);
	void getAllDataFromFile(const QString & strFileName, QStringList& strLstLines);
	void saveDataToFile(const QString & strFileName, const QStringList& strListHistoryDataTmp);
	void removeFile(const QString & strFileName);
	void renameFile(const QString & strOldFileName, const QString & strNewFileName);
public:
	QString  getSavaDataPath();
	QString getLastUpdateTime();
	void getLastUpdateLine(const QString & strFileName, QString& strLineLastDate);
	void createFile(const QString & strFileName);
private:
	QString m_strSaveDataPath;
	QString m_strSymbolUse;
};


#endif //__CLASS_FILE_DB_OPER_H__
