#include<iostream>
#include "HttpRqHandler.h"
using namespace std;


int main()
{
	curl_global_init(CURL_GLOBAL_DEFAULT); 
	HttpRqHandler getInstance;
	getInstance.PostTask("www.baidu.com","",0);

	curl_global_cleanup();
	return 0;
}
