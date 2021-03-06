#include "BaseLogger.h"



CBaseLogger* CBaseLogger::m_pInstance = 0;
// boost::mutex CBaseLogger::m_mutexInstance;
// boost::mutex CBaseLogger::m_mutexStream;

static const int  DEF_INT_BUFFSIZE = 512;
static const int  DEF_INT_MAXLINELEN = 1024*1024;
						
CBaseLogger& CBaseLogger::getInstance()
{	
// 	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CBaseLogger();
	}
	return (*m_pInstance);
}

void CBaseLogger::removeInstance()
{
// 	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


CBaseLogger::CBaseLogger()
{
	m_strLogFileName = defSQLFilename_OUT_ERRORREPORT;
	m_nCurrDebugLevel = DebugError;
}


CBaseLogger::~CBaseLogger()
{
    if (m_streamLogFile.is_open())
    {
		m_streamLogFile.close();
    }
}




static DebugLevelNameValue nameValueMapping[] =
{
	{ "DebugFatal",		DebugFatal		},
	{ "DebugError",		DebugError		},
	{ "DebugWarn",		DebugWarn		},
	{ "DebugNorm",		DebugNorm		},
	{ "DebugInfo",		DebugInfo		},
	{ "DebugDebug",		DebugDebug		},
	{ "DebugSQL",        DebugSQL         },
	{ "DebugCORBA",      DebugCORBA       },
	{ "DebugMsg",	    DebugMsg	        },
	{ "DebugMsgPub",	    DebugMsgPub	    },
	{ "DebugPeriodic",   DebugPeriodic    },
	{ "DebugDatabase",	DebugDatabase	},
	{ "DebugExternal",	DebugExternal	},
	{ "DebugTrace",		DebugTrace		},
	{ NULL,			DebugInfo		}
};


std::string CBaseLogger::_GetStringDebugLevel(EDebugLevel level)
{
	std::string strLevel;
	DebugLevelNameValue* pItem = nameValueMapping;

	while (pItem->pLevelName != NULL)
	{
		if (level == pItem->nLevelValue)
		{
			strLevel = pItem->pLevelName;
			break;
		}
		pItem++;
	}

	return strLevel;
}

void CBaseLogger::deletelogFile()
{
	if (m_streamLogFile.is_open())
	{
		m_streamLogFile.close();
	}
	remove(m_strLogFileName.c_str());
	m_strLogFileName.clear();

}

int CBaseLogger::setlogFile(const std::string& strLogFileName)
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

void CBaseLogger::setlogLevel(EDebugLevel nLoglevel)
{
	m_nCurrDebugLevel = nLoglevel;
}

void CBaseLogger::log(const std::string& file, int line, EDebugLevel level, ...)
{
// 	boost::mutex::scoped_lock lock(m_mutexStream);	

	int nGetlevel = 0;
	std::string strLogLevel;  
	int nStrLen = DEF_INT_MAXLINELEN;
	std::string logMsg;

	if ( level > m_nCurrDebugLevel )
	{
		return;
	}

	// Get the variable args
	va_list argPtr;

	//argPtr piont to level's pos
	va_start ( argPtr, level );
		
	// Construct the log message
	strLogLevel = _GetStringDebugLevel( ( EDebugLevel )level );	
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




std::string CBaseLogger::_ConstructMsgBody(int nStrLen, va_list args)
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

unsigned int CBaseLogger::_PthreadSelf()
{
// 	std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
	unsigned int threadNumber = 0;
//	sscanf(threadId.c_str(), "%lx", &threadNumber);
	return threadNumber;
	//return  ::GetCurrentThreadId();
}

std::string CBaseLogger::_ConstructMsgHeader(int nStrLen, const std::string& file, int line, std::string& strLogLevel)
{  
	std::string strLogMsgHeader;
	struct timeb timebuffer;
	struct tm newtime;
	std::string strLogMsgHeaderDateTime;///t[11/01/2013 14:44:07:906]
	std::string strLogMsgHeaderLogLevel;//[INFO]
	std::string strLogMsgHeaderThreadId;//[Thrd: 6248000]
	std::string strLogMsgHeaderFileName;//d:\googledrive1987.cpp:
	std::string strLogMsgHeaderLineNumber;   //234:
	unsigned int nCurrentThreadID = 0;

	char* pszBuffLogHeader = NULL;
	pszBuffLogHeader = new char[nStrLen];
	memset(pszBuffLogHeader, 0, nStrLen);

	//construct log header

	// Retrieve Time and Date
	ftime ( &timebuffer ); 

#if defined ( SOLARIS ) || defined( LINUX )
	newtime = *localtime_r ( &timebuffer.time, &newtime );
#else
	newtime = *localtime ( &timebuffer.time );   
#endif

	strLogMsgHeaderDateTime.clear();
	if ( ( &newtime ) != NULL )
	{
		sprintf ( pszBuffLogHeader, " [%02d/%02d/%02d %02d:%02d:%02d:%03d]", 
			newtime.tm_mday, newtime.tm_mon + 1, newtime.tm_year + 1900, 
			newtime.tm_hour, newtime.tm_min, newtime.tm_sec, timebuffer.millitm );
		//strLogMsgHeaderDateTime += "\t";
		strLogMsgHeaderDateTime = pszBuffLogHeader;
	}

	strLogMsgHeaderLogLevel.clear();
	strLogMsgHeaderLogLevel += " [";
	strLogMsgHeaderLogLevel += strLogLevel;
	strLogMsgHeaderLogLevel += "]";

	// Retrieve Thread Id
	memset(pszBuffLogHeader, 0, nStrLen);
	strLogMsgHeaderThreadId.clear();


	nCurrentThreadID = _PthreadSelf();

	sprintf ( pszBuffLogHeader, " [Thrd: %d]", nCurrentThreadID);
	strLogMsgHeaderThreadId = pszBuffLogHeader;

	strLogMsgHeaderFileName.clear();
	strLogMsgHeaderFileName = " " + file;
	strLogMsgHeaderFileName += ":";

	// Convert line to string

	memset(pszBuffLogHeader, 0, nStrLen);
	sprintf(pszBuffLogHeader, "%d: ", line );
	strLogMsgHeaderLineNumber = pszBuffLogHeader;

	// Construct the log message

	strLogMsgHeader.clear();

	// Indent so that the first line of the log message is obvious when word wrapping is enabled
	//strLogMsgHeader += "\t";
	strLogMsgHeader += strLogMsgHeaderDateTime;
	strLogMsgHeader	+= strLogMsgHeaderLogLevel;
	strLogMsgHeader	+= strLogMsgHeaderThreadId;
	strLogMsgHeader	+= strLogMsgHeaderFileName;
	strLogMsgHeader	+= strLogMsgHeaderLineNumber;

	if (NULL != pszBuffLogHeader)
	{
		delete[] pszBuffLogHeader;
		pszBuffLogHeader = NULL;
	}

	return strLogMsgHeader;
}

std::string CBaseLogger::_ConstructMessage(int nStrLen, const std::string& file, int line, std::string& strLogLevel, va_list args)
{  
	std::string strLogMsgHeader;
	std::string strLogMsgBody;
	std::string strLogMsg; 	

	//construct log header
	strLogMsgHeader = _ConstructMsgHeader(DEF_INT_BUFFSIZE, file, line, strLogLevel);
	//construct log body 
	strLogMsgBody = _ConstructMsgBody(nStrLen, args);

	strLogMsg = strLogMsgHeader + strLogMsgBody;
	strLogMsg += "\n";

	return strLogMsg;
}

void CBaseLogger::testLog()
{
	CBaseLogger::getInstance();
	std::string strLogFile = "logFile.log";
	CBaseLogger::getInstance().setlogFile(strLogFile);
	CBaseLogger::getInstance().setlogLevel(DebugTrace);

	_BaseLog(BaseLogSourceFLInfo, DebugTrace, "test log main");


	CBaseLogger::removeInstance();
}

//NS_END(TA_Base_Core)




