#include "Application.h"

#define	TITLE	"     Coursework2  Easy's Game of The Prisoner Dilemma     "

int finishedFile = 0;
int finishedfile2 = 0;

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
	//m_mainMenu.push_back("     best strategy present     ");
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
		//case Application::BESTSTRATEGYPRESENT:
		//	_BeststrategyPresent();
		//	break;
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
			//case 4:
			//	m_currentModual = BESTSTRATEGYPRESENT;
			//	break;

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
	//case Application::BESTSTRATEGYPRESENT:
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

	//int fileNum = 0;
	//cout << "strategy text files number : ";
	//cin >> fileNum;

	//create file
	StrategyCreator* creator = GangStrategyCreator::GetInstance();
	if (!creator->CreateStrategyTextFile("Coursework2 StrategyFile", 10))
		return false;

	cout << 10 <<" Strategy text Files Creation has been completed" << endl;
	cout << "Floder name : Coursework2 StrategyFile" << endl;
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

	StrategyCreator* creator = GangStrategyCreator::GetInstance();
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
	map<string, int> bestOneNameWin;

	//create thread
	//thread parameter
	int threadNum = 10;
	vector<short> *returnVar;
	vector<string> *outputStr;
	vector<vector<string>> *bestCombinationArray;
	vector<float>	   *bestSocreArray;
	vector<float>	   *averageScoreArray;

	returnVar = new vector<short>(threadNum, 0);
	outputStr = new vector<string>(threadNum);
	bestCombinationArray = new vector<vector<string>>(threadNum);
	bestSocreArray = new vector<float>(threadNum);
	averageScoreArray = new vector<float>(threadNum);

	//start to create thread
	vector<thread*> threads;
	for (int i = 0; i < threadNum; i++)
		threads.push_back(new thread(&Application::_CombatThread, this,
			i % 5, i <= 4 ? true : false,&((*bestCombinationArray)[i]), &((*bestSocreArray)[i]), &((*averageScoreArray)[i]),&((*outputStr)[i]), &((*returnVar)[i])));
	// 0 1 0 1 0 1 0 1 0 1
	coord.X = 0;coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);
	//use to show progress and wait for thread finishing
	while (true)
	{
		Sleep(100);
		cout << "progress : " << 5*5*5*5*5*10 << "/" << finishedFile << endl;
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
	//put output message into another pointer
	m_strategyCombatLog = outputStr;

	//delete thread
	for (int i = 0; i < (int)threads.size(); i++)
	{
		threads[i]->join();
		SAFE_DELETE(threads[i]);
	}

	//get winner
	system("CLS");
	_ShadowWindowLine(TITLE);
	coord.X = 0;coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);
	//display the result
	SetConsoleTextAttribute(m_console, 12);
	cout << "all combat finish !" << endl;
	cout << "list of all winners :" << endl;

	File outputFile;
	outputFile.Init("CourseWork 2 Best Strategies Combination.txt");
	outputFile.CreateFile();
	outputFile.OpenFile();

	vector<int> possibility = { 0,5,10,15,20 };
	for (int i = 0; i < threadNum; i++)
	{
		stringstream outputStr1;
		if (i <= 4)
		{
			outputStr1 << "Possibility of Spy : " << possibility[i % 5] << "%, Is Change Choise : " << "YES" <<", Average score : "<< (*averageScoreArray)[i]<<endl;
			cout << outputStr1.str();
			outputFile.WriteLine(outputStr1.str());
			for (int j = 0; j < (int)(*bestCombinationArray)[i].size(); j++)
			{
				stringstream outputStr2;
				outputStr2 << "winner strategy combination : " << (*bestCombinationArray)[i][j] << "  best scores : " << (*bestSocreArray)[i] << endl;
				cout << outputStr2.str();
				outputFile.WriteLine(outputStr2.str());
			}
			cout << endl;
			outputFile.WriteLine(" ");
		}
		else
		{
			outputStr1 << "Possibility of Spy : " << possibility[i % 5] << "%, Is Change Choise : " << "NO" << ", Average score : " << (*averageScoreArray)[i] << endl;
			cout << outputStr1.str();
			outputFile.WriteLine(outputStr1.str());
			for (int j = 0; j < (int)(*bestCombinationArray)[i].size(); j++)
			{
				stringstream outputStr2;
				outputStr2 << "winner strategy combination : " << (*bestCombinationArray)[i][j] << "  best scores : " << (*bestSocreArray)[i] << endl;
				cout << outputStr2.str();
				outputFile.WriteLine(outputStr2.str());
			}
			cout << endl;
			outputFile.WriteLine(" ");
		}
		
	}
	outputFile.CloseFile();
	cout << "time usage : " << (timeGetTime() - millisecond) / 1000.0f << " second"<<endl;
	SetConsoleTextAttribute(m_console, 240); 
	cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
	SetConsoleTextAttribute(m_console, 15);


	SAFE_DELETE(averageScoreArray);
	SAFE_DELETE(bestSocreArray);
	SAFE_DELETE(bestCombinationArray);
	SAFE_DELETE(returnVar);

	return true;
}

