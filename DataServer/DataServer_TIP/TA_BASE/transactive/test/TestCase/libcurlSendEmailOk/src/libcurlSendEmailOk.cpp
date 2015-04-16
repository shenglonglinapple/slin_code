/***************************************************************************
*                                  _   _ ____  _
*  Project                     ___| | | |  _ \| |
*                             / __| | | | |_) | |
*                            | (__| |_| |  _ <| |___
*                             \___|\___/|_| \_\_____|
*
* Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution. The terms
* are also available at http://curl.haxx.se/docs/copyright.html.
*
* You may opt to use, copy, modify, merge, publish, distribute and/or sell
* copies of the Software, and permit persons to whom the Software is
* furnished to do so, under the terms of the COPYING file.
*
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express or implied.
*
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

/* This is a simple example showing how to send mail using libcurl's SMTP
* capabilities. It builds on the smtp-mail.c example to add authentication
* and, more importantly, transport security to protect the authentication
* details from being snooped.
*
* Note that this example requires libcurl 7.20.0 or above.
*/

//not support gmail.com

#define FROM    "<linshenglong888@126.com>"
#define TO      "<linshenglong777@126.com>"
#define CC      "<shenglonglin1986@gmail.com>"

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

int main(void)
{
	CURL *pCurlHandle = NULL;
	CURLcode nCurlFunRes = CURLE_OK;
	struct curl_slist* pCurlRecipients = NULL;
	struct upload_status upload_ctx;

	upload_ctx.lines_read = 0;

	pCurlHandle = curl_easy_init();
	if (NULL == pCurlHandle)
	{
		return 0;
	}


	/* This is the URL for your mailserver. Note the use of smtps:// rather
	* than smtp:// to request a SSL based connection. */
	curl_easy_setopt(pCurlHandle, CURLOPT_URL, "smtp://smtp.126.com:25");
	/* Set username and password */
	curl_easy_setopt(pCurlHandle, CURLOPT_USERNAME, "linshenglong888");
	curl_easy_setopt(pCurlHandle, CURLOPT_PASSWORD, "051335");

	
	curl_easy_setopt(pCurlHandle, CURLOPT_MAIL_FROM, FROM);

	/* Add two recipients, in this particular case they correspond to the
	* To: and Cc: addressees in the header, but they could be any kind of
	* recipient. */
	pCurlRecipients = curl_slist_append(pCurlRecipients, TO);
	pCurlRecipients = curl_slist_append(pCurlRecipients, CC);
	curl_easy_setopt(pCurlHandle, CURLOPT_MAIL_RCPT, pCurlRecipients);

	/* We're using a callback function to specify the payload (the headers and
	* body of the message). You could just use the CURLOPT_READDATA option to
	* specify a FILE pointer to read from. */
	curl_easy_setopt(pCurlHandle, CURLOPT_READFUNCTION, payload_source);
	curl_easy_setopt(pCurlHandle, CURLOPT_READDATA, &upload_ctx);
	curl_easy_setopt(pCurlHandle, CURLOPT_UPLOAD, 1L);

	/* Since the traffic will be encrypted, it is very useful to turn on debug
	* information within libcurl to see what is happening during the
	* transfer */
	curl_easy_setopt(pCurlHandle, CURLOPT_VERBOSE, 1L);

	/* Send the message */
	nCurlFunRes = curl_easy_perform(pCurlHandle);

	/* Check for errors */
	if(nCurlFunRes != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(nCurlFunRes));
	}

	/* Free the list of recipients */
	curl_slist_free_all(pCurlRecipients);

	/* Always cleanup */
	curl_easy_cleanup(pCurlHandle);

	return (int)nCurlFunRes;
}
