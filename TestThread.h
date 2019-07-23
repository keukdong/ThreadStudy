#pragma once
#include "CThread.h"
class CTestThread :
	public CThread
{
	// 부모의 친구는 내 친구가 아니다.
	friend class CThreadManager;

public:
	virtual void Run() override;
};

