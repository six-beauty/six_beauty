#include "HttpRqHandler.h"
#include <iostream>

//Ͷ��Http������Ϣ
struct tagHttpTaskData
{
	TCHAR	szUrl[512];			//����url��ַ
	TCHAR	szContext[512];		//Http post�����Context����
	WORD	contextSize;		//context�ĳ��ȣ���Http gets������Ϊ0
};

void HttpRqWorker::HandleTask(const void* pBuffer,unsigned int wSize)
{
	if(sizeof(tagHttpTaskData)!=wSize)	return;
	if(pBuffer == NULL)	return;
	tagHttpTaskData *pTaskData = (tagHttpTaskData*)pBuffer;

	try
	{
		CurlAutoRelease curlAutoRelease;
		CURL* curl = curlAutoRelease.GetPtr();
		CURLcode res;

		std::string strResult;
		{
			curl_easy_setopt(curl,CURLOPT_URL,pTaskData->szUrl);
			curl_easy_setopt(curl,CURLOPT_VERBOSE,1);								//�򿪵���
			curl_easy_setopt(curl,CURLOPT_POSTFIELDS,pTaskData->szContext);			//post����	
			curl_easy_setopt(curl,CURLOPT_POSTFIELDSIZE,pTaskData->contextSize);
			curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,CurlWriteBuffer);			//д�ص�
			curl_easy_setopt(curl,CURLOPT_WRITEDATA,&strResult);					//д�洢
			curl_easy_setopt(curl,CURLOPT_TIMEOUT,10);								//�ִ��ʱ��

			res = curl_easy_perform(curl);
		}

		if(res != CURLE_OK)
		{
			//Ͷ��Http requeset ʧ��

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
		//��Exception
		std::cout<<"HttpRqWorker::HandleTask������Exception!!"<<std::endl;
	}
}


HttpRqHandler::HttpRqHandler()
{
}

HttpRqHandler::~HttpRqHandler()
{
}

void HttpRqHandler::Init()
{
	m_SessionMaster.StartService();
}
void HttpRqHandler::StopService()
{
	m_SessionMaster.StopService();
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



