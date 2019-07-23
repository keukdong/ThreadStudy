#pragma once
#include "Header.h"

// ����Ͽ� �ްԲ�
// ���� ������ Ŭ���������� ����(�ϳ���) ������ �Ѵ�.
class CThread
{
	friend class CThreadManager;

protected:
	CThread();
	virtual ~CThread() = 0;

private:
	HANDLE m_hThread;
	HANDLE m_hStartEvent;
	
	//LPDWORD
	unsigned int		m_iID;
	bool				m_bLoop;
	
private:
	static unsigned int _stdcall ThreadFunc(void* pArg);
	// createThread�� : static DWORD WINAPI ThreadFunc(void* pArg);

public:
	virtual void Create();
	virtual void Run()= 0;	

public:
	void Start();
	void SetLoop(bool bLoop);

public:
	HANDLE GetHandle()
	{
		return m_hThread;
	}

};

