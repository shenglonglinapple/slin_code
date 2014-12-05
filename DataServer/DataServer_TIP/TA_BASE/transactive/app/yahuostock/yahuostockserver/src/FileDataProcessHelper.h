#ifndef __CLASS_FILE_DATA_PROCESS_HELPER_H__
#define __CLASS_FILE_DATA_PROCESS_HELPER_H__

#include <string>

#include <QtCore/QString>
#include <QtCore/QStringList>


class CFileDataProcessHelper 
{
public:
	CFileDataProcessHelper();
	virtual ~CFileDataProcessHelper();
public:
	bool checkFileExist(const std::string& strFileName);
	void getAllDataFromFile(const std::string& strFileName, QStringList& strLstLines);
	void saveDataToFile(const std::string& strFileName, const QStringList& strListHistoryDataTmp);
	void removeFile(const std::string& strFileName);
	void renameFile(const std::string& strOldFileName, const std::string& strNewFileName);
};


#endif //__CLASS_FILE_DATA_PROCESS_HELPER_H__
