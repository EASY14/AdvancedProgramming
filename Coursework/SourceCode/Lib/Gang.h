#pragma once

#include "Player.h"

#ifndef _GANG_
#define _GANG_

class GangGame;

class Gang
{
public:
	Gang();
	~Gang();

	//input five strategy name for five menbers
	bool Init(GangGame *game, const vector<int>& strategyNames);
	
	//get all selection of all menbers
	bool GenerateSelection();

	//is every one make a same decision
	bool IsTotalAgreement();

	//how many people betray
	int GetBetrayNum()const;

	//how many people silence
	int GetSilenceNum()const;

	//Get all menbers 
	const vector<Player*>& GetAllMenbers()const;

	//Get every one selection
	const vector<SELECTION>& GetAllSelection()const;

	//remote spy because a spy will be distributed in any gand randomly
	void RemoteSpy();

	//create a spy randomly in 1 to 4
	void GenerateSpy();

	//is this number a spy
	bool IsSpy(int num)const;

	//reveal one not spy
	int RevealNotSpy(int choise);

	//get total score of menbers
	float GetTotalScore()const;

	//get the combination of strategy applied in menbers
	string GetStrategyCombination()const;

	//release menory
	void DeleteAllMenber();

	//how many menbers
	int GetMenbersNum();

	//get strategy name
	const vector<int> GetStrategyName()const;

protected :

	int m_menbersNum;

	int m_spy;

	int m_silence; 
	
	int m_betray;

	vector<int> m_combination;

	vector<Player*> m_menbers;

	vector<SELECTION> m_menbersSelection;

	string m_strategyCombination;
};

#endif // !_GANG_

