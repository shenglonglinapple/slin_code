#ifndef __CLASS_FILE_SYSTEM_ITEM_H__
#define __CLASS_FILE_SYSTEM_ITEM_H__ 


#include "CommonData.h"

#include <boost/filesystem.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/tokenizer.hpp"

NS_BEGIN(TA_Base_Test)


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

private:
	boost::filesystem::path m_fileSystemPath;
private:
	std::string m_strFileFullPath;//C://Sample//20121220.csv
	std::string m_strFullFileName;//20121220.csv
	std::string m_strFileName;//20121220
	std::string m_strFileExten;//csv
	boost::filesystem::path m_fFileFullPath;


};


NS_END(TA_Base_Test)


#endif // __CLASS_FILE_SYSTEM_ITEM_H__









