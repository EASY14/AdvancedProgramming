#pragma once

#include "File.h"

#ifndef _STRATEGYCREATOR_
#define _STRATEGYCREATOR_

class StrategyCreator
{
public :

	//singleton pattern
	static StrategyCreator* GetInstance()
	{
		return &m_instance;
	}

	//create strategy text file in given folder
	bool CreateStrategyTextFile(const string& floderAddress, int number = 10);
	
	//get the name of file 
	const vector<int>& GetFileName()const;

	//get the address of file 
	const vector<string>& GetFileAddress()const;

protected :

	//guarantee user only use GetInstance to get object
	StrategyCreator();
	virtual ~StrategyCreator(){}

	//prevent duplication
	StrategyCreator& operator=(const StrategyCreator& rhs) {}

	//instance
	static StrategyCreator m_instance;

	//store name
	vector<int> m_name;

	//store adress
	vector<string> m_address;

	//lines of code
	vector<string> m_outPutText;
	
	//the number of very beginning line
	int m_beginLineNo;

	//two line gap
	int m_LineNoGap;

	//minimum number of lines 
	int m_minLineNum;

	//maximum number of lines 
	int m_maxLineNum;

	//current line
	int m_currentLine;

	//store all no of lines
	vector<string> m_noKeyword;

	//store all selection string
	vector<string> m_selectionKeyword;

	//store all variable string
	vector<string> m_variableKeyword;

	//store all outcome string
	vector<string> m_outcomeKeyword;

	//store all culculative operator keyword
	vector<string> m_culculativeKeyword;

	//store all comparative operator keyword
	vector<string> m_comparativeKeyword;

	//randomly create Strategy Text
	string _RandomStrategyText();

	//randomly create no of lines 
	void _RandomNo();

	//randomly create if string
	string _RandomIf();

	//randomly create goto string
	string _RandomGoto();

	//randomly create selection string
	string _RandomSelection();

	//randomly create variable string
	string _RandomVariable();

	//randomly create outcome string
	string _RandomOutcome();

	//randomly create culculative operator string
	string _RandomCulculativeOperator();

	//randomly create Comparative operator string
	string _RandomComparativeOperator();

	//Get random number between a[include] and b[exclude];
	template<typename type>
	type _GetRandomNum(type a, type b)
	{
		return (rand() % (abs(a - b))) + a;
	}

};


#endif // !_STRATEGYCREATOR_