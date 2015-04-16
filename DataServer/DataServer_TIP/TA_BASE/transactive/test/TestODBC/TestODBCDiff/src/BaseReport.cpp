#include "BaseReport.h"



CBaseReport* CBaseReport::m_pInstance = 0;
// boost::mutex CBaseLogger::m_mutexInstance;
// boost::mutex CBaseLogger::m_mutexStream;

static const int  DEF_INT_BUFFSIZE = 512;
static const int  DEF_INT_MAXLINELEN = 1024*1024;
						
CBaseReport& CBaseReport::getInstance()
{	
// 	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CBaseReport();
	}
	return (*m_pInstance);
}

void CBaseReport::removeInstance()
{
// 	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


CBaseReport::CBaseReport()
{
	m_strLogFileName = DEF_Filename_OUT_BASE_REPORT;
}


CBaseReport::~CBaseReport()
{
    if (m_streamLogFile.is_open())
    {
		m_streamLogFile.close();
    }
}





void CBaseReport::deletelogFile()
{
	if (m_streamLogFile.is_open())
	{
		m_streamLogFile.close();
	}
	remove(m_strLogFileName.c_str());
	m_strLogFileName.clear();

}

int CBaseReport::setlogFile(const std::string& strLogFileName)
{
	int nFunRes = 0;
	m_strLogFileName = strLogFileName;
	if (m_streamLogFile.is_open())
	{
		m_strLogFileName.clear();
		m_streamLogFile.close();
	}
	// Open the file for appending (retain existing entries) 
	m_streamLogFile.open(m_strLogFileName.c_str(), std::ios::out | std::ios::app);
	if (m_streamLogFile.is_open())
	{
		m_streamLogFile << m_strLogFileName.c_str() << std::endl;
		m_streamLogFile.flush();
		nFunRes = 0;
	}
	else
	{
		m_streamLogFile.close();
		nFunRes = -1;
	}

	return nFunRes;
}



void CBaseReport::report(const std::string& file, int line, int level, ...)
{
// 	boost::mutex::scoped_lock lock(m_mutexStream);	

	int nGetlevel = 0;
	std::string strLogLevel;  
	int nStrLen = DEF_INT_MAXLINELEN;
	std::string logMsg;


	// Get the variable args
	va_list argPtr;

	//argPtr piont to level's pos
	va_start ( argPtr, level );
		
	// Construct the log message
	logMsg = _ConstructMessage (nStrLen, file, line, strLogLevel, argPtr);
	
	// Reset the arg pointer
	va_end ( argPtr );

	// Print the log message
	if (m_streamLogFile.is_open())
	{	 
		m_streamLogFile << logMsg.c_str();
		m_streamLogFile.flush();
	}
	else
	{
		printf("log: %s \r\n", logMsg.c_str());
	}

	return;
}




std::string CBaseReport::_ConstructMsgBody(int nStrLen, va_list args)
{
	char* format = "";
	std::string testFormat;
	std::string strMsgBody;
	char* buff = NULL;
	int ret = -1;

	format = va_arg ( args, char* );
	testFormat = format;

	// Construct message from format string and args
	strMsgBody.clear();


	buff = new char[nStrLen];
	memset(buff, 0, nStrLen);

	ret = vsnprintf ( buff, nStrLen, format, args ); 
	strMsgBody = buff;

	//message = message.insert ( 0, "    "); // Preprend indentation
	//message += "\n";

	if (NULL != buff)
	{
		delete[] buff;
		buff = NULL;
	}
	return strMsgBody;
}


std::string CBaseReport::_ConstructMessage(int nStrLen, const std::string& file, int line, std::string& strLogLevel, va_list args)
{  
	std::string strLogMsgBody;
	std::string strLogMsg; 	

	//construct log header
	//construct log body 
	strLogMsgBody = _ConstructMsgBody(nStrLen, args);

	strLogMsg = strLogMsgBody;
	//strLogMsg += "\n";

	return strLogMsg;
}

void CBaseReport::test()
{
	CBaseReport::getInstance();
	std::string strLogFile = DEF_Filename_OUT_BASE_REPORT;
	CBaseReport::getInstance().setlogFile(strLogFile);

	_Report(ReportFLInfo, 0, "param=%d", 1);


	CBaseReport::removeInstance();
}

//NS_END(TA_Base_Core)




