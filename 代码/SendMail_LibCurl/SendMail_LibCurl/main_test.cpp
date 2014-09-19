//#include<iostream>
//#include <cstdlib>
//#include "CSendMail.h"
//#include"curl/curl.h"
//#pragma comment(lib, "libcurld.lib") 
//
//using namespace std;
//
//#define USERNAME "sanyue9394@126.com"
//#define PASSWORD "sanyue214008"
//#define SMTPSERVER "smtp.126.com"
//#define SMTPPORT ":25" 
//#define RECIPIENT "sanyue9394@163.com"
//#define MAILFROM "sanyue9394@126.com"
//
//int main(int argc, char** argv)
//{
//   /* CSendMail sendMail(USERNAME, PASSWORD, SMTPSERVER,25, MAILFROM);    
//    sendMail.AddRecipient(RECIPIENT);
//    sendMail.AddRecipient("939445950@qq.com");
//    bool bRet=sendMail.SendMail("mytestfirst","I hate you");*/
//
//	CSendMail *pMail = new CSendMail("sanyue9394@126.com", "sanyue214008","smtp.126.com", 25, "sanyue9394@126.com");
//	pMail->AddRecipient(string("sanyue9394@163.com"));
//	bool bl=pMail->SendMail("subj","hello",5); //false
//
//    return 0; 
//}


#include <stdio.h>
#include <string.h>
#include"curl/curl.h"
#pragma comment(lib, "libcurld.lib") 
 
 
#define FROM    "<sanyue9394@126.com>"
#define TO      "<93944950@qq.com>"
#define CC      "<sanyue9394@163.org>"
 
static const char *payload_text[] = {
  "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
  "To: " TO "\r\n",
  "From: " FROM "(Example User)\r\n",
  "Cc: " CC "(Another example User)\r\n",
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n",
  "Subject: SMTP example message\r\n",
  "\r\n", /* empty line to divide headers from body, see RFC5322 */ 
  "The body of the message starts here.\r\n",
  "\r\n",
  "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
  "Check RFC5322.\r\n",
  NULL
};
 
struct upload_status {
  int lines_read;
};
 
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;
 
  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }
 
  data = payload_text[upload_ctx->lines_read];
 
  if(data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;
 
    return len;
  }
 
  return 0;
}
 
int main(void)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx;
 
  upload_ctx.lines_read = 0;
 
  curl = curl_easy_init();
  if(curl) {
    /* This is the URL for your mailserver */ 
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.126.com");
 
    /* Note that this option isn't strictly required, omitting it will result in
     * libcurl sending the MAIL FROM command with empty sender data. All
     * autoresponses should have an empty reverse-path, and should be directed
     * to the address in the reverse-path which triggered them. Otherwise, they
     * could cause an endless loop. See RFC 5321 Section 4.5.5 for more details.
     */ 
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);
 
    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */ 
    recipients = curl_slist_append(recipients, TO);
    recipients = curl_slist_append(recipients, CC);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
	curl_easy_setopt(curl, CURLOPT_USERNAME, "sanyue9394@126.com");
	curl_easy_setopt(curl, CURLOPT_PASSWORD, "sanyue214008");
    /* We're using a callback function to specify the payload (the headers and
     * body of the message). You could just use the CURLOPT_READDATA option to
     * specify a FILE pointer to read from. */ 
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
    /* Send the message */ 
    res = curl_easy_perform(curl);
 
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* Free the list of recipients */ 
    curl_slist_free_all(recipients);
 
    /* curl won't send the QUIT command until you call cleanup, so you should be
     * able to re-use this connection for additional messages (setting
     * CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and calling
     * curl_easy_perform() again. It may not be a good idea to keep the
     * connection open for a very long time though (more than a few minutes may
     * result in the server timing out the connection), and you do want to clean
     * up in the end.
     */ 
    curl_easy_cleanup(curl);
  }
 
  return (int)res;
}
