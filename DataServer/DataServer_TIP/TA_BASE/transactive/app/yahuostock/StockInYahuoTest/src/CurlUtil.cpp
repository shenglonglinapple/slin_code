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

CurlUtil::CurlUtil()
{

}

CurlUtil::~CurlUtil()
{

}

boost::shared_ptr<CURL> CurlUtil::createCurlHandle()
{
		boost::shared_ptr<CURL> curlHandle(curl_easy_init(), curl_easy_cleanup);

		if (curlHandle.get() == NULL) 
		{
			throw CBaseException(__FILE__, __LINE__, "curl_easy_init() failure");
		}
		return curlHandle;


}

template<typename T>
void CurlUtil::setOpt(CURL *handle, CURLoption option, T parameter) 
{
	CURLcode code = curl_easy_setopt(handle, option, parameter);
	if (code != CURLE_OK) 
	{
		throw CBaseException(__FILE__, __LINE__, std::string("curl_easy_setopt error: ") + curl_easy_strerror(code));
	}
}

void CurlUtil::perform( CURL *handle )
{
	CURLcode code = curl_easy_perform(handle);
	if (code != CURLE_OK) 
	{
		throw CBaseException(__FILE__, __LINE__, std::string("curl_easy_perform error: ") + curl_easy_strerror(code));
	}
}

size_t CurlUtil::writeToStringCallBack( void *buffer, size_t size, size_t nmemb, void *string )
{
	const size_t sizeInBytes = size*nmemb;
	static_cast<std::string *>(string)->append(static_cast<const char * >(buffer), sizeInBytes);
	return sizeInBytes;
}

std::string CurlUtil::getUrlData( const std::string url )
{
	boost::shared_ptr<CURL> curlHandle = createCurlHandle();
	setOpt(curlHandle.get(), CURLOPT_URL, url.c_str());
	setOpt(curlHandle.get(), CURLOPT_FOLLOWLOCATION, 1L);

	std::string data;
	setOpt(curlHandle.get(), CURLOPT_NOBODY, 0L);
	setOpt(curlHandle.get(), CURLOPT_WRITEDATA, &data);
	setOpt(curlHandle.get(), CURLOPT_WRITEFUNCTION, writeToStringCallBack);
	perform(curlHandle.get());

	return data;
}




