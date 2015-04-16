#ifndef __DEF_UTILITES_EXCEPTION_H__          
#define __DEF_UTILITES_EXCEPTION_H__           

#include "core/utilities/src/UtilitiesCommonDef.h"


NS_BEGIN(TA_Base_Core)


//
struct st_UtilitesException_ErrCodeString	
{
	const int      m_nErrCode;
	const char*    m_strErrString;
};



//
enum en_UtilitesException_ErrCode
{
	UtilitesException_ErrCode_UnKnow = 0,
	UtilitesException_ErrCode_ParamError,
};



//
static const st_UtilitesException_ErrCodeString  s_UtilitesException_ErrCodeString[]=	
{   

	{
		/*m_nErrCode*/UtilitesException_ErrCode_UnKnow,
		/*m_strErrString*/("UtilitesException_ErrCode_UnKnow")
	},

	{
		/*m_nErrCode*/UtilitesException_ErrCode_ParamError,
		/*m_strErrString*/("UtilitesException_ErrCode_ParamError")
	},

}; //static const st_UtilitesException_ErrCodeString  s_UtilitesException_ErrCodeString[]

NS_END(TA_Base_Core)

#endif//__DEF_UTILITES_EXCEPTION_H__           

