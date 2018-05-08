#pragma once

//std
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <thread>
#include <mutex>
#include <functional>

#include <math.h>
#include <conio.h>

//window
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <Shlwapi.h>

using namespace std;


#define SAFE_DELETE(x)       if(x){delete x;x = nullptr;}


inline void ErrorOutput(wchar_t* file, int line, wchar_t* error)
{
	_Debug_message(error, file, line);
}

inline void ErrorOutput(wchar_t* error)
{
	_Debug_message(error, __FILEW__, __LINE__);
}

namespace GameEnum
{
	enum SELECTION
	{
		SILENCE,   // choose slience
		BETRAY,    // choose betrary
		NOCHOISE,  // no choose 
	};

	enum GAMEOUTCOME
	{
		// do total agreement
		NONE = 'N', // the game just begin , no result
		W = 'W',	// I stayed slient and the other prisoner stayed slient OR finding a spy
		X = 'X',    // I stayed slient and the other prisoner betrayed me
		Y = 'Y',    // I betrayed the other prisoner and the other prisoner stayed slient
		Z = 'Z',    // I betrayed the other prisoner and the other prisoner betrayed me

		// not total agreement
		A = 'A',    // I was in a gang with a mixed response where we had most betrays
		B = 'B',    // I was in a gang with a mixed response where we had the least betrays
		C = 'C',    // I was in a gang with a mixed response where both gangs made cumulative equivalent decision
	};
}