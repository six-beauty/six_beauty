#ifndef _SERVICE_THREAD_H
#define _SERVICE_THREAD_H

#include <atlcore.h>


//同步对象接口
struct IThreadLock
{
	//锁定函数
	virtual void Lock()=0;
	//解锁函数 
	virtual void UnLock()=0;
};

//线程接口
struct IServiceThread
{
	//状态判断
	virtual bool IsRuning()=0;
	//启动线程
	virtual bool StartThead()=0;
	//停止线程
	virtual bool StopThread(unsigned long dwWaitSeconds)=0;
	//中止线程
	virtual bool TerminateThread(unsigned long dwExitCode)=0;
};

//////////////////////////////////////////////////////////////////////////

//临界区同步类
class CThreadLock : public IThreadLock
{
	//变量定义
	private:
		CRITICAL_SECTION     m_csLock;		//临界变量

		//函数定义
	public:
		//构造函数
		inline CThreadLock() { ::InitializeCriticalSection(&m_csLock); }
		//析构函数
		inline ~CThreadLock() { ::DeleteCriticalSection(&m_csLock); }

		//功能函数
	public:
		//锁定函数
		virtual inline void Lock() { ::EnterCriticalSection(&m_csLock); }
		//解锁函数 
		virtual inline void UnLock() { ::LeaveCriticalSection(&m_csLock); }
};

//////////////////////////////////////////////////////////////////////////

//安全同步锁定句柄
class CThreadLockHandle
{
	//变量定义
	private:
		int				m_nLockCount;		//锁定计数
		IThreadLock     *m_pIThreadLock;	//锁定对象

		//函数定义
	public:
		//构造函数
		CThreadLockHandle(IThreadLock * pIThreadLock, bool bAutoLock=true);
		//析构函数
		virtual ~CThreadLockHandle();

		//功能函数
	public:
		//锁定函数
		void Lock();
		//解锁函数 
		void UnLock();
		//获取锁定次数
		int inline GetLockCount() { return m_nLockCount; }
};

//////////////////////////////////////////////////////////////////////////

//线程对象类
class CServiceThread : public IServiceThread
{
	//变量定义
	private:
		volatile bool		m_bRun;				//运行标志
		UINT				m_uThreadID;		//线程标识
		HANDLE				m_hThreadHandle;    //线程句柄

		//函数定义
	protected:
		//构造函数
		CServiceThread(void);
		//析构函数
		virtual ~CServiceThread(void);

		//接口函数
	public:
		//获取状态
		virtual bool IsRuning();
		//启动线程
		virtual bool StartThead();
		//停止线程
		virtual bool StopThread(unsigned long dwWaitSeconds=INFINITE);
		//中止线程
		virtual bool TerminateThread(unsigned long dwExitCode);

		//功能函数
	public:
		//获取标识
		UINT GetThreadID() { return m_uThreadID; }
		//获取句柄
		HANDLE GetThreadHandle() { return m_hThreadHandle; }
		//投递消息
		bool PostThreadMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);

		//事件函数
	private:
		//开始事件
		virtual bool OnThreadStratEvent() { return true; }
		//停止事件
		virtual bool OnThreadStopEvent() { return true; }

		//内部函数
	private:
		//运行函数
		virtual bool RepetitionRun()=0;
		//线程函数
		static unsigned __stdcall ThreadFunction(LPVOID pThreadData);
};

//////////////////////////////////////////////////////////////////////////

#endif

