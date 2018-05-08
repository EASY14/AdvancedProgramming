#include "Game.h"



Game::Game()
{
	m_iterations = 0;
}


Game::~Game()
{
}

bool Game::Init(Player *player1, int strategyName1, Player * player2, int strategyName2, const GamePunishmentRule & rule)
{
	//initise all player
	if (!player1->Init(strategyName1, this))
		return false;
	if (!player2->Init(strategyName2, this))
		return false;

	//push into container
	m_players.clear();
	m_players.push_back(player1);
	m_players.push_back(player2);

	//apply punishment rull
	m_punishmentRule = rule;

	m_iterations = 0;

	return true;
}

bool Game::Run(int times)
{
	SELECTION selection = SELECTION::NOCHOISE;
	//map<Player*, SELECTION> playerSelection;
	vector<Player*> players; 
	vector<SELECTION> playersSelection;
	//Result result[2];
	for (int i = 0; i < times; i++)
	{
		m_iterations++;
		for (int j = 0; j < (int)m_players.size(); j++)
		{
			//get every player choose and culculate score for every player
			selection = m_players[j]->GetSelection();
			if (selection == SELECTION::NOCHOISE)
				return false;
			else
			{
				players.push_back(m_players[j]);
				playersSelection.push_back(selection);
			}
				
		}
		_GetResult(players, playersSelection);
		players.clear();
		playersSelection.clear();
	}

	return true;
}

void Game::_GetResult(vector<Player*>& players, vector<SELECTION>& playersSelection)
{
	int silence = 0, betrary = 0;
	for (int i = 0; i < (int)playersSelection.size(); i++)
	{
		if (playersSelection[i] == SELECTION::BETRAY)
			betrary++;
		else if (playersSelection[i] == SELECTION::SILENCE)
			silence++;
	}


	int compare = betrary - silence;

	if (betrary == 0)
	{
		for (int i = 0; i < (int)players.size(); i++)
		{
			players[i]->SetScore(players[i]->GetScore() + m_punishmentRule.AllSliencePunish);
			players[i]->SetAllOutcomeW(players[i]->GetAllOutcomeW() + 1);
		}
	}
	else if (silence == 0)
	{
		for (int i = 0; i < (int)players.size(); i++)
		{
			players[i]->SetScore(players[i]->GetScore() + m_punishmentRule.AllBetraryPunish);
			players[i]->SetAllOutcomeZ(players[i]->GetAllOutcomeZ() + 1);
		}
	}
	else if (compare == 0)
	{
		for (int i = 0; i < (int)players.size(); i++)
		{
			if (playersSelection[i] == SELECTION::BETRAY)
			{
				players[i]->SetScore(players[i]->GetScore() + m_punishmentRule.BetraryPubnish);
				players[i]->SetAllOutcomeY(players[i]->GetAllOutcomeY() + 1);
			}
			else if (playersSelection[i] == SELECTION::SILENCE)
			{
				players[i]->SetScore(players[i]->GetScore() + m_punishmentRule.BeBetraryedPunish);
				players[i]->SetAllOutcomeX(players[i]->GetAllOutcomeX() + 1);
			}
		}
	}
}

int Game::GetIterations()
{
	return m_iterations;
}

