#include "CurlUtil.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


#include "BaseException.h"

CurlUtil* CurlUtil::m_pInstance = 0;
QMutex CurlUtil::m_mutexInstance;

CurlUtil& CurlUtil::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CurlUtil();
	}
	return (*m_pInstance);
}

void CurlUtil::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}


CurlUtil::CurlUtil()
{
	m_pCurlHandle = NULL;
	_CreateCurlHandle();
}

CurlUtil::~CurlUtil()
{
	_FreeCurlHandle();
}

void  CurlUtil::_CreateCurlHandle()
{
	QMutexLocker lock(&m_mutexCurlHandle);	
	
	if (NULL == m_pCurlHandle)
	{
		m_pCurlHandle = curl_easy_init();
	}

	if (NULL == m_pCurlHandle)
	{
		throw CBaseException(__FILE__, __LINE__, "curl_easy_init() failure");
	}
}
void  CurlUtil::_FreeCurlHandle()
{
	QMutexLocker lock(&m_mutexCurlHandle);	

	if (NULL == m_pCurlHandle)
	{
		curl_easy_cleanup(m_pCurlHandle);
		m_pCurlHandle = NULL;
	}

}

template<typename T>
void CurlUtil::_SetOpt(CURL *handle, CURLoption option, T parameter) 
{
	CURLcode code = curl_easy_setopt(handle, option, parameter);
	if (code != CURLE_OK) 
	{
		throw CBaseException(__FILE__, __LINE__, std::string("curl_easy_setopt error: ") + curl_easy_strerror(code));
	}
}

void CurlUtil::_Perform( CURL *handle )
{
	CURLcode code = curl_easy_perform(handle);
	if (code != CURLE_OK) 
	{
		throw CBaseException(__FILE__, __LINE__, std::string("curl_easy_perform error: ") + curl_easy_strerror(code));
	}
}

size_t CurlUtil::_WriteToStringCallBack( void *buffer, size_t size, size_t nmemb, void *string )
{
	const size_t sizeInBytes = size*nmemb;
	static_cast<std::string *>(string)->append(static_cast<const char * >(buffer), sizeInBytes);
	return sizeInBytes;
}

std::string CurlUtil::getUrlData( const std::string url )
{
	std::string data;
	QMutexLocker lock(&m_mutexCurlHandle);	


	_SetOpt(m_pCurlHandle, CURLOPT_URL, url.c_str());
	_SetOpt(m_pCurlHandle, CURLOPT_FOLLOWLOCATION, 1L);

	_SetOpt(m_pCurlHandle, CURLOPT_NOBODY, 0L);
	_SetOpt(m_pCurlHandle, CURLOPT_WRITEDATA, &data);
	_SetOpt(m_pCurlHandle, CURLOPT_WRITEFUNCTION, _WriteToStringCallBack);
	_Perform(m_pCurlHandle);

	return data;
}




