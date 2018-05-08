#pragma once

#include "Game.h"
#include "Gang.h"

#ifndef _GANGGAME_
#define _GANGGAME_

class GangGame : public BaseGame
{
public:
	GangGame();
	~GangGame();

	struct GangGamePunishmentRule
	{
		//total agreement
		float AllSliencePunish;
		float AllBetraryPunish;
		float BeBetraryedPunish;
		float BetraryPubnish;

		//not total agreement
		float MoreBetrayDisagreePunish;
		float EquivalentDisagreePunish;
		float LessBetrayDisagreePunish;

		//spy finding 
		float FindSpyGangPunish;
		float FindSpyOpposingGangPunish;
		float SpyBeFoundPunish;
		float ChangeChoisePunish;
		float InsistChoisePunish;
		GangGamePunishmentRule()
		{
			AllSliencePunish = 2.0f; //W
			AllBetraryPunish = 4.0f; //X
			BeBetraryedPunish = 5.0f;//Y
			BetraryPubnish = 0.0f;   //Z

			MoreBetrayDisagreePunish = 2.5f;//A
			EquivalentDisagreePunish = 2.0f;//B
			LessBetrayDisagreePunish = 3.0f;//C

			FindSpyGangPunish = 0.0f;;
			FindSpyOpposingGangPunish = 5.0f;
			SpyBeFoundPunish = 2.0f;
			ChangeChoisePunish = 2.0f;
			InsistChoisePunish = 0.0f;
		}
	};

	//initialise game and players
	bool Init(Gang* gang1, const vector<int>& strategyName1, Gang* gang2, const vector<int>& strategyName2, int generateSpyPossible, bool isChangeChoise, GangGamePunishmentRule& rule = GangGamePunishmentRule());

	//run the game procedure for times
	bool Run(int times);

	//get total iterations
	virtual int GetIterations() override;

protected:

	//prevent duplication
	Game& operator=(const Game& rhs) {}

	//culculate result insituation of total agreement in gang
	void _AgreementResult();

	//culculate result in situation of not total agreement in gang
	void _NotAgreementResult();

	bool _SpyFinding();

	//ture means in that possibility otherwise false means out of possibility
	bool processEvent(function<int(int)> fun, int possibility);

	//how possible generate a spy
	int m_generateSpyPossible;

	//is change choise
	int m_isChangeChoise;

	//the rule for how many years for punishment
	GangGamePunishmentRule m_punishmentRule;

	//all players
	vector<Gang*> m_gangs;

	//how many iterations
	int m_iterations;
};


#endif // !_GANGGAME_