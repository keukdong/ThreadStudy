#pragma once
#include "CThread.h"
class CTestThread :
	public CThread
{
	// �θ��� ģ���� �� ģ���� �ƴϴ�.
	friend class CThreadManager;

	// �θ��� �����ڰ� private�̰� �ڽ��� �����ڴ� ��� �ɱ�?
	// �Ҹ��ڸ� �������� ����ä��, ������ �Ŵ����� create<CTestThread>�� �����Ϸ����ϸ�
	// �����Ϸ����� CTestThread �Ҹ��ڰ� �Ͻ������� �����Ǿ��ٰ� �����ش�. 
	// ���� �����ڵ� ������ �Լ���� ���´�.
//private:
//	CTestThread() { ; }
//	~CTestThread() { ; }

public:
	virtual void Run();
};

