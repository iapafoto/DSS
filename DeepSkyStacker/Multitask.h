#ifndef __MULTITASK_H__
#define __MULTITASK_H__

const DWORD				WM_MT_PROCESS	= WM_USER+1;
const DWORD				WM_MT_STOP		= WM_USER+2;

class CMultitask
{
protected :
	CComAutoCriticalSection	m_CriticalSection;
	std::vector<HANDLE>		m_vThreads;
	std::vector<DWORD>		m_vThreadIds;
	std::vector<HANDLE>		m_vEvents;

protected :
	LONG	GetNrThreads()
	{
		return (LONG)m_vThreads.size();
	};

public :
	CMultitask()
	{
	};

	virtual ~CMultitask()
	{
		CloseAllThreads();
	};

	static LONG	GetNrProcessors(bool bReal = false);
	static void	SetUseAllProcessors(bool bUseAll);
	static bool	GetReducedThreadsPriority();
	static void	SetReducedThreadsPriority(bool bReduced);

	HANDLE	GetThreadEvent(DWORD dwThreadId)
	{
		HANDLE			hResult = nullptr;

		for (size_t i = 0;(i<m_vThreadIds.size()) && !hResult;i++)
		{
			if (dwThreadId == m_vThreadIds[i])
				hResult = m_vEvents[i];
		};

		return hResult;
	};

	void	CloseAllThreads();
	void	StartThreads(LONG lNrThreads = 0);
	HANDLE	GetAvailableThread();
	DWORD	GetAvailableThreadId();

	virtual bool	DoTask(HANDLE hEvent)   = 0;
	virtual bool	Process() = 0;
};

#endif // __MULTITASK_H__