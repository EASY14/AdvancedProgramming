#pragma once

#include "StrategyFileManager.h"
#include "StrategyInterpreter.h"

#ifndef _PLAYER_
#define _PLAYER_

class Player
{
public :
	Player();

	bool Init(int strategyFileName, BaseGame* game);

	//run interpreter
	virtual SELECTION GetSelection();

	//get player score
	float GetScore()const;

	//set player score
	void SetScore(float score);

	//get total times of W situation
	int GetAllOutcomeW()const;

	//get total times of X situation
	int GetAllOutcomeX()const;

	//get total times of Y situation
	int GetAllOutcomeY()const;

	//get total times of Z situation
	int GetAllOutcomeZ()const;

	//get total times of X situation
	int GetAllOutcomeA()const;

	//get total times of Y situation
	int GetAllOutcomeB()const;

	//get total times of Z situation
	int GetAllOutcomeC()const;

	//set total times of W situation
	void SetAllOutcomeW(int w);

	//set total times of X situation
	void SetAllOutcomeX(int x);

	//set total times of Y situation
	void SetAllOutcomeY(int y);

	//set total times of Z situation
	void SetAllOutcomeZ(int z);

	//set total times of X situation
	void SetAllOutcomeA(int A);

	//set total times of Y situation
	void SetAllOutcomeB(int B);

	//set total times of Z situation
	void SetAllOutcomeC(int C);

	//get the outcome of the last game
	GAMEOUTCOME GetLastOutcome();

protected :
	//how many years build up in prison
	float m_score;

	//used to generate player selection
	StrategyInterpreter m_interpreter;

	//how many times has W been outcome in privious game
	int m_allOutcomeW;

	//how many times has X been outcome in privious game
	int m_allOutcomeX;

	//how many times has Y been outcome in privious game
	int m_allOutcomeY;

	//how many times has Z been outcome in privious game
	int m_allOutcomeZ;

	//how many times has Z been outcome in privious game
	int m_allOutcomeA;

	//how many times has Z been outcome in privious game
	int m_allOutcomeB;

	//how many times has Z been outcome in privious game
	int m_allOutcomeC;

	//give the outcome of the last game
	GAMEOUTCOME m_lastOutcome;
};

#endif // !_PLAYER_
