#include "StrategyFile.h"

bool StrategyFile::Init(const string& address, int name)
{
	if (!File::Init(address))
		return false;

	if (!OpenFile())
		return false;

	// divide codes into individual word putted in container respectively
	string tempstr;
	while (ReadLine(&tempstr))
	{
		vector<string> dividedStr;
		_SplitString(tempstr," ",dividedStr);

		m_code.push_back(dividedStr);
	}

	m_name = name;

	CloseFile();
	return true;
}

const StrategyFile::CodeInfo* StrategyFile::GetCode() const
{
	return &m_code;
}

int StrategyFile::GetName() const
{
	return m_name;
}

void StrategyFile::_SplitString(const std::string & s, const std::string & c, std::vector<std::string>& v)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}
