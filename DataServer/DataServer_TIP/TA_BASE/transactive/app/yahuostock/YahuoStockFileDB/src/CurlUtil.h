#ifndef __CLASS_CURL_UTIL_H__
#define __CLASS_CURL_UTIL_H__

#include <iostream>  
#include <string>
#include <memory>
#include <stdexcept>
#include <string>
#include <curl/curl.h>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

class CurlUtil
{
public:
	static CurlUtil& getInstance();
	static void removeInstance();

private:
	static CurlUtil* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CurlUtil();
	virtual ~CurlUtil();
public:	
	std::string getUrlData(const std::string url);
private:	
	void  _CreateCurlHandle();
	void  _FreeCurlHandle();
	template<typename T>
	void _SetOpt(CURL *handle, CURLoption option, T parameter);
	void _Perform(CURL *handle);
	static size_t _WriteToStringCallBack(void *buffer, size_t size, size_t nmemb, void *string);


private:
	QMutex m_mutexCurlHandle;
	CURL*   m_pCurlHandle;//(curl_easy_init(), curl_easy_cleanup);


};



#endif //__CLASS_CURL_UTIL_H__
