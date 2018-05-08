#pragma once

#include "File.h"

#ifndef _STRATEGYFILE_
#define _STRATEGYFILE_

class StrategyFile : protected File
{
public:
	//type of fileinfo
	typedef vector<vector<string>> CodeInfo;

	//initiate
	bool Init(const string& address, int name);

	//get code of strategic Language 
	const CodeInfo* GetCode() const;

	//get name of strategic file
	int GetName()const;

protected:

	//container of code of strategic language
	vector<vector<string>> m_code;

	//name of strategy file
	int m_name;

	//sperate string by c
	void _SplitString(const std::string& s, const std::string& c, std::vector<std::string>& v);
	
};


#endif // !_STRATEGYFILE_