void Application::_CombatThread(int possibilityChoise, bool ischangechoise, vector<string>* bestCombination, float* bestSocre, float* averageScore, string* outputString, short* returnVar)
{
	GangGame::GangGamePunishmentRule rule;
	GangGame game;
	Gang gang1, gang2;
	vector<int> possibility = { 0,5,10,15,20 };
	*bestSocre = 5000;

	//statistic 
	float totalScore = 0;
	float totalGangs = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				for (int n = 0; n < 5; n++) {
					for (int m = 0; m < 5; m++)
					{
						vector<int> strategyname1 = { i, i, k, n, m };
						vector<int> strategyname2;
						for (int i = 0; i < 5; i++)
							strategyname2.push_back(strategyname1[i] + 5);
						int generateSpyPossible = possibility[possibilityChoise];
						bool isChangeChoise = ischangechoise ? true : false;
						if (!game.Init(&gang1, strategyname1, &gang2, strategyname2, generateSpyPossible, isChangeChoise, rule))
						{
							*returnVar = 1;
							return;
						}
						game.Run(200);
						finishedFile++;
						string combination1 = gang1.GetStrategyCombination();
						float score1 = gang1.GetTotalScore();
						string combination2 = gang2.GetStrategyCombination();
						float score2 = gang2.GetTotalScore();

						totalScore += score1;
						totalScore += score2;
						totalGangs += 2;

						stringstream output;
						output << "Possibility of Spy : " << std::left << std::setw(2) << generateSpyPossible << "%     Is Change Choise : " << std::left << std::setw(5) << (isChangeChoise ? "Yes" : "No") << endl
							<< "Combination of Strategies : " << std::right << std::setw(7) << combination1 << std::left << "vs" << std::setw(7) << combination2
							<< "  Result: Gang 1 Score: " << std::left << std::setw(6) << score1
							<< " ,Gang 2 Score: " << std::left << std::setw(6) << score2 << endl;
						(*outputString) += output.str();

						if (score1 < score2)
						{
							if (score1 < *bestSocre)
							{
								bestCombination->clear();
								bestCombination->push_back(combination1);
								*bestSocre = score1;
							}
							else if (score1 == *bestSocre)
								bestCombination->push_back(combination1);
							if (possibilityChoise == 0)
								m_bestStrategyCombination = gang1.GetStrategyName();
						}
						else if(score1 < score2)
						{
							if (score2 < *bestSocre)
							{
								bestCombination->clear();
								bestCombination->push_back(combination2);
								*bestSocre = score2;
							}
							else if (score2 == *bestSocre)
								bestCombination->push_back(combination2);
							if (possibilityChoise == 0)
								m_bestStrategyCombination = gang2.GetStrategyName();
						}
						else if (score1 == score2)
						{
							if (score2 < *bestSocre)
							{
								bestCombination->clear();
								bestCombination->push_back(combination2);
								bestCombination->push_back(combination1);
								*bestSocre = score2;
							}
							else if (score2 == *bestSocre)
							{
								bestCombination->push_back(combination2);
								bestCombination->push_back(combination1);
							}
							if (possibilityChoise == 0)
								m_bestStrategyCombination = gang2.GetStrategyName();
						}


					}
				}
			}
		}
	}
	*averageScore = totalScore / totalGangs;
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
	outputFile.Init("CourseWork 2 All strategies combination combat.txt");
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

