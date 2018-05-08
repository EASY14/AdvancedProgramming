#pragma once

#include "StrategyFile.h"

#ifndef _MANAGER_
#define _MANAGER_

class StrategyFileManager
{
public:

	//singleton pattern
	static StrategyFileManager* GetInstance()
	{
		return &m_instance;
	}

	//create a file and put it into container
	bool CreateStrategyFile(const string& address);

	//search the file by name and return the code 
	const StrategyFile::CodeInfo* GetCode(int name)const;

	//remove all strategy file
	void RemoteAll();

private :

	//guarantee user only use GetInstance to get object
	StrategyFileManager();
	~StrategyFileManager();

	//prevent duplication
	StrategyFileManager& operator=(const StrategyFileManager& rhs){}

	//instance
	static StrategyFileManager m_instance;

	//binary tree
	//contain strategy file
	vector<StrategyFile*> m_container;

	//vector
	//contain strategy file
	//vector<StrategyFile*> m_container;
};

#endif // !_MANAGER_

