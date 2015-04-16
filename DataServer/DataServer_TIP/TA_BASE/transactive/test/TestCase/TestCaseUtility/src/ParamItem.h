#ifndef __CLASS_PARAM_ITEM_H__
#define __CLASS_PARAM_ITEM_H__ 


#include "UtilitiesCommonData.h"

#include "boost/tokenizer.hpp"

NS_BEGIN(TA_Base_Core)


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

};


NS_END(TA_Base_Core)


#endif // __CLASS_FILE_SYSTEM_ITEM_H__









