#inlcude "TestThread.h"
#include "ThreadManager.h"

int main(void)
{
	CTestThread* pThread = CThreadManager::GetInst()->CreateThread<CTestThread>("TestThread");
	pThread->Start();
 	CThreadManager::DestroyInst();
  return 0;
}
