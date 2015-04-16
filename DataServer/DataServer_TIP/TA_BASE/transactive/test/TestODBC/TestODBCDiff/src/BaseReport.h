#ifndef __CLASS_BASE_REPORT_HH__
#define __CLASS_BASE_REPORT_HH__


#include "ProjectCommonData.h"


// Forward declaration
#define ReportFLInfo			        __FILE__,__LINE__

#define _Report						CBaseReport::getInstance().report

#define  DEF_Filename_OUT_BASE_REPORT   "BASE_REPORT.csv"




// Class Definition: Logger
class CBaseReport
{
public:
	static CBaseReport& getInstance();
	static void removeInstance();

private:
	static CBaseReport* m_pInstance;
// 	static boost::mutex m_mutexInstance;
// 	static boost::mutex m_mutexStream;

private:
	CBaseReport();
	~CBaseReport();

public:
	int  setlogFile(const std::string& strLogFileName);
	void deletelogFile();

	void report(const std::string& file, int line, int level, ...);
private:	
	std::string _ConstructMessage(int nStrLen, const std::string& file, int line, std::string& strLogLevel, va_list args);
														  
	std::string _ConstructMsgBody(int nStrLen, va_list args);


private:
	std::string			m_strLogFileName;
	std::ofstream		m_streamLogFile;

public:
	void test();
};



#endif // __CLASS_BASE_LOGGER_HH__

//NS_END(TA_Base_Core)




