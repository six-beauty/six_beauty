#include "./HttpSessionMaster.h"
/**********************************************************************
ģ��:��ҳ��������
ʹ��:1����main���������ȫ�ֺ���
		curl_global_init(CURL_GLOBAL_DEFAUTL);
		curl_global_cleanup();
	 2��ʵ��һ��worker���ಢ�̳�HttpSessionWorkerBase,ʵ��HandleTask����
	 3����ʵ�ֵ�worker������Ϊģ�����ʹ���HttpSessionMaster
ע�⣺HandleTask() ������Ҫ��֤�̰߳�ȫ
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
	//У�����
	if(m_hCompletionPort==NULL)
	{
		//��ɶ˿�δ��ʼ��
		return false;
	}
	//��������
	DWORD dwThancferred=0;
	OVERLAPPED *pOverLapped=NULL;
	HttpSessionMaster<HttpSessionWorkBase> *pQueueService=NULL;

	//�ȴ���ɶ˿�
	if(GetQueuedCompletionStatus(m_hCompletionPort,&dwThancferred,(PULONG_PTR)&pQueueService,&pOverLapped,INFINITE))
	{
		//�ж��˳�
		if (pQueueService == NULL)	return false;

		//��ȡ����
		memset(m_cbBuffer,0,sizeof(m_cbBuffer));
		unsigned int uSize;
		bool bGet = pQueueService->GetTask(m_cbBuffer,uSize);

		if(bGet==true)
		{
			//��������
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
