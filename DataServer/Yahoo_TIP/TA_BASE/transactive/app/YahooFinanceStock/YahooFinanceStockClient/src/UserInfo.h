#ifndef __CLASS_USER_INFO_H__
#define __CLASS_USER_INFO_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

class CUserInfo
{
public:
	enum EUserState
	{
		UserState_OFFLINE,
		UserState_ONLINE,
	};
public:
	CUserInfo();
	virtual ~CUserInfo();
public:
	CUserInfo& operator=(const CUserInfo& objectCopy);
private:
	void _Init();
public:
	void setUseID(const QString& strUserName, const QString& strPassWord);
	void resetLoginTime();
public:
	QString m_strUSEID;
	QString m_strUSERNAME;
	QString m_strPASSWORD;
	QString m_strLASTLOGINTIME;
	qint32 m_nLOGINCOUNT;
	qint32 m_nSTATE;
};


#endif //__CLASS_USER_INFO_H__
