#include "Application.h"

#define	TITLE	"     Coursework1  Easy's Game of The Prisoner Dilemma     "

int finishedFile = 0;

int main(){
	return Application().Run();
}
//^b*[^:b#/]+.*$

Application::Application()
{
	m_currentModual = MODUAL::MENUSELECTION;

	m_mainMenuSelection = 0;

	m_mainMenu.push_back("     Create Strategy Files     ");
	m_mainMenu.push_back("    Output Create Files Log    ");
	m_mainMenu.push_back("   All Strategy Files Combat   ");
	m_mainMenu.push_back("Output Stategy Files Combat log");
	m_mainMenu.push_back("     Read Files and Combat     ");
	m_mainMenu.push_back("           E  X  I  T          ");

	m_isEsc = false;

	m_strategyCombatLog = nullptr;

	SYSTEM_INFO info;
	GetSystemInfo(&info);
	m_coreNumber = info.dwNumberOfProcessors;
	return;
}

Application::~Application()
{
	CloseHandle(m_console);
	SAFE_DELETE(m_strategyCombatLog);
}

int Application::Run()
{
	//initialisation
	if (!_Init())
		return 1;

	while (true)
	{
		char input;
		do{
			input = _getch();
		} while (m_currentModual != MENUSELECTION && input != ' ');
		switch(input)
		{
		case ' ': //key
			m_logReturnVar = 1;
			_InputHandle(SPACE);
			break;

		case -32: // arrow
			switch (_getch()) 
			{ 
			case 75:
				_InputHandle(ARROWLEFT);
				break;
			case 77:
				_InputHandle(ARROWRIGHT);
				break;
			case 72:
				_InputHandle(ARROWUP);
				break;
			case 80:
				_InputHandle(ARROWDOWN);
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}

		switch (m_currentModual)
		{
		case Application::MENUSELECTION:
			if (!_ShowMenu())
				return 1;
			break;
		case Application::STRATEGYFILECREATION:
			if (!_CreateStategyFile())
				return 1;
			break;
		case Application::ALLSTRATEGYCOMBAT:
			if (!_AllStrategyFileCombat())
				return 1;
			break;

		case Application::OUTPUTCREATEFILESLOG:
			_OutputCreateFileLog();
			break;

		case Application::OUTPUTSTRATEGYFILECOMBATLOG:
			_OutputStrategyFileLog();
			break;

		case Application::READFILESANDCOMBAT:
			_ReadFilesAndCombat();
			break;
		}

		if (m_isEsc)
			return 0;
		 
	}

	return 0;
}

bool Application::_Init()
{
	m_console = GetStdHandle(STD_OUTPUT_HANDLE);
	_ShowMenu();
	return true;
}

void Application::_InputHandle(INPUT input)
{


	switch (m_currentModual)
	{
	case Application::MENUSELECTION:
		switch (input)
		{
		case Application::SPACE:
			switch (m_mainMenuSelection)
			{
			case 0:
				m_currentModual = STRATEGYFILECREATION;
				break;

			case 1:
				m_currentModual = OUTPUTCREATEFILESLOG;
				break;

			case 2:
				m_currentModual = ALLSTRATEGYCOMBAT;
				break;

			case 3:
				m_currentModual = OUTPUTSTRATEGYFILECOMBATLOG;
				break;

			case 4:
				m_currentModual = READFILESANDCOMBAT;
				break;

			case 5:
				m_isEsc = true;
				break;
			}
			break;
		case Application::ARROWUP:
			m_mainMenuSelection -= 1;
			if (m_mainMenuSelection < 0)
				m_mainMenuSelection = m_mainMenu.size() - 1;
			break;
		case Application::ARROWDOWN:
			m_mainMenuSelection += 1;
			if (m_mainMenuSelection > (int)(m_mainMenu.size() - 1))
				m_mainMenuSelection = 0;
			break;
		default:
			break;
		}
		break;
	case Application::STRATEGYFILECREATION:
	case Application::ALLSTRATEGYCOMBAT:
	case Application::OUTPUTCREATEFILESLOG:
	case Application::OUTPUTSTRATEGYFILECOMBATLOG:
	case Application::READFILESANDCOMBAT:
		switch (input)
		{
		case Application::SPACE:
			m_currentModual = MENUSELECTION;
			break;
		}
		break;
	}
}
bool Application::_CreateStategyFile()
{
	system("CLS");

	_ShadowWindowLine(TITLE);
	COORD coord;
	coord.X = 0;
	coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);

	int fileNum = 0;
	cout << "strategy text files number : ";
	cin >> fileNum;

	//create file
	StrategyCreator* creator = StrategyCreator::GetInstance();
	if (!creator->CreateStrategyTextFile("Coursework1 StrategyFile", fileNum))
		return false;

	cout << fileNum <<" Strategy text Files Creation has been completed" << endl;
	cout << "Floder name : Coursework1 StrategyFile" << endl;
	//display all file
	const vector<string>& strategyAddress = creator->GetFileAddress();

	//output log
	m_fileCreateLog.clear();
	for (int i = 0; i < (int)strategyAddress.size(); i++)
		m_fileCreateLog += strategyAddress[i] + '\n';
	SetConsoleTextAttribute(m_console, 240);
	cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
	SetConsoleTextAttribute(m_console, 15);
	return true;
}

