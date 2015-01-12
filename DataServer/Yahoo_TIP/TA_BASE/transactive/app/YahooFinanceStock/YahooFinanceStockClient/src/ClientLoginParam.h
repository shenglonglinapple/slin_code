#ifndef __CLASS_CLIENT_LOGIN_PARAM_HH__
#define __CLASS_CLIENT_LOGIN_PARAM_HH__



#include <QtCore/QString>
//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CClientLoginParam 
{ 
public: 
	CClientLoginParam(); 
	virtual ~CClientLoginParam(); 
public:
	CClientLoginParam& operator=(const CClientLoginParam& objCopy);
public:
	void setDefaultValue();
	void logInfo(const QString& file, qint32 line);
	qint32 getHandle();
	void setValue( const QString& strUserName, const QString& strPassWord , const QString& strServerIP, const qint32& nServerPort);
public:
	QString m_strUserName;
	QString m_strPassWord;
public:
	QString m_strServerIP;
	qint32 m_nServerPort;
public:
	qint32 m_nHandle;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_CLIENT_LOGIN_PARAM_HH__



