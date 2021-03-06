#ifndef __CLASS_FILE_SYSTEM_ITEM_H__
#define __CLASS_FILE_SYSTEM_ITEM_H__ 


#include "CFDServerCommonData.h"

#include <boost/filesystem.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/tokenizer.hpp"

////////QT_BEGIN_NAMESPACE

class CCFDServerUtilityFun;

class CFileSystemItem
{
public:
	typedef std::list<std::string>                      LstLineT;
	typedef std::list<std::string>::iterator            LstLineIterT;

public:
	CFileSystemItem(const std::string& strFilePath);	
	~CFileSystemItem(void);

public:
	time_t getFileNameTime();
	std::string getFileFullPath();
	int    getAllLinesInFile(LstLineT& lstLine);
private:
	std::string _GetFileNameTimeStrValue(const std::string& strFileName);

private:
	boost::filesystem::path m_fileSystemPath;
private:
	std::string m_strFileFullPath;//C://Sample//20121220.csv
	std::string m_strFullFileName;//20121220.csv
	std::string m_strFileName;//20121220
	std::string m_strFileExten;//csv
	std::string m_strFileNameTimeStrValue;//2012-12-20 09:00:00
	time_t      m_nFileNameTimeIntValue;
	boost::filesystem::path m_fFileFullPath;

private:
	CCFDServerUtilityFun*			m_pUtilityFun;

};


//////QT_END_NAMESPACE


#endif // __CLASS_FILE_SYSTEM_ITEM_H__









