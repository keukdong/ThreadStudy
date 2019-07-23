#include "CThread.h"
#include "process.h"
#include "TestThread.h"
// 스레드는 커널모드, 유저모드
// 커널에는 뮤텍스, 세마포어, 이벤트
// 유저에는 크리티컬 섹션
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

	// Start()가 호출될때까지 대기
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
//	// Start()가 호출될때까지 대기
//	WaitForSingleObject(pThread->m_hStartEvent, INFINITE);
//	pThread->Run();
//	return 0;
//}

void CThread::Create()
{
	//1. 보안수준, null이라면 chile process에게 영향안받음
	//2. false: 오토 리셋 이벤트 오브젝트. 기다리는 스레드가 release되면 자동으로 nonsignal 스테이트로 변환.
	//2. 자동으로 수동으로 이벤트 오브젝트 생성할지
	//3. false: 초기상태는 nonsignaled.
	//4. 이벤트 오브젝트 이름
	m_hStartEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (!m_hStartEvent)
	{
		//failed to create event object
		return;
	}
	// CreateThread : "windows.h:
	// 1. 보안수준
	// 2. 스레드에 할당될 스택사이즈
	// 3. 스레드에 의해 실행될 함수의 주소
	// 4. 스레드에 넘겨줄 매개변수 포인터
	// 5. 스레드 시작 시점 플레그 0: 만들어진후 즉시 실행
	//m_hThread = CreateThread(NULL, 0, CThread::ThreadFunc, this, 0, m_iID);

	// _beginthreadex : "process.h"
	// _beginthread : __cdecl : 성공일때 0으로 실패일 때 -1을 리턴한다.
	// Ansi 표준 C라이브러리 함수를 호출할 경우, _beginthread는 동기화이유ㄸ문ㅇ ㅔ안정성 보장못받지만
	// _beginthreadex는 스레드별로 내부적으로 별도의 메모리 공간을 할당한다. 이렇게 스레드 생성시,
	// 할당된 별도의 메모리 공강ㄴ을 해제하기위해 _endthreadex와 짝을 이뤄서 이용.
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
