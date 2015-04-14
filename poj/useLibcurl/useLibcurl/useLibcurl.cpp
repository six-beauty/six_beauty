#include<iostream>
#include<string>
#include"curl/curl.h"
using namespace std;

class CurlAutoRelease
{
public:
	CurlAutoRelease(){	p = curl_easy_init();}
	~CurlAutoRelease(){	curl_easy_cleanup(p);}
	CURL *GetPtr(){	return p;}
protected:
	CURL* p;
};

UINT CurlWriteBuffer(char *buffer,UINT size,UINT nmemb,std::string* stream)
{
	UINT sizes = size*nmemb;
	if(stream == NULL) return 0;
	stream->append(buffer,sizes);
	return sizes;
}

int main()
{
	curl_global_init(CURL_GLOBAL_DEFAULT); 
	
	std::string szUrl("www.baidu.com");
	std::string szContent("");

	try
	{
		CurlAutoRelease curlAutoRelease;
		CURL* curl = curlAutoRelease.GetPtr();
		CURLcode res;

		std::string strResult;
		{
			curl_easy_setopt(curl,CURLOPT_URL,szUrl.c_str());
			curl_easy_setopt(curl,CURLOPT_VERBOSE,1);								//打开调试
			curl_easy_setopt(curl,CURLOPT_POSTFIELDS,szContent.c_str());			//post请求	
			curl_easy_setopt(curl,CURLOPT_POSTFIELDSIZE,szContent.length());
			curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,CurlWriteBuffer);			//写回调
			curl_easy_setopt(curl,CURLOPT_WRITEDATA,&strResult);					//写存储
			curl_easy_setopt(curl,CURLOPT_TIMEOUT,10);								//最长执行时间

			res = curl_easy_perform(curl);
		}

		if(res != CURLE_OK)
		{
			//投递Http requeset 失败
			std::cout<<"投递Http请求失败！"<<std::endl;
			return -1;
		}
		else
		{
			std::cout<<strResult<<std::endl;
		}
	}
	catch (...)
	{
		//出Exception
		std::cout<<"HttpRqWorker::HandleTask出现了Exception!!"<<std::endl;
	}


	curl_global_cleanup();
	return 0;
}
