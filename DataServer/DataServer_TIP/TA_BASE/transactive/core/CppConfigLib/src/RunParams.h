#ifndef __CLASS_RUN_PARAMS_H__
#define __CLASS_RUN_PARAMS_H__ 


#include "core/utilities/src/UtilitiesCommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


NS_BEGIN(TA_Base_Core)

class CParamItem;

class CRunParams
{
private:
	typedef std::map<std::string, CParamItem*>                      MapParamKeyParamItemT;
	typedef std::map<std::string, CParamItem*>::iterator            MapParamKeyParamItemIterT;
	typedef std::map<std::string, CParamItem*>::value_type          MapParamKeyParamItemValueTypeT;

public:
	static CRunParams& getInstance();
	static void removeInstance();

private:
	static CRunParams* m_pInstance;
	static boost::mutex m_mutexInstance;

private:
	CRunParams(void);	
	~CRunParams(void);

public:
	void setParamLine(const std::string& strLine);
	void setParamKeyAndValue(const std::string& strParamKey, const std::string& strParamValue);
	void setParamKeyAndParamItem(const std::string& strParamKey, CParamItem* pParamItem);


	bool isSetParam( const std::string& strParamKey );
	std::string getStringParamValue(const std::string& strParamKey);
	void logInfo();

private:
	void _FreeData();
private:
	boost::mutex m_mutexMapParamKeyParamItem;
	MapParamKeyParamItemT  m_MapParamKeyParamItem;


};//class


NS_END(TA_Base_Core)


#endif // __CLASS_CONFIG_INFO_H__



















