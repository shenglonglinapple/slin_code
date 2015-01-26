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
	QString m_strUserID;
	QString m_strUserName;
	QString m_strPassWord;
	QString m_strLastLoginTime;
	qint32 m_nLoginCount;
	qint32 m_nState;
};


#endif //__CLASS_USER_INFO_H__
