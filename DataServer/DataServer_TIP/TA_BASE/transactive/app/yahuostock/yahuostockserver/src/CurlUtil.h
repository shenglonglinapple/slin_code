#ifndef __CLASS_CURL_UTIL_H__
#define __CLASS_CURL_UTIL_H__

#include <iostream>  
#include <string>
#include <memory>
#include <stdexcept>
#include <string>
#include <curl/curl.h>
#include <boost/shared_ptr.hpp>

class CurlUtil
{
public:
	CurlUtil();
	virtual ~CurlUtil();
public:	
	static boost::shared_ptr<CURL> createCurlHandle();//std::shared_ptr

	template<typename T>
	static void setOpt(CURL *handle, CURLoption option, T parameter);

	static void perform(CURL *handle);

	static size_t writeToStringCallBack(void *buffer, size_t size, size_t nmemb, void *string);

	static std::string getUrlData(const std::string url);

	//--


};



#endif //__CLASS_YAHUO_REQACK_H__
