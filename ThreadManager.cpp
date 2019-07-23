#include "ThreadManager.h"
#include "CThread.h"

CThreadManager* CThreadManager::m_pInst = nullptr;

CThreadManager::~CThreadManager()
{
	auto iter = m_mapThread.begin();
	auto iterEnd = m_mapThread.end();

	for (; iter != iterEnd; iter++)
	{
		WaitForSingleObject(iter->second->GetHandle(), INFINITE);
		delete iter->second;
	}
	m_mapThread.clear();
}

CThread* CThreadManager::FindThread(std::string strName)
{
	std::unordered_map<std::string, CThread*>::iterator iter = m_mapThread.find(strName);
	std::unordered_map<std::string, CThread*>::iterator iterEnd = m_mapThread.end();

	if(iter == iterEnd)
		return nullptr;

	return iter->second;
}

