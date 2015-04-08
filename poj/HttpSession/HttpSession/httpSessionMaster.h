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
	HttpSessionWorkBase(HANDLE hCompletionPort);
	virtual ~HttpSessionWorkBase();
private:
	//运行函数
	virtual bool RepetionRun();
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
	bool SetTaskDataSize(UINT uSize);
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
	StopService();
}

template<class T>
bool HttpSessionMaster<T>::StartService()
{
	ASSERT(m_hCompletionPort == NULL);

	try
	{
		//获取系统cpu核数
		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);
		UINT uThreadCount = SystemInfo.dwNumberOfProcessors * 2;

		//建立完成端口
		m_hCompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,SystemInfo.dwNumberOfProcessors);

		for(int i=0;i<uThreadCount;++i)
		{
			HttpSessionWorkBase *pWork = new T(m_hCompletionPort);
			if (pWork == NULL)
				throw ("工作线程创建失败!");
			m_WorkerThread.push_back(pWork);
		}
		for(int i=0;i<)
	}
	catch (...)
	{
		//出现了Exception
		ASSERT(false);
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

	for(int i=0;i<(int)m_WorkerThread.size();++i)
	{
		HttpSessionWorkBase *pWork = m_WorkerThread[i];
		pWork->StopThread();
		SafeDelete(pWork);
	}

	//关闭完成端口handle
	if(m_hCompletionPort != NULL)
	{
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;
	}
}

