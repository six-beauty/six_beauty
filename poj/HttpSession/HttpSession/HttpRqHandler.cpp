#include "HttpRqHandler.h"
#include <iostream>

//投递Http请求消息
struct tagHttpTaskData
{
	TCHAR	szUrl[512];			//请求url地址
	TCHAR	szContext[512];		//Http post请求的Context参数
	WORD	contextSize;		//context的长度，若Http gets操作，为0
};

void HttpRqWorker::HandleTask(void* pBuffer,WORD wSize)
{
	if(sizeof(tagHttpTaskData)==wSize)	return;
	if(pBuffer != NULL)	return;
	tagHttpTaskData *pTaskData = (tagHttpTaskData*)pBuffer;

	try
	{
		CurlAutoRelease curlAutoRelease;
		CURL* curl = curlAutoRelease.GetPtr();
		CURLcode res;

		std::string strResult;
		{
			curl_easy_setopt(curl,CURLOPT_URL,pTaskData->szUrl);
			curl_easy_setopt(curl,CURLOPT_VERBOSE,1);								//打开调试
			curl_easy_setopt(curl,CURLOPT_POSTFIELDS,pTaskData->szContext);			//post请求	
			curl_easy_setopt(curl,CURLOPT_POSTFIELDSIZE,pTaskData->contextSize);
			curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,CurlWriteBuffer);			//写回调
			curl_easy_setopt(curl,CURLOPT_WRITEDATA,&strResult);					//写存储
			curl_easy_setopt(curl,CURLOPT_TIMEOUT,10);								//最长执行时间

			res = curl_easy_perform(curl);
		}

		if(res != CURLE_OK)
		{
			//投递Http requeset 失败

			return;
		}
		else
		{
			CThreadLockHandle lockHandle(&m_threadLock);
			std::cout<<strResult<<std::endl;
		}
	}
	catch (...)
	{
		//出Exception
		std::cout<<"HttpRqWorker::HandleTask出现了Exception!!"<<std::endl;
	}
}


HttpRqHandler::HttpRqHandler()
{

}

HttpRqHandler::~HttpRqHandler()
{

}

bool HttpRqHandler::PostTask(std::string szUrl,std::string szContext,WORD contextSize)
{
	tagHttpTaskData taskData;
	ZeroMemory(&taskData,sizeof(tagHttpTaskData));

	lstrcpyn(taskData.szUrl,szUrl.c_str(),sizeof(taskData.szUrl));
	lstrcpyn(taskData.szContext,szContext.c_str(),sizeof(taskData.szContext));
	taskData.contextSize = contextSize;

	m_SessionMaster.PostTask(&taskData,sizeof(tagHttpTaskData));

	return true;
}



