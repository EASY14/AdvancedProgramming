#pragma once

#include  "StrategyFile.h"

using namespace GameEnum;

#ifndef _STRATEGYINTERPRETER_
#define _STRATEGYINTERPRETER_

class BaseGame;
class Player;

class StrategyInterpreter
{
public :

	StrategyInterpreter();

	//initiate
	bool Init(const StrategyFile::CodeInfo* code, BaseGame* game, Player* player);

	//produce selection according to code of strategic language
	SELECTION GetSelection();

protected :

	//point to game 
	BaseGame* m_pGame;
	//point to player
	Player* m_pPlayer;

	//point to file information
	const StrategyFile::CodeInfo* m_pCode;

	int m_currentWord;
	int m_currentLine;
	
	//handle if key word
	void _IfKeyword();

	//handle goto key word
	void _GotoLine(const string& num);

	//goto next line
	void _NextLine();

	//handle betrary/slience/random key word
	SELECTION _SeletionKeyword(const string& word);

	//handle comparison between two variable
	void _IfVariableKeyword();

	//handle comparison between two OUTCOME enum
	void _IfOutcomeKeyword();

	//get the value by string of variable
	float _GetValue(const string& word);

};


#endif // !_STRATEGYINTERPRETER_
