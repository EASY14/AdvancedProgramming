#include "Game.h"

StrategyInterpreter::StrategyInterpreter()
{
	srand((int)time(0));
	m_pCode = nullptr;

	m_currentWord = 0;
	m_currentLine = 0;
}

bool StrategyInterpreter::Init(const StrategyFile::CodeInfo * code, BaseGame* game, Player* player)
{
	if ((*code).size() == 0)
	{
		ErrorOutput(L"file info is null");
		return false;
	}

	m_pCode = code;

	m_pGame = game;
	m_pPlayer = player;

	m_currentWord = 0;
	m_currentLine = 0;

	return true;
}

SELECTION StrategyInterpreter::GetSelection()
{
	m_currentLine = 0;
	m_currentWord = 1; //1
	while (true)
	{
		const string& word = (*m_pCode)[m_currentLine][m_currentWord];

		//find the second word
		//if (word == "IF")
		if (word[0] == 'I')//IF
			_IfKeyword();
		else if (word[0] == 'G')
		{
			m_currentWord += 1;
			const string& line = (*m_pCode)[m_currentLine][m_currentWord];
			_GotoLine(line);
		}
		else
			return _SeletionKeyword(word);

	}
}

void StrategyInterpreter::_IfKeyword()
{
	m_currentWord += 1; //2
	const string& word = (*m_pCode)[m_currentLine][m_currentWord];
	int intVar = 0;
	//if (word == "LASTOUTCOME") //when it is outcome enum
	if (word[0] == 'L') //when it is outcome enum
		_IfOutcomeKeyword();
	else
		_IfVariableKeyword();

	//else if (word == "ALLOUTCOMES_W"  //when it is variable
	//	|| word == "ALLOUTCOMES_X" 
	//	|| word == "ALLOUTCOMES_Y" 
	//	|| word == "ALLOUTCOMES_Z" 
	//	|| word == "ITERATIONS" 
	//	|| word == "MYSCORE"
	//	|| word == "ITERATIONS")
	//{
	//	_IfVariableKeyword();
	//}
	//else
	//	ErrorOutput(L"unidentify keyword");

	return;
}

void StrategyInterpreter::_IfOutcomeKeyword()
{
	//it must use = operator, therefore skip detect operator and compare two value
	GAMEOUTCOME lastOutcomeVar = m_pPlayer->GetLastOutcome();
	m_currentWord += 2; //4 get another one variable
	const string& word = (*m_pCode)[m_currentLine][m_currentWord];

	if (lastOutcomeVar == word[0])
	{
		m_currentWord += 2; //6 get num which indicate where it goes to
		_GotoLine((*m_pCode)[m_currentLine][m_currentWord]);
	}
	else
		_NextLine();
}

void StrategyInterpreter::_IfVariableKeyword()
{
	//firstly get the first variable and get the operator and get the second variable
	float var1 = 0.0f;
	float var2 = 0.0f;
	string word = (*m_pCode)[m_currentLine][m_currentWord]; //get variable
	var1 += _GetValue(word);
	while (true)
	{
		m_currentWord += 1;
		word = (*m_pCode)[m_currentLine][m_currentWord]; //get culculative operator
		if (word[0] == '+') // plus
		{
			m_currentWord += 1;
			word = (*m_pCode)[m_currentLine][m_currentWord]; //get variable
			var1 += _GetValue(word);//+=
		}
		else if(word[0] == '-') //minus
		{
			m_currentWord += 1;
			word = (*m_pCode)[m_currentLine][m_currentWord]; //get variable
			var1 -= _GetValue(word);//-=
		}
		else if (60 <= word[0] && word[0] <= 62)
		{
			break;//it breaks the loop means the keyword is operator used for comparison
		}
		else
		{
			ErrorOutput(L"unidentify keyword ");
			return;
		}
			
	}

	string ope = word; // < > =

	m_currentWord += 1;
	word = (*m_pCode)[m_currentLine][m_currentWord]; //get var
	var2 += _GetValue(word);
	while (true)
	{
		m_currentWord += 1;
		word = (*m_pCode)[m_currentLine][m_currentWord]; //get oper
		if (word[0] == '+') 
		{
			m_currentWord += 1;
			word = (*m_pCode)[m_currentLine][m_currentWord]; //get var
			var2 += _GetValue(word);
		}
		else if (word[0] == '-')
		{
			m_currentWord += 1;
			word = (*m_pCode)[m_currentLine][m_currentWord]; //get var
			var2 -= _GetValue(word);
		}
		else if (word[0] == 'G') //if (word == "GOTO") 
		{
			break; //GOTO it breaks the loop means the keyword is GOTO
		}
		else
		{
			ErrorOutput(L"unidentify keyword ");
			return;
		}
			
	}

	//below is for comparing two variable
	m_currentWord += 1; // num
	word = (*m_pCode)[m_currentLine][m_currentWord];// get num which indicate where it goes to
	if (ope.size() == 1) //< > =
	{
		switch (ope[0])
		{
		case '<':
			if (var1 < var2)
			{
				_GotoLine(word);
			}
			else
				_NextLine();
			break;

		case '>':
			if (var1 > var2)
			{
				_GotoLine(word);
			}
			else
				_NextLine();
			break;

		case '=':
			if (var1 == var2)
				_GotoLine(word);
			else
				_NextLine();
			break;

		default:
			ErrorOutput(L"unidentify keyword ");
			break;
		}
	}
	else if(ope.size() == 2)//<= >=
	{
		switch (ope[0])
		{
		case '<':
			if (var1 <= var2)
			{
				_GotoLine(word);
			}
			else
				_NextLine();
			break;

		case '>':
			if (var1 >= var2)
			{
				_GotoLine(word);
			}
			else
				_NextLine();
			break;

		default:
			ErrorOutput(L"unidentify keyword ");
			break;
		}
	}
}