void Application::_BeststrategyPresent()
{
	system("CLS");
	_ShadowWindowLine(TITLE, 0);
	COORD coord; coord.X = 0; coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);

	if (m_bestStrategyCombination.size() == 0)
	{
		cout << "you don't have best strategy combination" << endl;
		SetConsoleTextAttribute(m_console, 240);
		cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
		SetConsoleTextAttribute(m_console, 15);
		return;
	}
	finishedfile2 = 0;

	StrategyCreator* creator = GangStrategyCreator::GetInstance();
	const vector<int>& strategyName = creator->GetFileName();
	const vector<string>& strategyAddress = creator->GetFileAddress();
	//load all strategy file
	StrategyFileManager::GetInstance()->RemoteAll();
	for (int i = 0; i < (int)strategyAddress.size(); i++)
		StrategyFileManager::GetInstance()->CreateStrategyFile(strategyAddress[i]);

	vector<int> possibility = { 0,5,10,15,20 };

	//create thread
	int threadNum = 10;
	vector<short> *returnVar;
	vector<float>	   *averageScoreArray;

	returnVar = new vector<short>(threadNum, 0);
	averageScoreArray = new vector<float>(threadNum);

	//start to create thread
	vector<thread*> threads;
	for (int i = 0; i < threadNum; i++)
		threads.push_back(new thread(&Application::_PresentBestStrategyThread, this,
			i % 5, i <= 4 ? true : false, &((*averageScoreArray)[i]), &((*returnVar)[i])));

	while (true)
	{
		Sleep(100);
		cout << "progress : " << 5 * 5 * 5 * 5 * 5 * 10 << "/" << finishedfile2 << endl;
		bool isBreak = true;
		for (int i = 0; i < (int)(*returnVar).size(); i++)
		{
			if ((*returnVar)[i] == 1)
				return;
			else if ((*returnVar)[i] == 0)
				isBreak = false;
		}
		if (isBreak)
			break;
	}

	system("CLS");
	for (int i = 0; i < threadNum; i++)
	{

		if (i <= 4)
		{
			stringstream output;
			output << "Possibility of Spy : " << std::left << std::setw(2) << possibility[i % 5] << "%     Is Change Choise : " << std::left << "YES" << endl
				<< " Average score : " << (*averageScoreArray)[0] << endl << endl;
			cout << output.str();
		}
		else
		{
			stringstream output;
			output << "Possibility of Spy : " << std::left << std::setw(2) << possibility[i % 5] << "%     Is Change Choise : " << std::left << std::setw(5) << "NO" << endl
				<< " Average score : " << (*averageScoreArray)[0] << endl<<endl;
			cout << output.str();
		}
	}



	SetConsoleTextAttribute(m_console, 240);
	cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
	SetConsoleTextAttribute(m_console, 15);
}

void Application::_PresentBestStrategyThread(int possibilityChoise, bool ischangechoise, float* averageScore, short* returnVar)
{
	GangGame::GangGamePunishmentRule rule;
	GangGame game;
	Gang gang1, gang2;
	vector<int> possibility = { 0,5,10,15,20 };
	//statistic 
	float totalScore = 0;
	float totalGangs = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				for (int n = 0; n < 5; n++) {
					for (int m = 0; m < 5; m++)
					{
						vector<int> strategyname2 = { i, i, k, n, m };
						int generateSpyPossible = possibility[possibilityChoise];
						bool isChangeChoise = (ischangechoise == 0 ? true : false);
						if (!game.Init(&gang1, m_bestStrategyCombination, &gang2, strategyname2, generateSpyPossible, isChangeChoise, rule))
							return;
						game.Run(200);
						finishedfile2++;
						string combination1 = gang1.GetStrategyCombination();
						float score1 = gang1.GetTotalScore();

						totalScore += score1;
						totalGangs += 1;
					}
				}
			}
		}
	}
	*averageScore = totalScore / totalGangs;
	*returnVar = 2;
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

void Application::_ReadFilesAndCombat()
{
	system("CLS");
	_ShadowWindowLine(TITLE, 0);
	COORD coord; coord.X = 0; coord.Y = 6;
	SetConsoleCursorPosition(m_console, coord);

	StrategyFileManager::GetInstance()->RemoteAll();
	string address[10];
	for (int i = 0; i < 10; i++)
	{
		cout << "Please input "<< i << " file address : ";
		cin >> address[i];
		while (!StrategyFileManager::GetInstance()->CreateStrategyFile(address[i]))
		{
			cout << "input Error, please enter again" << endl;
			cout << "Please input " << i << " file address : ";
			cin >> address[i];
		}
	}

	vector<int> possibility = { 0,5,10,15,20 };
	vector<int> strategy1 = { 0,1,2,3,4 };
	vector<int> strategy2 = { 5,6,7,8,9 };
	Gang gang1, gang2;
	GangGame game;

	for (int i = 0; i < 10; i++)
	{
		if (!game.Init(&gang1, strategy1, &gang2, strategy2, possibility[i % 5], i <= 4 ? true : false))
			return;
		if (!game.Run(200))
			return;

		cout << "Possibility of Spy : " << std::left << std::setw(2) << possibility[i % 5] << "%     Is Change Choise : " << std::left << std::setw(5) << (i <= 4 ? "Yes" : "No") << endl
			<< "Combination of Strategies : " << std::right << std::setw(7) << gang1.GetStrategyCombination() << std::left << "vs" << std::setw(7) << gang2.GetStrategyCombination()
			<< "  Result: Gang 1 Score: " << std::left << std::setw(6) << gang1.GetTotalScore()
			<< " ,Gang 2 Score: " << std::left << std::setw(6) << gang2.GetTotalScore() << endl;

	}
	SetConsoleTextAttribute(m_console, 240);
	cout << ">>>>" << "Press Space Return" << "<<<<" << endl;
	SetConsoleTextAttribute(m_console, 15);

}
