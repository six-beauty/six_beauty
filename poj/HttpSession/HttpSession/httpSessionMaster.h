#pragma once

#include "ServiceThread.h"
#include <string>
#include <vector>
#include <list>

const unsigned int MAX_DATA_PACKET = 10240;

//����http�Ķ����߳���
class HttpSessionWorkBase:public CServiceThread
{
protected:
	HANDLE			m_hCompletionPort;					//��ɶ˿�
	//��������
private:
	BYTE			m_cbBuffer[MAX_DATA_PACKET];		//���ջ���

public:
	HttpSessionWorkBase();
	virtual ~HttpSessionWorkBase();
	bool InitThread(HANDLE hCompletionPort);
protected:
	//���к���
	virtual bool RepetitionRun();
	//��������,��Ҫ�ɼ̳�HttpSessionWorkBase����ʵ��
	virtual void HandleTask(const void* pBuffer,unsigned int uSize);

	static UINT CurlWriteBuffer(char *buffer,UINT size,UINT nmemb,std::string* stream);
};

 
template<class T>
class HttpSessionMaster
{
	typedef std::list<char*>	TaskQueue;
public:
	bool StartService();
	void StopService();
	void PostTask(void* pBuffer,unsigned int uSize);
public:
	HttpSessionMaster();
	~HttpSessionMaster();
	bool GetTask(void *pBuffer,unsigned int &uSize);
private:
	HANDLE				m_hCompletionPort;		
	CThreadLock			m_ThreadLock;
	TaskQueue			m_TaskQueue;		//�������
	TaskQueue			m_FreeTaskQueue;	//�����ڴ�أ���ʡnew�Ŀ���
	
	std::vector<HttpSessionWorkBase*>		m_WorkerThread;		//�����߳�
	UINT								m_uPerTaskDataSize;	//�����������ݵĴ�С
};

template<class T>
HttpSessionMaster<T>::HttpSessionMaster():m_hCompletionPort(NULL)
{
}

template<class T>
HttpSessionMaster<T>::~HttpSessionMaster()
{
}

template<class T>
bool HttpSessionMaster<T>::StartService()
{
	if(m_hCompletionPort != NULL)
		return false;

	try
	{
		//��ȡϵͳcpu����
		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);
		UINT uThreadCount = SystemInfo.dwNumberOfProcessors * 2;

		//������ɶ˿�
		m_hCompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,SystemInfo.dwNumberOfProcessors);

		for(unsigned int i=0;i<uThreadCount;++i)
		{
			HttpSessionWorkBase *pWork = new T();
			pWork->InitThread(m_hCompletionPort);
			if (pWork == NULL)
				throw ("�����̴߳���ʧ��!");
			m_WorkerThread.push_back(pWork);
		}
		for(int i=0;i< (int)m_WorkerThread.size(); ++i)
		{
			HttpSessionWorkBase* pWorkerThread = m_WorkerThread[i];
			if(pWorkerThread->StartThead() == false)
				throw ("�����߳�����ʧ��");
		}

		for(TaskQueue::iterator itr = m_TaskQueue.begin();itr != m_TaskQueue.end();++itr)
		{
			m_FreeTaskQueue.push_back(*itr);
		}
		m_TaskQueue.clear();
		m_uPerTaskDataSize = 0;
	}
	catch (...)
	{
		//������Exception
		return false;
	}
	return true;
}

template<class T>
void HttpSessionMaster<T>::StopService()
{
	if(m_hCompletionPort != NULL)
	{
		for(int i=0;i<(int)m_WorkerThread.size();++i)
			PostQueuedCompletionStatus(m_hCompletionPort,0,NULL,NULL);
	}

	unsigned int threadCount = m_WorkerThread.size();
	for(unsigned int i=0;i<threadCount;++i)
	{
		HttpSessionWorkBase *pWork = m_WorkerThread[i];
		pWork->StopThread();
		if(pWork != NULL)	delete pWork;
	}

	//�ر���ɶ˿�handle
	if(m_hCompletionPort != NULL)
	{
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;
	}
}

template<class T>
void HttpSessionMaster<T>::PostTask(void* pBuffer,unsigned int uSize)
{
	CThreadLockHandle LockHandle(&m_ThreadLock);
	if(uSize != m_uPerTaskDataSize)
	{
		//���ݵĴ�С������Ҫ��
		m_uPerTaskDataSize = uSize;
	}

	char *ptr;
	if(!m_FreeTaskQueue.empty())
	{
		ptr = m_FreeTaskQueue.back();
		m_FreeTaskQueue.pop_back();
	}
	else
	{
		ptr = new char(m_uPerTaskDataSize);
	}

	lstrcpyn(ptr,(char*)pBuffer,uSize);
	m_TaskQueue.push_front(ptr);
	PostQueuedCompletionStatus(m_hCompletionPort,uSize,(ULONG_PTR)this,NULL);
}

template<class T>
bool HttpSessionMaster<T>::GetTask(void *pBuffer,unsigned int &uSize)
{
	CThreadLockHandle LockHandle(&m_ThreadLock);
	uSize = m_uPerTaskDataSize;

	if(m_TaskQueue.empty())
		return false;

	char *ptr = m_TaskQueue.back();
	m_TaskQueue.pop_back();

	lstrcpyn((char*)pBuffer,ptr,m_uPerTaskDataSize);
	m_FreeTaskQueue.push_front(ptr);

	return true;
}




