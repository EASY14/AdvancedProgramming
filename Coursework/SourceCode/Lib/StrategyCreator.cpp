#include "StrategyCreator.h"

StrategyCreator StrategyCreator::m_instance;

StrategyCreator::StrategyCreator()
{
	srand((int)time(0));

	m_beginLineNo = 10;
	m_LineNoGap = 10;
	m_maxLineNum = 8;
	m_minLineNum = 3;

	//initilise selection keyword
	m_selectionKeyword.push_back("SILENCE");
	m_selectionKeyword.push_back("BETRAY");
	m_selectionKeyword.push_back("RANDOM");

	//initilise variable keyword
	m_variableKeyword.push_back("ALLOUTCOMES_W ");
	m_variableKeyword.push_back("ALLOUTCOMES_X ");
	m_variableKeyword.push_back("ALLOUTCOMES_Y ");
	m_variableKeyword.push_back("ALLOUTCOMES_Z ");
	m_variableKeyword.push_back("ITERATIONS ");
	m_variableKeyword.push_back("MYSCORE ");

	//initilise outcome keyword
	m_outcomeKeyword.push_back("W ");
	m_outcomeKeyword.push_back("X ");
	m_outcomeKeyword.push_back("Y ");
	m_outcomeKeyword.push_back("Z ");

	//initilise culculative operator keyword
	m_culculativeKeyword.push_back("- ");
	m_culculativeKeyword.push_back("+ ");

	//initilise comparative operator keyword
	m_comparativeKeyword.push_back("< ");
	m_comparativeKeyword.push_back("> ");
	m_comparativeKeyword.push_back("= ");

}


bool StrategyCreator::CreateStrategyTextFile(const string& floderAddress, int number)
{
	//Create a floder
	if (!PathIsDirectory(floderAddress.c_str()))
		if (!CreateDirectory(floderAddress.c_str(), NULL))
			return false;

	m_name.clear();
	m_address.clear();

	//create certain number of strategy file
	for (int i = 0; i < number; i++)
	{
		//create a strategy file
		stringstream fileAddress;
		fileAddress << floderAddress << "\\" << i << ".txt";
		File newFile;
		newFile.Init(fileAddress.str());
		newFile.CreateFile();

		//reset random data
		m_currentLine = 0;
		m_noKeyword.clear();
		m_outPutText.clear();

		//create line number
		_RandomNo();

		//create text line by line
		for (int i = 0; i < (int)m_noKeyword.size(); i++)
			m_outPutText.push_back(_RandomStrategyText());

		//write into file
		if (!newFile.OpenFile())
			return false;
		for (int i = 0; i < (int)m_outPutText.size(); i++)
			newFile.WriteLine(m_outPutText[i]);
		newFile.CloseFile();

		m_name.push_back(i);
		m_address.push_back(fileAddress.str());
	}

	return true;
}

void StrategyCreator::_RandomNo()
{
	int lineNum = _GetRandomNum(m_minLineNum, m_maxLineNum + 1);
	for (int i = 0; i < (lineNum*2); i++)
	{
		stringstream no;
		no << m_beginLineNo + (m_LineNoGap*i) << " ";
		m_noKeyword.push_back(no.str());
	}
	
}


string StrategyCreator::_RandomStrategyText()
{
	string text;
	//0 means IF Keyword
	//1 means Selection Keyword
	if ((m_currentLine%2) == 0)
		text = m_noKeyword[m_currentLine] + _RandomIf();
	else
		text = m_noKeyword[m_currentLine] + _RandomSelection();

	m_currentLine += 1;
	return text;
}


string StrategyCreator::_RandomIf()
{
	string text;
	
	if ((rand()%2) == 0) //compare outcome
	{
		text = "IF LASTOUTCOME = " + _RandomOutcome();
	}
	else //compare variable
	{
		stringstream integer1;
		integer1 << _GetRandomNum(1, 6) << " ";
		stringstream integer2;
		integer2 << _GetRandomNum(1, 6) << " ";
		string leftInt = ((rand() % 2) == 0) ? _RandomCulculativeOperator() + integer1.str() : "";
		string rightInt = ((rand() % 2) == 0) ? _RandomCulculativeOperator() + integer2.str() : "";
		string left = _RandomVariable() + leftInt;
		string right = _RandomVariable() + rightInt;
		text = "IF " + left + _RandomComparativeOperator() + right;
	}
	text += _RandomGoto();
	return text;
}

string StrategyCreator::_RandomGoto()
{
	string text;
	//when it comes to last two line then set goes to second line
	if (m_currentLine == (m_noKeyword.size()-2))
	{
		text = "GOTO " + m_noKeyword[1];
	}
	else
	{
		int randomLine = 0;
		//randomLine = 2 + m_currentLine + (_GetRandomNum(0, ((m_noKeyword.size() - m_currentLine) / 2) - 1)) * 2;
		//when it comes to last four line then set goes to last two line
		if (m_currentLine == (m_noKeyword.size() - 4))
			randomLine = m_noKeyword.size() - 2;
		else // normally set them going to next one line or next two line
			randomLine = m_currentLine + _GetRandomNum(1, 3) * 2;
		text = "GOTO " + m_noKeyword[randomLine];
	}
	
	return text;
}

string StrategyCreator::_RandomSelection()
{
	return m_selectionKeyword[rand() % m_selectionKeyword.size()];
}

string StrategyCreator::_RandomVariable()
{
	return m_variableKeyword[rand() % m_variableKeyword.size()];
}

string StrategyCreator::_RandomOutcome()
{
	return m_outcomeKeyword[rand() % m_outcomeKeyword.size()];
}

string StrategyCreator::_RandomCulculativeOperator()
{
	return m_culculativeKeyword[rand() % m_culculativeKeyword.size()];
}

string StrategyCreator::_RandomComparativeOperator()
{
	return m_comparativeKeyword[rand()%m_comparativeKeyword.size()];
}

//get the name of file 
const vector<int>& StrategyCreator::GetFileName()const
{
	return m_name;
}

//get the address of file 
const vector<string>& StrategyCreator::GetFileAddress()const
{
	return m_address;
}
