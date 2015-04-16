#ifndef __CLASS_WORK_GET_ALL_FILE_NAME_IN_PATH_H__
#define __CLASS_WORK_GET_ALL_FILE_NAME_IN_PATH_H__ 


#include "UtilitiesCommonData.h"

#include "FileSystemFolder.h"

NS_BEGIN(TA_Base_Core)


class CWorkGetAllFileNameInPath
{
public:
	CWorkGetAllFileNameInPath(void);	
	~CWorkGetAllFileNameInPath(void);
public:
	void doWork();
private:
	void _SaveAllFileName(CFileSystemFolder::MapTimeFileSystemItemT& mapTimeFileSystemItem);
public:
	std::string m_strFullPath;
	std::string m_strSaveDataFileName;
	CFileSystemFolder* m_pFileSystemFolder;
};


NS_END(TA_Base_Core)


#endif // __CLASS_WORK_GET_ALL_FILE_NAME_IN_PATH_H__