bool Application::_AllStrategyFileCombat()
{
	system("CLS");

	int millisecond = timeGetTime();


	StrategyCreator* creator = StrategyCreator::GetInstance();
	const vector<int>& strategyName = creator->GetFileName();
	const vector<string>& strategyAddress = creator->GetFileAddress();
	finishedFile = 0;
	SAFE_DELETE(m_strategyCombatLog);
	//if do not create files
	if (strategyName.size() == 0 || strategyAddress.size() == 0)
	{
		COORD coord; coord.X = 0; coord.Y = 6;
		SetConsoleCursorPosition(m_console, coord);
		_ShadowWindowLine(TITLE);
		SetConsoleTextAttribute(m_console, 12);
		cout << "you do not have any strategy file for combat, please create some" << endl;
		SetConsoleTextAttribute(m_console, 240);
		cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
		SetConsoleTextAttribute(m_console, 15);
		return true;
	}

	_ShadowWindowLine(TITLE);
	COORD coord;coord.X = 0;coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);
	//load all strategy file
	StrategyFileManager::GetInstance()->RemoteAll();
	for (int i = 0; i < (int)strategyAddress.size(); i++)
		StrategyFileManager::GetInstance()->CreateStrategyFile(strategyAddress[i]);

	//record the best score and relative file
	map<int, int> bestOneNameWin;
	for (int i = 0; i < (int)strategyName.size(); i++)
		bestOneNameWin[strategyName[i]] = 0;

	if (strategyName.size() >= 20) // if more than 20 files
	{
		//create thread

		//thread parameter
		int threadNum = m_coreNumber * 2 + 2;
		int filePack = strategyName.size() / threadNum;
		vector<short> *returnVar;
		vector<string> *outputStr;
		vector<map<int, int>> *bestOneNameWinArray;

		//instantialisation of thread parameter based on how many files remain
		if (filePack*threadNum != strategyName.size())
		{
			returnVar = new vector<short>(threadNum + 1, 0);
			outputStr = new vector<string>(threadNum + 1);
			bestOneNameWinArray = new vector<map<int, int>>(threadNum + 1);
		}
		else
		{
			returnVar = new vector<short>(threadNum, 0);
			outputStr = new vector<string>(threadNum);
			bestOneNameWinArray = new vector<map<int, int>>(threadNum);
		}

		//start to create thread
		vector<thread*> threads;
		for (int i = 0; i < threadNum; i++)
			threads.push_back(new thread(&Application::_CombatThread, this, 
				filePack*i, filePack*(i + 1), strategyName, &((*bestOneNameWinArray)[i]), &((*outputStr)[i]), &((*returnVar)[i])));

		//if it has remaining files
		if (filePack*threadNum != strategyName.size())
			threads.push_back(new thread(&Application::_CombatThread,this ,
				filePack*threadNum, strategyName.size(), strategyName, &((*bestOneNameWinArray)[(*bestOneNameWinArray).size() - 1]), &((*outputStr)[(*outputStr).size() - 1]), &((*returnVar)[(*returnVar).size() - 1])));

		COORD coord;coord.X = 0;coord.Y = 6;
		SetConsoleCursorPosition(m_console, coord);
		//use to show progress and wait for thread finishing
		while (true)
		{
			Sleep(100);
			cout << "progress : " << strategyName.size() << "/" << finishedFile << endl;
			bool isBreak = true;
			for (int i = 0; i < (int)(*returnVar).size(); i++)
			{
				if ((*returnVar)[i] == 1)
					return false;
				else if ((*returnVar)[i] == 0)
					isBreak = false;
			}
			if (isBreak)
				break;
		}
		vector<map<int, int>>& bestOneNameWinArray1 = *bestOneNameWinArray;
		for (int i = 0; i < (int)bestOneNameWinArray1.size(); i++) //output combat log
		{
			for (map<int, int>::iterator j = bestOneNameWinArray1[i].begin(); j != bestOneNameWinArray1[i].end(); j++)
			{
				bestOneNameWin[j->first] += j->second;
			}
		}
		m_strategyCombatLog = outputStr;

		for (int i = 0; i < (int)threads.size(); i++)
		{
			threads[i]->join();
			SAFE_DELETE(threads[i]);
		}

		SAFE_DELETE(bestOneNameWinArray);
		SAFE_DELETE(returnVar);
	}
	else
	{
		Game game;
		Player player1, player2;
		Game::GamePunishmentRule rule;
		vector<string> *outputStr;
		outputStr = new vector<string>(strategyName.size());
		//start combat
		for (int i = 0; i < (int)strategyName.size(); i++)
		{
			for (int j = i + 1; j < (int)strategyName.size(); j++)
			{
				stringstream output;
				if (!game.Init(&player1, i, &player2, j, rule))
					return false;

				if (!game.Run(200))
					return false;

				output << std::right << std::setw(5) << i << std::left << "vs" << std::setw(5) << j
					<< "  Result: Player 1 Score: " << std::left << std::setw(5) << player1.GetScore() 
					<< " ,Player 2 Score: " << std::left << std::setw(5) << player2.GetScore() << endl;

				(*outputStr)[i] += output.str();
				if (player1.GetScore() < player2.GetScore())
					bestOneNameWin[i] += 1;
				else if (player1.GetScore() > player2.GetScore())
					bestOneNameWin[j] += 1;
			}
		}
		m_strategyCombatLog = outputStr;
	}
	//get winner
	vector<map<int, int>::iterator> winners;
	winners.push_back(bestOneNameWin.begin());
	for (map<int, int>::iterator i = (++bestOneNameWin.begin()); i != bestOneNameWin.end(); i++)
	{
		if (winners[0]->second < i->second)
		{
			winners.clear();
			winners.push_back(i);
		}
		else if (winners[0]->second == i->second)
			winners.push_back(i);
	}

	File outputFile;
	outputFile.Init("CourseWork 1 Best Strategies.txt");
	outputFile.CreateFile();
	outputFile.OpenFile();
	system("CLS");
	_ShadowWindowLine(TITLE);
	coord;coord.X = 0;coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);
	//display the result
	SetConsoleTextAttribute(m_console, 12);
	cout << "all combat finish !" << endl;
	cout << "list of all winners :" << endl;
	for (int i = 0; i < (int)winners.size(); i++)
	{
		stringstream outputStr;
		outputStr << "winner strategy name : " << winners[i]->first << "  win times : " << winners[i]->second;
		cout << outputStr.str() << endl;
		
		outputFile.WriteLine(outputStr.str());
	}
	outputFile.CloseFile();
	cout << "time usage : " << (timeGetTime() - millisecond) / 1000.0f << " second"<<endl;
	SetConsoleTextAttribute(m_console, 240); 
	//time handling 100 files //106.428 //49.9 //46.9 //28.57 //25.76 //5.942
	//time handling 1000 files //2084 // 2087
	//time handling 1000 files without log //1430 // 588

	cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
	SetConsoleTextAttribute(m_console, 15);

	return true;
}

