#include <stdio.h>
#include "curl/curl.h"
size_t read_data(void *ptr, size_t size, size_t nmemb, void *data)
{
	//    FILE *fp = (FILE *)data;
	size_t return_size = fread(ptr, size, nmemb, (FILE*)data);
	printf("write %d\n", (int)return_size);
	return return_size;

}
int main()
{
	CURL *curl;
	CURLcode res;

	FILE *fp = fopen("data.txt", "rb");
	if (fp == NULL) {
		printf("can't open \n");
		return -1;
	}
	struct curl_slist *slist=NULL;

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
		curl_easy_setopt(curl, CURLOPT_FTPSSLAUTH, CURLFTPAUTH_SSL);
		curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<sixbeauty@126.com>");    //发送者
		curl_easy_setopt(curl, CURLOPT_URL, "smtp.126.com");
		slist = curl_slist_append(slist, "<939445950@163.com>");  //接收者
		curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, slist);
		curl_easy_setopt(curl, CURLOPT_USERNAME, "sanyue9394@126.com");
		curl_easy_setopt(curl, CURLOPT_PASSWORD, "sanyue214008");
		curl_easy_setopt(curl, CURLOPT_READDATA, fp);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data);

	}
	res = curl_easy_perform(curl);

	printf("The return code is %d\n", res);

	fclose(fp);
	curl_slist_free_all(slist);
	curl_easy_cleanup(curl);

	return 0;
}