void StrategyInterpreter::_GotoLine(const string& num)
{
	//if the first word of line is as similar as parameter, it will jump to there. 
	for (int i = 0; i < (int)(*m_pCode).size(); i++)
	{
		if ((*m_pCode)[i][0] == num)
		{
			m_currentLine = i;
			m_currentWord = 1;
			return;
		}
	}
}

void StrategyInterpreter::_NextLine()
{
	//go to next line
	m_currentWord = 1;
	m_currentLine += 1;
}

SELECTION StrategyInterpreter::_SeletionKeyword(const string & word)
{
	//if (word == "SILENCE")
	//	return SELECTION::SILENCE;
	//else if (word == "BETRAY")
	//	return SELECTION::BETRAY;
	//else if (word == "RANDOM")
	if (word[0] == 'S')
		return SELECTION::SILENCE;
	else if (word[0] == 'B')
		return SELECTION::BETRAY;
	else if (word[0] == 'R')
		return (rand() % 2 == 1) ? SELECTION::SILENCE : SELECTION::BETRAY;
	else
	{
		ErrorOutput(L"unidentify keyword");
		return SELECTION::NOCHOISE;
	}
}

float StrategyInterpreter::_GetValue(const string & word)
{
	//get the varible from game pointer by string of variable
	//if (word == "ALLOUTCOMES_W") 
	//	return m_pPlayer->GetAllOutcomeW();
	//else if (word == "ALLOUTCOMES_X")
	//	return m_pPlayer->GetAllOutcomeX();
	//else if (word == "ALLOUTCOMES_Y")
	//	return m_pPlayer->GetAllOutcomeY();
	//else if (word == "ALLOUTCOMES_Z")
	//	return m_pPlayer->GetAllOutcomeZ();
	//else if (word == "ALLOUTCOMES_A")
	//	return m_pPlayer->GetAllOutcomeA();
	//else if (word == "ALLOUTCOMES_B")
	//	return m_pPlayer->GetAllOutcomeB();
	//else if (word == "ALLOUTCOMES_C")
	//	return m_pPlayer->GetAllOutcomeC();
	//else if (word == "ITERATIONS")
	//	return m_pGame->GetIterations();
	//else if (word == "MYSCORE")
	//	return m_pPlayer->GetScore();
	//else
	//	return atoi(word.c_str());
	if (word[0] == 'A')
	{
		if(word[12] == 'W')
			return (float)m_pPlayer->GetAllOutcomeW();
		else if(word[12] == 'X')
			return (float)m_pPlayer->GetAllOutcomeX();
		else if (word[12] == 'Y')
			return (float)m_pPlayer->GetAllOutcomeY();
		else if (word[12] == 'Z')
			return (float)m_pPlayer->GetAllOutcomeZ();
		else if (word[12] == 'A')
			return (float)m_pPlayer->GetAllOutcomeA();
		else if (word[12] == 'B')
			return (float)m_pPlayer->GetAllOutcomeB();
		else if (word[12] == 'C')
			return (float)m_pPlayer->GetAllOutcomeC();
	}
	else
	{
		if(word[0] == 'I')
			return (float)m_pGame->GetIterations();
		else if(word[0] == 'M')
			return m_pPlayer->GetScore();
		else
			return (float)atoi(word.c_str());
	}
	return 0;
}