void Application::_CombatThread(int beginFile, int EndFile, const vector<int>& strategyName, map<int, int>* bestOneNameWin, string* outputString, short* returnVar)
{
	Game game;
	Player player1, player2;
	Game::GamePunishmentRule rule;
	//start combat
	for (int i = beginFile; i < EndFile; i++)
	{
		for (int j = i + 1; j < (int)strategyName.size(); j++)
		{
			if (!game.Init(&player1, i, &player2, j, rule))
			{
				*returnVar = 1;
				return;
			}

			if (!game.Run(200))
			{
				*returnVar = 1;
				return;
			}
			stringstream output;
			output << std::right << std::setw(5) << i << std::left << "vs" << std::setw(5) << j
				<< "  Result: Player 1 Score: " << std::left << std::setw(5) << player1.GetScore() 
				<< " ,Player 2 Score: " << std::left << std::setw(5) << player2.GetScore() << endl;
			(*outputString)+=output.str();
			
			if (player1.GetScore() < player2.GetScore())
				(*bestOneNameWin)[i]++;
			else if (player1.GetScore() > player2.GetScore())
				(*bestOneNameWin)[j]++;
		}
		finishedFile++;
	}
	*returnVar = 2;
}

void Application::_OutputCreateFileLog()
{
	system("CLS");
	_ShadowWindowLine(TITLE, 0);
	COORD coord; coord.X = 0; coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);
	if (m_fileCreateLog.size() == 0)
	{
		cout << "it has not any strategy text file creation outlog" << endl;
	}
	else
	{
		cout << "list of Strategy Text File" << endl;
		cout << m_fileCreateLog << endl;
	}
	SetConsoleTextAttribute(m_console, 240);
	cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
	SetConsoleTextAttribute(m_console, 15);
}

