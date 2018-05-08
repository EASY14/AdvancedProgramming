#pragma once

#include "..\Lib\GangStrategyCreator.h"
#include "..\Lib\GangGame.h"

#ifndef _APPLICATION_
#define _APPLICATION_


class Application
{
public :
	Application();
	~Application();

	int Run();

private :

	enum MODUAL
	{
		MENUSELECTION,
		STRATEGYFILECREATION,
		ALLSTRATEGYCOMBAT,
		OUTPUTCREATEFILESLOG,
		OUTPUTSTRATEGYFILECOMBATLOG,
		READFILESANDCOMBAT,
		BESTSTRATEGYPRESENT
	};

	enum INPUT
	{
		SPACE,
		ESC,
		ARROWLEFT,
		ARROWRIGHT,
		ARROWUP,
		ARROWDOWN,
	};

	HANDLE m_console;
	DWORD m_written;
	vector<string> m_mainMenu;
	int m_mainMenuSelection;

	MODUAL m_currentModual;

	bool m_isEsc;

	int m_coreNumber;

	short m_logReturnVar;

	string m_fileCreateLog;

	vector<string>* m_strategyCombatLog;

	vector<int> m_bestStrategyCombination;

	bool _Init();

	//handle all input value
	void _InputHandle(INPUT input);

	//handle creation of file
	bool _CreateStategyFile();

	//handle combat of strategy
	bool _AllStrategyFileCombat();

	bool _ShowMenu();

	void _ShadowWindowLine(char *str, int yOffset = 0);

	void _DrawBox(SMALL_RECT rc);

	void _CombatThread(int possibilityChoise, bool ischangechoise, vector<string>* bestCombination, float* bestSocre, float* averageScore,string* outputString, short* returnVar);

	void _OutputCreateFileLog();

	void _OutputStrategyFileLog();

	void _CombatOutlogThread(short* returnVar);

	void _BeststrategyPresent();

	void _PresentBestStrategyThread(int possibilityChoise, bool ischangechoise, float* averageScore, short* returnVar);

	void _ReadFilesAndCombat();
};


#endif // !_APPLICATION_

//1.interpreter ok
//2.creator ok
//3.player
//4.game
//5.application


//01234  56789
//
//Team A : 01234 (Leader 0, spy e.g. 4)
//0 picks other member randomly in team(e.g 2)
//Then another member not leader(0) or chosen member(2) is then revealed as not the spy(1)
//
//now the leader(0) who chose(2) as potential spy and knows that(1) is / not/ a spy has
//a choice, change choice to last other member of team(3 or 4) or stick with original choice(2)
