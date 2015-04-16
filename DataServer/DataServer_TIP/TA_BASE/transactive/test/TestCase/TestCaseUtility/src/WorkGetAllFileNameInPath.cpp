#include "WorkGetAllFileNameInPath.h"
#include <sstream>
#include <fstream> 
#include <boost/algorithm/string.hpp>

#include "FileSystemFolder.h"
#include "FileSystemItem.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)





CWorkGetAllFileNameInPath::CWorkGetAllFileNameInPath( void )
{
	m_strFullPath.clear();
	m_strSaveDataFileName.clear();
	m_pFileSystemFolder = new CFileSystemFolder();
}

CWorkGetAllFileNameInPath::~CWorkGetAllFileNameInPath( void )
{

	if (NULL != m_pFileSystemFolder)
	{
		delete m_pFileSystemFolder;
		m_pFileSystemFolder = NULL;
	}
}

void CWorkGetAllFileNameInPath::doWork()
{
	CFileSystemFolder::MapTimeFileSystemItemT mapTimeFileSystemItem;


	m_strFullPath = "C:\\Users\\lin.shenglong\\Desktop\\work_perforce_3001DBSync_Chennai\\changelist_Chennai_Review_Branch\\pictures_changelist_Chennai_Review_Branch";
	m_pFileSystemFolder->getAllFileSystemItemInPath(m_strFullPath, mapTimeFileSystemItem);
	_SaveAllFileName(mapTimeFileSystemItem);
}

void CWorkGetAllFileNameInPath::_SaveAllFileName(CFileSystemFolder::MapTimeFileSystemItemT& mapTimeFileSystemItem)
{
	CFileSystemFolder::MapTimeFileSystemItemIterT iterMap;
	CFileSystemItem* pFileSystemItem = NULL;
	std::string strFileName;
	std::ofstream fileSaveData;

	fileSaveData.open("fileSaveData.csv");		
	
	iterMap = mapTimeFileSystemItem.begin();

	while (iterMap != mapTimeFileSystemItem.end())
	{
		pFileSystemItem = (iterMap->second);
		strFileName = pFileSystemItem->getFileName();

		fileSaveData<<strFileName<<std::endl;

		iterMap++;
	}

	fileSaveData.close();
}

NS_END(TA_Base_Core)
