void Application::_OutputStrategyFileLog()
{
	system("CLS");
	_ShadowWindowLine(TITLE, 0);
	COORD coord; coord.X = 0; coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);
	if (m_strategyCombatLog == nullptr)
	{
		cout << "it has not any strategy combat outlog" << endl;
	}
	else
	{
		m_logReturnVar = 0;
		thread *outlogThread = new thread(&Application::_CombatOutlogThread,this,&m_logReturnVar);
		outlogThread->join();
		delete outlogThread;
	}

	SetConsoleTextAttribute(m_console, 240);
	cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
	SetConsoleTextAttribute(m_console, 15);
}

void Application::_CombatOutlogThread(short* returnVar)
{
	File outputFile;
	outputFile.Init("CourseWork 1 All strategies combat.txt");
	outputFile.CreateFile();
	outputFile.OpenFile();
	for (int i = 0; i < (int)m_strategyCombatLog->size(); i++)
	{
		cout << (*m_strategyCombatLog)[i];
		outputFile.WriteLine((*m_strategyCombatLog)[i]);
	}
	outputFile.CloseFile();
	*returnVar = -1;
}

void Application::_ReadFilesAndCombat()
{
	system("CLS");
	_ShadowWindowLine(TITLE, 0);
	COORD coord; coord.X = 0; coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);
	
	string address1;
	string address2;
	cout << "Please input first file address : ";
	cin >> address1;
	StrategyFileManager::GetInstance()->RemoteAll();
	while (!StrategyFileManager::GetInstance()->CreateStrategyFile(address1))
	{
		cout << "input Error, please enter again" << endl;
		cout << "Please input first file address : ";
		cin >> address1;
	}
	cout << "Please input second file address : ";
	cin >> address2;
	while (!StrategyFileManager::GetInstance()->CreateStrategyFile(address2))
	{
		cout << "input Error, please enter again" << endl;
		cout << "Please input second file address : ";
		cin >> address2;
	}

	Player player1, player2;
	Game game;
	if (!game.Init(&player1, 0, &player2, 1))
		return;
	if (!game.Run(200))
		return;

	cout << std::right << std::setw(5) << "first  " << std::left << "vs" << std::setw(5) << "  second"
		<< "  Result: first Score: " << std::left << std::setw(5) << player1.GetScore()
		<< " ,Player second Score: " << std::left << std::setw(5) << player2.GetScore() << endl;

	SetConsoleTextAttribute(m_console, 240);
	cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
	SetConsoleTextAttribute(m_console, 15);

}

