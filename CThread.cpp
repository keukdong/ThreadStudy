#include "CThread.h"
#include "process.h"
#include "TestThread.h"
// ������� Ŀ�θ��, �������
// Ŀ�ο��� ���ؽ�, ��������, �̺�Ʈ
// �������� ũ��Ƽ�� ����
CThread::CThread()
{
	m_hThread = 0;
	m_hStartEvent = 0;
	m_bLoop = false;
}

CThread::~CThread()
{
	if (m_hThread)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		std::cout << "Thread id:" << m_iID << " Close()... \n" ;
	}
}

unsigned int _stdcall CThread::ThreadFunc(void* pArg)
{
	//CThread* pThread = reinterpret_cast<CThread* >(pArg);
	CThread* pThread = (CThread*)pArg;

	// Start()�� ȣ��ɶ����� ���
	WaitForSingleObject(pThread->m_hStartEvent, INFINITE);
	do {
		pThread->Run();
	} while (pThread->m_bLoop);

	return 0;
}

//DWORD __stdcall CThread::ThreadFunc2(void* pArg)
//{
//	CThread* pThread = reinterpret_cast<CThread*>(pArg);
//
//	// Start()�� ȣ��ɶ����� ���
//	WaitForSingleObject(pThread->m_hStartEvent, INFINITE);
//	pThread->Run();
//	return 0;
//}

void CThread::Create()
{
	//1. ���ȼ���, null�̶�� chile process���� ����ȹ���
	//2. false: ���� ���� �̺�Ʈ ������Ʈ. ��ٸ��� �����尡 release�Ǹ� �ڵ����� nonsignal ������Ʈ�� ��ȯ.
	//2. �ڵ����� �������� �̺�Ʈ ������Ʈ ��������
	//3. false: �ʱ���´� nonsignaled.
	//4. �̺�Ʈ ������Ʈ �̸�
	m_hStartEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (!m_hStartEvent)
	{
		//failed to create event object
		return;
	}
	// CreateThread : "windows.h:
	// 1. ���ȼ���
	// 2. �����忡 �Ҵ�� ���û�����
	// 3. �����忡 ���� ����� �Լ��� �ּ�
	// 4. �����忡 �Ѱ��� �Ű����� ������
	// 5. ������ ���� ���� �÷��� 0: ��������� ��� ����
	//m_hThread = CreateThread(NULL, 0, CThread::ThreadFunc, this, 0, m_iID);

	// _beginthreadex : "process.h"
	// _beginthread : __cdecl : �����϶� 0���� ������ �� -1�� �����Ѵ�.
	// Ansi ǥ�� C���̺귯�� �Լ��� ȣ���� ���, _beginthread�� ����ȭ���������� �ľ����� �����������
	// _beginthreadex�� �����庰�� ���������� ������ �޸� ������ �Ҵ��Ѵ�. �̷��� ������ ������,
	// �Ҵ�� ������ �޸� �������� �����ϱ����� _endthreadex�� ¦�� �̷Ｍ �̿�.
	//https://jhb.kr/36
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, CThread::ThreadFunc, this, 0, &m_iID);
	std::cout << "Thread id:" << m_iID << " Create()... \n";
}

void CThread::Start()
{
	SetEvent(m_hStartEvent);
}

void CThread::SetLoop(bool bLoop)
{
	m_bLoop = bLoop;
}
