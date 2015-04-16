#ifndef __CLASS_CONFIG_INFO_H__
#define __CLASS_CONFIG_INFO_H__ 


#include "core/utilities/src/UtilitiesCommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


NS_BEGIN(TA_Base_Core)

class CConfigInfo
{
public:
	static CConfigInfo& getInstance();
	static void removeInstance();

private:
	static CConfigInfo* m_pInstance;
	static boost::mutex m_mutexInstance;

private:
	CConfigInfo(void);	
	~CConfigInfo(void);

public:
	std::string getDbType();

	void logInfo();
private:
	void _LoadDefaultConfigInfo();
private:
	std::string m_strConfigFileName;
	std::string m_strDbType;


};//class


NS_END(TA_Base_Core)


#endif // __CLASS_CONFIG_INFO_H__



















