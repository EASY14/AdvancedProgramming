#pragma once

#include "Player.h"

using namespace GameEnum;

#ifndef _GAME_
#define _GAME_

class Player;

class BaseGame 
{
public :

	//get total iterations
	virtual int GetIterations() = 0;
};

class Game : public BaseGame
{
public:
	Game();
	~Game();

	struct GamePunishmentRule
	{
		float AllSliencePunish;
		float AllBetraryPunish;
		float BeBetraryedPunish;
		float BetraryPubnish;

		GamePunishmentRule()
		{
			AllSliencePunish = 2.0f; //W
			AllBetraryPunish = 4.0f; //X
			BeBetraryedPunish = 5.0f;//Y
			BetraryPubnish = 0.0f;   //Z
		}
	};

	//initialise game and players
	bool Init(Player *player1, int strategyName1, Player * player2, int strategyName2, const GamePunishmentRule & rule = GamePunishmentRule());

	//run the game procedure for times
	bool Run(int times);

	//get total iterations
	virtual int GetIterations() override;

protected:

	//prevent duplication
	Game& operator=(const Game& rhs) {}

	//culculate result
	void _GetResult(vector<Player*>& players, vector<SELECTION>& playersSelection);

	//the rule for how many years for punishment
	GamePunishmentRule m_punishmentRule;

	//all players
	vector<Player*> m_players;

	//how many iterations
	int m_iterations;
};


#endif // !_GAME_
