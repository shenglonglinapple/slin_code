#ifndef  __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_
#define  __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_

#include "ProjectCommonDef.h"
#include "ProjectSysInclude.h"
#include "ProjectQTInclude.h"


//////////////////////////////////////////////////////////////////////////
//static const std::string DEFVALUE_String_UserName = "CTS007";
//static const std::string DEFVALUE_String_PassWord = "Password1";
static const std::string DEFVALUE_String_UserName = "DU07";
static const std::string DEFVALUE_String_PassWord = "Changeme1";
static const bool DEFVALUE_Bool_EnableDebug = false;

//static const std::string DEFVALUE_String_ServerIP = "211.144.192.149";
static const std::string DEFVALUE_String_ServerIP = "cts.sdicfutures.com";
static const int DEFVALUE_Int_ServerPort = 9170;
static const bool DEFVALUE_Bool_Synchronous = true;
//////////////////////////////////////////////////////////////////////////


static const std::string DEFVALUE_String_OrderType_MARKET = "MARKET";
static const std::string DEFVALUE_String_OrderType_MARKET_FAK = "MARKET_FAK";
static const std::string DEFVALUE_String_OrderType_MARKET_FOK = "MARKET_FOK";
static const std::string DEFVALUE_String_OrderType_LIMIT = "LIMIT";
static const std::string DEFVALUE_String_OrderType_LIMIT_FAK = "LIMIT_FAK";
static const std::string DEFVALUE_String_OrderType_LIMIT_FOK = "LIMIT_FOK";
static const std::string DEFVALUE_String_OrderType_STOP = "STOP";
static const std::string DEFVALUE_String_OrderType_UNKNOWN = "UNKNOWN";
//////////////////////////////////////////////////////////////////////////


static const int DEFVALUE_Int_OnePage_HistoryBarNumber = 128;//1024
static const std::string DEFVALUE_String_HistoryBarType = "DAY";
static const int DEFVALUE_Int_InstrumentID = 1;//
//////////////////////////////////////////////////////////////////////////

#endif  // __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_








