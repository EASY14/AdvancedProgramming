#pragma once

#include "..\Lib\StrategyCreator.h"
#include "..\Lib\Game.h"

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
		READFILESANDCOMBAT

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

	void _CombatThread(int beginFile, int EndFile, const vector<int>& strategyName, map<int, int>* bestOneNameWin, string* outputString, short* returnVar);

	void _OutputCreateFileLog();

	void _OutputStrategyFileLog();

	void _CombatOutlogThread(short* returnVar);

	void _ReadFilesAndCombat();
};


#endif // !_APPLICATION_
