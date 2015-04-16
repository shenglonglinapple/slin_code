#ifndef __CLASS_PARAM_ITEM_H__
#define __CLASS_PARAM_ITEM_H__ 


#include "CFDServerCommonData.h"

#include "boost/tokenizer.hpp"

////////QT_BEGIN_NAMESPACE

class CCFDServerUtilityFun;

class CParamItem
{
public:
	//"Param=ParamValue"
	CParamItem(const std::string& strParamLine);	
	~CParamItem(void);
private:
	int _ProcessParamLine();

public:
	std::string getParamKey();
	std::string getStringParamValue();
private:
	std::string m_strParamLine;
	std::string m_strParam;
	std::string m_strParamValue;
private:
	CCFDServerUtilityFun* m_pUtilityFun;

};


//////QT_END_NAMESPACE


#endif // __CLASS_FILE_SYSTEM_ITEM_H__









