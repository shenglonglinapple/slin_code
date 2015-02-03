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
	void setValue( const QString& strServerIP, quint16 nServerPort, const QString& strUserName, const QString& strPassWord );
	void setValue(qint32 nHandle);

public:
	void logInfo(const QString& file, qint32 line);
	qint32 getHandle();
private:
	void _Init();

public:
	QString m_strUserName;
	QString m_strPassWord;
public:
	QString m_strServerIP;
	quint16 m_nServerPort;
public:
	qint32 m_nHandle;
}; 

#endif//__CLASS_CLIENT_ACTOR_PARAM_HH__



