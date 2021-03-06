#ifndef __CLASS_FILE_SYSTEM_MANAGER_H__
#define __CLASS_FILE_SYSTEM_MANAGER_H__ 


#include "CFDServerCommonData.h"

#include <list>
#include <map>
#include <time.h>

////////QT_BEGIN_NAMESPACE

class CFileSystemItem;

class CFileSystemManager
{
public:
	typedef std::list<CFileSystemItem*>				LstFileSystemItemsInPathT;
	typedef std::list<CFileSystemItem*>::iterator   LstFileSystemItemsInPathIterT;

	typedef std::map<time_t, CFileSystemItem*>					MapTimeFileSystemItemT;
	typedef std::map<time_t, CFileSystemItem*>::iterator		MapTimeFileSystemItemIterT;
	typedef std::map<time_t, CFileSystemItem*>::value_type		MapTimeFileSystemItemValueTypeT;
public:
	CFileSystemManager(void);	
	~CFileSystemManager(void);

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


//////QT_END_NAMESPACE


#endif // __CLASS_FILE_SYSTEM_MANAGER_H__









