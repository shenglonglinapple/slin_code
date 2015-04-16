#include "FileSystemItem.h"
#include <sstream>

#include "BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Test)

static const int DEF_VALUE_INT_MAXLINELEN = 10240;


CFileSystemItem::CFileSystemItem( const std::string& strFilePath )
{
	BOOST_LOG_FUNCTION();
	m_fFileFullPath = boost::filesystem::system_complete(boost::filesystem::path(strFilePath, boost::filesystem::native ));
	m_strFileFullPath = m_fFileFullPath.generic_string();//C://Sample//20121220.csv
	m_strFullFileName = m_fFileFullPath.filename().generic_string();//20121220.csv
	m_strFileName = m_fFileFullPath.stem().generic_string();//20121220
	m_strFileExten = m_fFileFullPath.extension().generic_string();//.csv
}

CFileSystemItem::~CFileSystemItem( void )
{
	BOOST_LOG_FUNCTION();

}


std::string CFileSystemItem::getFileFullPath()
{
	BOOST_LOG_FUNCTION();

	return m_strFileFullPath;
}

int CFileSystemItem::getAllLinesInFile( LstLineT& lstLine )
{
	int nFunRes = 0;
	char* pszInBuff = NULL;
	boost::filesystem::ifstream inputDataStream(m_fFileFullPath); 

	if (inputDataStream.fail())
	{
		LOG_ERROR<<"Failed to open file: "<<m_fFileFullPath.generic_string();
		nFunRes = -1;
		return nFunRes;
	}


	pszInBuff = new char[DEF_VALUE_INT_MAXLINELEN];
	memset(pszInBuff, 0, DEF_VALUE_INT_MAXLINELEN);

	// Read in all lines and add them to a list
	while ( inputDataStream.getline ( pszInBuff, DEF_VALUE_INT_MAXLINELEN ) )
	{
		std::string strLine = pszInBuff;
		//check line is not empty or commont line
		if (false == strLine.empty() && ';' != strLine[0])
		{
			lstLine.push_back(strLine);
		}	
		memset(pszInBuff, 0, DEF_VALUE_INT_MAXLINELEN);
	}//while

	// close file
	if (inputDataStream.is_open())
	{
		inputDataStream.close();
	}

	if (NULL != pszInBuff)
	{
		delete[] pszInBuff;
		pszInBuff = NULL;
	}

	return nFunRes;
}





NS_END(TA_Base_Test)
















