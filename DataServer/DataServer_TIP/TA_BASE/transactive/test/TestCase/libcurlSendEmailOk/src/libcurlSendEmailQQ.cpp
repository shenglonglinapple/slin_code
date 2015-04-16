#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <fstream>
#include <string>
using namespace std;

#define  DEF_FILE_SENDER    ".\\SparkHo\\sender.txt"
#define  DEF_FILE_ETMP      ".\\SparkHo\\etmp.txt"
#define  DEF_FILE_EMAIL     ".\\SparkHo\\email.txt"


#define FROM       "<linshenglong777@126.com>"
//#define TO         "<linshenglong888@126.com>"
#define TO         "<shenglonglin1986@gmail.com>"
#define CC         "<shenglonglin1986@gmail.com>"

static const char *payload_text[] = 
{
	"Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
	"To: " TO "\r\n",
	"From: " FROM "(Example User)\r\n",
	"Cc: " CC "(Another example User)\r\n",
	"Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n",
	"Subject: SMTP SSL example message\r\n",
	"\r\n", /* empty line to divide headers from body, see RFC5322 */
	"The body of the message starts here.\r\n",
	"\r\n",
	"It could be a lot of lines, could be MIME encoded, whatever.\r\n",
	"Check RFC5322.\r\n",
	NULL
};

struct upload_status 
{
	int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
	struct upload_status *upload_ctx = (struct upload_status *)userp;
	const char *data;

	if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) 
	{
		return 0;
	}

	data = payload_text[upload_ctx->lines_read];

	if(data) 
	{
		size_t len = strlen(data);
		memcpy(ptr, data, len);
		upload_ctx->lines_read++;
		return len;
	}
	return 0;
}




//1）我们可以把发件人的帐号和密码，放到一个txt文件里，然后通过下面的函数读出来：
int getsender(char * strUser,char * strSrv,char * strPass)
{
	char sbuf[100],*token;
	ifstream _sfile(DEF_FILE_SENDER); //从sender.txt里读取发件人资料
	if(!_sfile)
	{
		_sfile.close();
		return -1;
	}
	_sfile.seekg(0, ios::beg);
	_sfile.getline(sbuf,100); //读取第一行，如sparkho@qq.com
	token = strtok(sbuf,"@");
	strcpy(strUser, token);
	token = strtok(NULL,"@");
	strcpy(strSrv, token);
	_sfile.getline(sbuf,100); //读取第二行，密码：如1234567890
	strcpy(strPass, sbuf);
	_sfile.close();
	return 1;
}

//2）回调函数，读取发件内容，供libcurl调用：
size_t read_data(void *ptr, size_t size, size_t nmemb, void *data)
{
	FILE *fp = (FILE *)data;
	size_t return_size = fread(ptr, size, nmemb, fp);
	return return_size;
} 

//3）libcurl发邮件的主函数：
int curlMail()
{
	struct upload_status upload_ctx;

	upload_ctx.lines_read = 0;

	char strUser[100],strPass[100],strSrv[100];
	char ebuf[100],RevList[100];
	getsender(strUser, strSrv, strPass);                                      //从sender.txt里读取发件人资料
	//std::string strfrom = (std::string)strUser+"@"+(std::string)strSrv;           //发送人邮址
	std::string strfrom = (std::string)strUser+"@"+(std::string)strSrv;           //发送人邮址
	//string SrvAdd = "smtp://smtp."+(string)strSrv;                   //邮件服务器地址
	//std::string SrvAdd = "smtps://smtp."+(std::string)strSrv;                   //邮件服务器地址
	std::string SrvAdd = "smtp://smtp.126.com";//+(std::string)strSrv;                   //邮件服务器地址
	FILE *fp = fopen(DEF_FILE_ETMP, "rb");               //读取发件内容
	if (fp == NULL) return -1;
	// 初始化libcurl
	CURL *pCurlHandle;
	CURLcode return_code,res;
	//return_code = curl_global_init(CURL_GLOBAL_WIN32);
	//if (CURLE_OK != return_code) return -1;
	struct curl_slist *slist=NULL;
	ifstream _efile(DEF_FILE_EMAIL);                            //读取收件人email地址的列表
	if(!_efile)
	{
		_efile.close();
	}
	else
	{
		while(_efile.getline(ebuf,100))
		{
			sprintf(RevList,"<%s>",ebuf);
			slist = curl_slist_append(slist, RevList);  //邮件接收列表
		}
		_efile.close();
	}
	pCurlHandle = curl_easy_init();
	if(pCurlHandle)
	{
		curl_easy_setopt(pCurlHandle, CURLOPT_URL, SrvAdd.c_str());                                       //邮件服务器地址
		curl_easy_setopt(pCurlHandle, CURLOPT_USERNAME, strUser);                                       //用户帐号
		curl_easy_setopt(pCurlHandle, CURLOPT_PASSWORD, strPass);                                      //用户密码
		curl_easy_setopt(pCurlHandle, CURLOPT_MAIL_FROM, FROM);                          //发送人邮址
		curl_easy_setopt(pCurlHandle, CURLOPT_MAIL_RCPT, slist);                                           //收件人列表

 		curl_easy_setopt(pCurlHandle, CURLOPT_READFUNCTION, read_data);  
 		curl_easy_setopt(pCurlHandle, CURLOPT_READDATA, fp);

		//curl_easy_setopt(pCurlHandle, CURLOPT_READFUNCTION, payload_source);
		//curl_easy_setopt(pCurlHandle, CURLOPT_READDATA, &upload_ctx);
		curl_easy_setopt(pCurlHandle, CURLOPT_UPLOAD, 1L);


		curl_easy_setopt(pCurlHandle, CURLOPT_VERBOSE, 1L);

		//curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
		//curl_easy_setopt(pCurlHandle, CURLOPT_FTPSSLAUTH, CURLFTPAUTH_SSL);
                         //回调函数，用于读发送内容
	}
	res = curl_easy_perform(pCurlHandle);
	fclose(fp);
	curl_slist_free_all(slist);
	curl_easy_cleanup(pCurlHandle);
	//curl_global_cleanup();
	return 1;
}


int main()
{
	curlMail();
}




