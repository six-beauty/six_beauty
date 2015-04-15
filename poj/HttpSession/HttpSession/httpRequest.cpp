#include<iostream>
#include "HttpRqHandler.h"
using namespace std;


int main()
{
	curl_global_init(CURL_GLOBAL_DEFAULT); 
	HttpRqHandler getInstance;
	getInstance.Init();
	int i;
	while(cin>>i)
	{
		if(i==0)
			break;
		getInstance.PostTask("www.baidu.com","",0);
	}

	getInstance.StopService();

	curl_global_cleanup();
	return 0;
}
