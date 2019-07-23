#pragma once
#include "Header.h"
class CThreadManager
{
private:
	CThreadManager(){ ; }
	~CThreadManager();

private:
	// 정적멤버변수는 클래스 내부에서 =값으로 초기화가 불가능하므로
	// 클래스 외부에서 전역 변수처럼 초기화 시켜야한다. 
	static CThreadManager* m_pInst;
	std::unordered_map<std::string, class CThread*> m_mapThread;

public:
	static CThreadManager* GetInst()
	{
		if(m_pInst == nullptr)
		{
			m_pInst = new CThreadManager();
		}
		return m_pInst;
	}
	static void DestroyInst()
	{
		if (m_pInst)
			delete m_pInst;
	}

public:
	class CThread* FindThread(std::string strName);

	template <typename T>
	T* CreateThread(const std::string& strName)
	{
		T* pThread = (T*)FindThread(strName);

		if (pThread)
			return pThread;

		pThread = new T;		// 디폴트 생성자 호출
		// pThread = new T();   : CTestThread(), ~CTestThread() 명시적 선언, 정의

		pThread->Create();

		m_mapThread.insert(make_pair(strName, pThread));

		return pThread;
	}

	template<typename ThreadType>
	ThreadType* FindThread(std::string strName)
	{
		std::unordered_map<std::string, class CThread*>::iterator iter = m_mapThread.find(strName);
		std::unordered_map<std::string, class CThread*>::iterator iterEnd = m_mapThread.end();

		if (iter == iterEnd)
			return nullptr;

		if (typeid(iterEnd) == typeid(ThreadType))
			return iter->second;

		return nullptr;
	}
};

