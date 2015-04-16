#ifndef __CLASS_FILE_SYSTEM_ITEM_H__
#define __CLASS_FILE_SYSTEM_ITEM_H__ 


#include "core/utilities/src/UtilitiesCommonData.h"

#include <boost/filesystem.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/tokenizer.hpp"

NS_BEGIN(TA_Base_Core)


class CFileSystemItem
{
public:
	typedef std::list<std::string>                      LstLineT;
	typedef std::list<std::string>::iterator            LstLineIterT;

public:
	CFileSystemItem(const std::string& strFilePath);	
	~CFileSystemItem(void);

public:
	std::string getFileFullPath();
	int    getAllLinesInFile(LstLineT& lstLine);
	std::time_t getLastWriteTime();
private:
	boost::filesystem::path m_fileSystemPath;
private:
	std::string m_strFileFullPath;//C://Sample//20121220.csv
	std::string m_strFullFileName;//20121220.csv
	std::string m_strFileName;//20121220
	std::string m_strFileExten;//csv
	boost::filesystem::path m_fFileFullPath;
	std::time_t m_nLastWriteTime;


};


NS_END(TA_Base_Core)


#endif // __CLASS_FILE_SYSTEM_ITEM_H__