bool Application::_ShowMenu()
{
	system("CLS");

	SetConsoleOutputCP(437); 
	_ShadowWindowLine(TITLE,3);
	int chNum = strlen("Please choose your selection (up/down arrow selection, space confirm )");
	SMALL_RECT rc;
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // console windows info
	COORD coord;
	GetConsoleScreenBufferInfo(m_console, &bInfo); // get window buffer
	rc.Left = (bInfo.dwSize.X - chNum) / 2 - 2;
	rc.Top = 0;
	rc.Right = rc.Left + chNum + 2;
	rc.Bottom = rc.Top + 4;

	
	coord.X = rc.Left + 2;
	coord.Y = rc.Top + 10;
	SetConsoleCursorPosition(m_console, coord);
	SetConsoleTextAttribute(m_console, 11);
	cout << "Please choose your selection (up/down arrow selection, space confirm )";

	chNum = strlen(m_mainMenu[0].c_str())+8; 
	rc.Left = (bInfo.dwSize.X - chNum) / 2 - 2;
	rc.Top = 0;
	rc.Right = rc.Left + chNum + 2;
	rc.Bottom = rc.Top + 4;
	for (int i = 0; i < (int)m_mainMenu.size(); i++)
	{
		coord.X = rc.Left + 2;
		coord.Y = rc.Top + 15 + i * 2;
		SetConsoleCursorPosition(m_console, coord);
		if (i != m_mainMenuSelection) 
		{
			SetConsoleTextAttribute(m_console, 15);
			cout << "    " << m_mainMenu[i] << "    " << endl;
		}
		else
		{
			SetConsoleTextAttribute(m_console, 240);
			cout << ">>>>" << m_mainMenu[i] << "<<<<" << endl;
		}
	}
	SetConsoleTextAttribute(m_console, 15);
	return true;
}

void Application::_ShadowWindowLine(char *str, int yOffset)
{
	SMALL_RECT rc;
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // console windows info
	WORD att0, att1, attText;
	int i, chNum = strlen(str);
	GetConsoleScreenBufferInfo(m_console, &bInfo); // get window buffer
	// culculate size 
	rc.Left = (bInfo.dwSize.X - chNum) / 2 - 2;
	rc.Top = yOffset;
	rc.Right = rc.Left + chNum + 2;
	rc.Bottom = rc.Top + 4;
	att0 = BACKGROUND_INTENSITY; 
	att1 = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;
	attText = FOREGROUND_RED | FOREGROUND_INTENSITY; 
													 
	COORD posShadow = { rc.Left + 1, rc.Top + 1 }, posText = { rc.Left, rc.Top };
	for (i = 0; i<5; i++)
	{
		FillConsoleOutputAttribute(m_console, att0, chNum+4 , posShadow, &m_written);
		posShadow.Y++;
	}
	for (i = 0; i<5; i++)
	{
		FillConsoleOutputAttribute(m_console, att1, chNum+4 , posText, &m_written);
		posText.Y++;
	}
	// 写文本和边框
	posText.X = rc.Left + 2;
	posText.Y = rc.Top + 2;
	WriteConsoleOutputCharacter(m_console, str, strlen(str), posText, &m_written);
	_DrawBox( rc);
	SetConsoleTextAttribute(m_console, bInfo.wAttributes); // recover
}

void Application::_DrawBox(SMALL_RECT rc) 
{
	char chBox[6];
	COORD pos;

	chBox[0] = (char)0xda; // left up
	chBox[1] = (char)0xbf; // right down
	chBox[2] = (char)0xc0; // left down
	chBox[3] = (char)0xd9; // right up
	chBox[4] = (char)0xc4; // horizontal
	chBox[5] = (char)0xb3; // vertical

	// 画边框的上 下边界
	for (pos.X = rc.Left + 1; pos.X<rc.Right - 1; pos.X++)
	{
		pos.Y = rc.Top;
		//pos.X -= 1;
		// draw upward
		WriteConsoleOutputCharacter(m_console, &chBox[4], 1, pos, &m_written);
		//pos.X += 1;
		pos.Y = rc.Bottom;
		//pos.X -= 1;
		// draw downward
		WriteConsoleOutputCharacter(m_console, &chBox[4], 1, pos, &m_written);
		//pos.X += 2;
		
	}

}
