#ifndef __CLASS_FILE_SYSTEM_FOLDER_H__
#define __CLASS_FILE_SYSTEM_FOLDER_H__ 


#include "UtilitiesCommonData.h"

#include <list>
#include <map>
#include <time.h>

NS_BEGIN(TA_Base_Core)

class CFileSystemItem;

class CFileSystemFolder
{
public:
	typedef std::list<CFileSystemItem*>				LstFileSystemItemsInPathT;
	typedef std::list<CFileSystemItem*>::iterator   LstFileSystemItemsInPathIterT;

	typedef std::map<time_t, CFileSystemItem*>					MapTimeFileSystemItemT;
	typedef std::map<time_t, CFileSystemItem*>::iterator		MapTimeFileSystemItemIterT;
	typedef std::map<time_t, CFileSystemItem*>::value_type		MapTimeFileSystemItemValueTypeT;
public:
	CFileSystemFolder(void);	
	~CFileSystemFolder(void);

public:
	bool checkDirectory(const std::string& strFolderPath);
	int createDirectory(const std::string& strFolderPath);
	int getAllFileSystemItemInPath(const std::string& strFolderPath, MapTimeFileSystemItemT& mapTimeFileSystemItem);
	int removeOldFile(time_t nStarTime, MapTimeFileSystemItemT& mapTimeFileSystemItem );
	int freeData(MapTimeFileSystemItemT& mapTimeFileSystemItem );

private:
	int _GetAllFileNameInPath( const std::string& strFolderPath, LstFileSystemItemsInPathT& lstFileSystemItemsInPath);
	int _SortAllFileInPathByTime(LstFileSystemItemsInPathT& lstFileSystemItemsInPath, MapTimeFileSystemItemT& mapTimeFileSystemItem);
};


NS_END(TA_Base_Core)


#endif // __CLASS_FILE_SYSTEM_FOLDER_H__









