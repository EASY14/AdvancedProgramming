#include "GangGame.h"


Gang::Gang()
{
	m_spy = -1;
	m_silence = 0;
	m_betray = 0;
}


Gang::~Gang()
{
	DeleteAllMenber();
}

bool Gang::Init(GangGame *game, const vector<int>& strategyNames)
{
	DeleteAllMenber();

	m_menbersNum = strategyNames.size();

	Player* player = nullptr;
	for (int i = 0; i < m_menbersNum; i++)
	{
		// initilise all menbers and push into container
		player = new Player();
		if (!player->Init(strategyNames[i], game))
			return false;

		m_menbers.push_back(player);
		m_menbersSelection.push_back(SELECTION::NOCHOISE);
	}


	//store strategy combination
	stringstream combination;
	for (int i = 0; i < m_menbersNum; i++)
		combination << strategyNames[i] << " ";
	m_strategyCombination = combination.str();

	m_combination = strategyNames;

	m_spy = -1;
	m_silence = 0;
	m_betray = 0;

	return true;
}

bool Gang::GenerateSelection()
{
	m_silence = 0;
	m_betray = 0;
	SELECTION selection = SELECTION::NOCHOISE;
	for (int i = 0; i < m_menbersNum; i++)
	{
		if (i != m_spy)
		{
			selection = m_menbers[i]->GetSelection();
			if (selection == SELECTION::NOCHOISE)
				return false;
			else
				m_menbersSelection[i] = selection;

			//record
			if (selection == SELECTION::BETRAY)
				m_betray++;
			else if(selection == SELECTION::SILENCE)
				m_silence++;
		}
	}

	if (m_spy != -1) 
	{
		//it does have a spy
		// get the minority selection for spy
		if (m_betray > m_silence)
			m_menbersSelection[m_spy] = SELECTION::SILENCE;
		else if (m_betray < m_silence)
			m_menbersSelection[m_spy] = SELECTION::BETRAY;
		else if (m_betray == m_silence)
			m_menbersSelection[m_spy] = rand() % 2 == 0 ? SELECTION::SILENCE : SELECTION::BETRAY;

		//record
		if (m_menbersSelection[m_spy] == SELECTION::BETRAY)
			m_betray++;
		else if (m_menbersSelection[m_spy] == SELECTION::SILENCE)
			m_silence++;
	}

	return true;
}

bool Gang::IsTotalAgreement()
{
	if (m_betray == 0 || m_silence == 0)
		return true;
	else
		return false;
}

int Gang::GetBetrayNum() const
{
	return m_betray;
}

int Gang::GetSilenceNum() const
{
	return m_silence;
}

const vector<Player*>& Gang::GetAllMenbers() const
{
	return m_menbers;
}

const vector<SELECTION>& Gang::GetAllSelection() const
{
	return m_menbersSelection;
}

void Gang::RemoteSpy()
{
	m_spy = -1;
}

void Gang::GenerateSpy()
{
	m_spy = (rand() % (m_menbersNum-1)) + 1;
	//0 is not spy so randomly get one in [1,(m_menbersNum-1)]
}

bool Gang::IsSpy(int num) const
{
	if (m_spy == num)
		return true;
	else
		return false;
}

int Gang::RevealNotSpy(int choise)
{
	for (int i = 1; i < m_menbersNum; i++)
	{
		if (i != m_spy && i != choise)
		{
			return i;
		}
	}
	return 0;
}

float Gang::GetTotalScore() const
{
	float totalScore = 0;
	for (int i = 0; i < m_menbersNum; i++)
		totalScore += m_menbers[i]->GetScore();

	return totalScore;
}

string Gang::GetStrategyCombination() const
{
	return m_strategyCombination;
}

void Gang::DeleteAllMenber()
{
	if (m_menbers.size() != 0)
	{
		for (int i = 0; i < m_menbersNum; i++)
		{
			SAFE_DELETE(m_menbers[i]);
		}
		m_menbers.clear();
	}
}

int Gang::GetMenbersNum()
{
	return m_menbersNum;
}

const vector<int> Gang::GetStrategyName() const
{
	return m_combination;
}
