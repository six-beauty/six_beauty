#include "./HttpSessionMaster.h"
/**********************************************************************
模块:网页交互基类
使用:1、在main中添加两个全局函数
		curl_global_init(CURL_GLOBAL_DEFAUTL);
		curl_global_cleanup();
	 2、实现一个worker子类并继承HttpSessionWorkerBase,实现HandleTask函数
	 3、把实现的worker子类作为模板类型传给HttpSessionMaster
注意：HandleTask() 函数需要保证线程安全
**********************************************************************/


HttpSessionWorkBase::HttpSessionWorkBase():m_hCompletionPort(NULL)
{
}

HttpSessionWorkBase::~HttpSessionWorkBase()
{
}

bool HttpSessionWorkBase::InitThread(HANDLE hCompletionPort)
{
	if(hCompletionPort == NULL)	
		return false;
	m_hCompletionPort = hCompletionPort;
	return true;
}

bool HttpSessionWorkBase::RepetitionRun()
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
		unsigned int uSize;
		bool bGet = pQueueService->GetTask(m_cbBuffer,uSize);

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
