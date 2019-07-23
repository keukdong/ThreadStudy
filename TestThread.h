#pragma once
#include "CThread.h"
class CTestThread :
	public CThread
{
	// 부모의 친구는 내 친구가 아니다.
	friend class CThreadManager;

	// 부모의 생성자가 private이고 자식의 생성자는 어떻게 될까?
	// 소멸자를 정의하지 않은채로, 스레드 매니저로 create<CTestThread>를 실행하려고하면
	// 컴파일러에서 CTestThread 소멸자가 암시적으로 삭제되었다고 말해준다. 
	// 또한 생성자도 삭제된 함수라고 나온다.
//private:
//	CTestThread() { ; }
//	~CTestThread() { ; }

public:
	virtual void Run();
};

