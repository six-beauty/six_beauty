#include "./HttpSessionMaster.h"

HttpSessionWorkBase::HttpSessionWorkBase(HANDLE hCompletionPort):m_hCompletionPort(hCompletionPort)
{
}

HttpSessionWorkBase::~HttpSessionWorkBase()
{
}

bool HttpSessionWorkBase::RepetionRun()
{
	//校验参数
	if(m_hCompletionPort==NULL)
	{
		//完成端口未初始化
		return false;
	}
	//变量定义
	DWORD dwThancferred=0;
	OVERLAPPED *pOverLapped=NULL;
	HttpSessionMaster<HttpSessionWorkBase> *pQueueService=NULL;

	//等待完成端口
	if(GetQueuedCompletionStatus(m_hCompletionPort,&dwThancferred,(PULONG_PTR)&pQueueService,&pOverLapped,INFINITE))
	{
		//判断退出
		if (pQueueService == NULL)	return false;

		//获取数据
		memset(m_cbBuffer,0,sizeof(m_cbBuffer));
		bool bGet = pQueueService->GetTask(m_cbBuffer,sizeof(m_cbBuffer));

		if(bGet==true)
		{
			//处理数据
			HandleTask(m_cbBuffer,dwThancferred);
		}

		return true;
	}
	return false;
}

void HttpSessionWorkBase::HandleTask(const void* pBuffer,UINT uSize)
{

}

UINT HttpSessionWorkBase::CurlWriteBuffer(char *buffer,UINT size,UINT nmemb,std::string* stream)
{
	UINT sizes = size*nmemb;
	if(stream == NULL) return 0;
	stream->append(buffer,sizes);
	return sizes;
}
