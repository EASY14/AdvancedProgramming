#include "StrategyFileManager.h"

StrategyFileManager StrategyFileManager::m_instance;

StrategyFileManager::StrategyFileManager()
{
	
}

StrategyFileManager::~StrategyFileManager()
{
	RemoteAll();
}

//binary tree
bool StrategyFileManager::CreateStrategyFile(const string & address)
{
	StrategyFile* strategyfile = new StrategyFile();
	if (!strategyfile->Init(address, m_container.size()))
		return false;
	//m_container[name] = strategyfile;
	m_container.push_back(strategyfile);
	return true;
}

const StrategyFile::CodeInfo* StrategyFileManager::GetCode(int name)const
{
	if (name < 0 || name >= (int)m_container.size())
		return nullptr;
	else
		return m_container[name]->GetCode();
}

void StrategyFileManager::RemoteAll()
{
	for (int i = 0; i < (int)m_container.size(); i++)
	{
		delete m_container[i];
	}
	m_container.clear();
}


//vector
//bool StrategyFileManager::CreateStrategyFile(const string & address, const string& name)
//{
//	StrategyFile* strategyfile = new StrategyFile();
//	if (!strategyfile->Init(address, name))
//		return false;
//	m_container.push_back(strategyfile);
//	return true;
//}
//
//const StrategyFile::CodeInfo* StrategyFileManager::GetCode(const string & name)const
//{
//	for (int i = 0; i < (int)m_container.size(); i++)
//	{
//		if (m_container[i]->GetName() == name)
//			return m_container[i]->GetCode();
//	}
//	return nullptr;
//}
//
//void StrategyFileManager::Remote(const string & name)
//{
//	for (vector<StrategyFile*>::iterator i = m_container.begin(); i != m_container.end(); i++)
//	{
//		if ((*i)->GetName() == name)
//		{
//			SAFE_DELETE((*i));
//			m_container.erase(i);
//			return;
//		}
//	}
//}
//
//void StrategyFileManager::RemoteAll()
//{
//	for (vector<StrategyFile*>::iterator i = m_container.begin(); i != m_container.end(); i++)
//	{
//		SAFE_DELETE((*i));
//	}
//	m_container.clear();
//}