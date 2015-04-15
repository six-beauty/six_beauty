#pragma once

#include "ServiceThread.h"
#include <string>
#include <vector>
#include <list>

const unsigned int MAX_DATA_PACKET = 10240;

//处理http的队列线程类
class HttpSessionWorkBase:public CServiceThread
{
protected:
	HANDLE			m_hCompletionPort;					//完成端口
	//辅助变量
private:
	BYTE			m_cbBuffer[MAX_DATA_PACKET];		//接收缓冲

public:
	HttpSessionWorkBase();
	virtual ~HttpSessionWorkBase();
	bool InitThread(HANDLE hCompletionPort);
protected:
	//运行函数
	virtual bool RepetitionRun();
	//工作函数,需要由继承HttpSessionWorkBase的类实现
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
	TaskQueue			m_TaskQueue;		//任务队列
	TaskQueue			m_FreeTaskQueue;	//任务内存池，节省new的开销
	
	std::vector<HttpSessionWorkBase*>		m_WorkerThread;		//工作线程
	UINT								m_uPerTaskDataSize;	//单个任务数据的大小
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
		//获取系统cpu核数
		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);
		UINT uThreadCount = SystemInfo.dwNumberOfProcessors * 2;

		//建立完成端口
		m_hCompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,SystemInfo.dwNumberOfProcessors);

		for(unsigned int i=0;i<uThreadCount;++i)
		{
			HttpSessionWorkBase *pWork = new T();
			pWork->InitThread(m_hCompletionPort);
			if (pWork == NULL)
				throw ("工作线程创建失败!");
			m_WorkerThread.push_back(pWork);
		}
		for(int i=0;i< (int)m_WorkerThread.size(); ++i)
		{
			HttpSessionWorkBase* pWorkerThread = m_WorkerThread[i];
			if(pWorkerThread->StartThead() == false)
				throw ("工作线程启动失败");
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
		//出现了Exception
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

	//关闭完成端口handle
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
		//数据的大小不符合要求
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




