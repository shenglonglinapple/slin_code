#ifndef __CLASS_CLIENT_LOGIN_PARAM_HH__
#define __CLASS_CLIENT_LOGIN_PARAM_HH__



#include <string>
//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CClientLoginParam 
{ 
public: 
	CClientLoginParam(); 
	virtual ~CClientLoginParam(); 
public:
	CClientLoginParam& operator=(const CClientLoginParam& clinetLoginParam);
public:
	void setDefaultValue();
	void logInfo(const std::string& file, int line);

public:
	std::string m_strUserName;
	std::string m_strPassWord;
	bool m_bEnableDebug;
public:
	std::string m_strServerIP;
	int m_nServerPort;
	bool m_bSynchronous;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_NODE_HH__



