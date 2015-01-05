#ifndef __CLASS_MSG_PROCESSER_H__
#define __CLASS_MSG_PROCESSER_H__

#include <QtCore/QObject>
#include <QtCore/QBitArray>

class CReqLogin;
class CAckLogin;
class CReqLogout;
class CAckLogout;

class CMsgProcesser
{
public:
    CMsgProcesser(void);
	~CMsgProcesser(void);
public:
	CAckLogin* processReq(const CReqLogin* pReqLogin);
	CAckLogout* processReq(const CReqLogout* pReqLogout);
};

#endif//__CLASS_MSG_PROCESSER_H__
