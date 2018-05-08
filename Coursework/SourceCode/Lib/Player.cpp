#include "Player.h"

Player::Player()
{
	m_score = 0;
	m_allOutcomeW = 0;
	m_allOutcomeX = 0;
	m_allOutcomeY = 0;
	m_allOutcomeZ = 0;

	m_allOutcomeA = 0;
	m_allOutcomeB = 0;
	m_allOutcomeC = 0;

	m_lastOutcome = GAMEOUTCOME::NONE;
}

bool Player::Init(int strategyFileName, BaseGame* game)
{
	StrategyFileManager *manager = StrategyFileManager::GetInstance();

	//initialise interpreter
	if (!m_interpreter.Init(manager->GetCode(strategyFileName), game, this))
		return false;

	m_score = 0;

	m_allOutcomeW = 0;
	m_allOutcomeX = 0;
	m_allOutcomeY = 0;
	m_allOutcomeZ = 0;

	m_allOutcomeA = 0;
	m_allOutcomeB = 0;
	m_allOutcomeC = 0;

	m_lastOutcome = GAMEOUTCOME::NONE;

	return true;
}

SELECTION Player::GetSelection()
{
	return m_interpreter.GetSelection();
}

void Player::SetScore(float score)
{
	m_score = score;
}

float Player::GetScore()const
{
	return m_score;
}

int Player::GetAllOutcomeW()const
{
	return m_allOutcomeW;
}

int Player::GetAllOutcomeX()const
{
	return m_allOutcomeX;
}

int Player::GetAllOutcomeY()const
{
	return m_allOutcomeY;
}

int Player::GetAllOutcomeZ()const
{
	return m_allOutcomeZ;
}

int Player::GetAllOutcomeA() const
{
	return m_allOutcomeA;
}

int Player::GetAllOutcomeB() const
{
	return m_allOutcomeB;
}

int Player::GetAllOutcomeC() const
{
	return m_allOutcomeC;
}

void Player::SetAllOutcomeW(int w)
{
	m_lastOutcome = GAMEOUTCOME::W;
	m_allOutcomeW = w;
}

void Player::SetAllOutcomeX(int x)
{
	m_lastOutcome = GAMEOUTCOME::X;
	m_allOutcomeX = x;
}

void Player::SetAllOutcomeY(int y)
{
	m_lastOutcome = GAMEOUTCOME::Y;
	m_allOutcomeY = y;
}

void Player::SetAllOutcomeZ(int z)
{
	m_lastOutcome = GAMEOUTCOME::Z;
	m_allOutcomeZ = z;
}

void Player::SetAllOutcomeA(int A)
{
	m_lastOutcome = GAMEOUTCOME::A;
	m_allOutcomeA = A;
}

void Player::SetAllOutcomeB(int B)
{
	m_lastOutcome = GAMEOUTCOME::B;
	m_allOutcomeB = B;
}

void Player::SetAllOutcomeC(int C)
{
	m_lastOutcome = GAMEOUTCOME::C;
	m_allOutcomeC = C;
}

GAMEOUTCOME Player::GetLastOutcome()
{
	return m_lastOutcome;
}
