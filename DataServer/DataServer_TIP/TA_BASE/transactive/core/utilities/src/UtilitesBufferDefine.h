#ifndef  __DEF__UTILITIES_COMMON_DEF_H_
#define  __DEF__UTILITIES_COMMON_DEF_H_

#include "core/utilities/src/UtilitiesCommonDef.h"

//////////////////////////////////////////////////////////////////////////
///#define
//////////////////////////////////////////////////////////////////////////



NS_BEGIN(TA_Base_Core) 

//-function
//---------------------------------------------------------------

#define DEF_DELETE_ARRAY(pArray)		if (pArray) { delete [](pArray); (pArray) = NULL; }
#define DEF_DELETE(p)					if (p) { delete (p); (p) = NULL; }

//---------------------------------------------------------------




//---------------------------------------------------------------




NS_END(TA_Base_Core)

#endif  // __DEF__UTILITIES_COMMON_DEF_H_











