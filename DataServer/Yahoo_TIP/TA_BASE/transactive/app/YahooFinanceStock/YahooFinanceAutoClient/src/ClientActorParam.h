#ifndef __CLASS_CLIENT_ACTOR_PARAM_HH__
#define __CLASS_CLIENT_ACTOR_PARAM_HH__

#include <QtCore/QString>

class CClientActorParam 
{ 
public: 
	CClientActorParam(); 
	virtual ~CClientActorParam(); 
public:
	CClientActorParam& operator=(const CClientActorParam& objCopy);
public:
	void setServerValue(const QString& strServerIP, quint16 nServerPort);
	void setUserValue(const QString& strUserName, const QString& strPassWord);
	void setHandleValue(qint32 nHandle);

	QString getServerIP();
	quint16 getServerPort();
	QString getUserName();
	QString getUserPWD();
	qint32 getHandle();
public:
	void logInfo(const QString& file, qint32 line);
	
private:
	void _Init();

private:
	QString m_strUserName;
	QString m_strPassWord;
	QString m_strServerIP;
	quint16 m_nServerPort;
private:
	qint32 m_nHandle;
}; 

#endif//__CLASS_CLIENT_ACTOR_PARAM_HH__



