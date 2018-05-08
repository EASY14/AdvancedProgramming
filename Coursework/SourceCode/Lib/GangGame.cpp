#include "GangGame.h"



GangGame::GangGame()
{
	m_iterations = 0;
	m_generateSpyPossible = 0;
}


GangGame::~GangGame()
{

}

bool GangGame::Init(Gang* gang1, const vector<int>& strategyName1, Gang* gang2, const vector<int>& strategyName2, int generateSpyPossible, bool isChangeChoise, GangGamePunishmentRule& rule)
{
	//initise all gang
	if (!gang1->Init(this, strategyName1))
		return false;
	if (!gang2->Init(this, strategyName2))
		return false;

	//push into container
	m_gangs.clear();
	m_gangs.push_back(gang1);
	m_gangs.push_back(gang2);

	//apply punishment rule
	m_punishmentRule = rule;

	m_generateSpyPossible = generateSpyPossible;

	m_isChangeChoise = isChangeChoise;

	m_iterations = 0;

	return true;
}

bool GangGame::Run(int times)
{	

	//example £º input 75% than it has 75% true.
	function<int(int)> IsInPossibility = [](int possibility)
	{
		return possibility == 0 ? false : (rand() % 100) + 1 <= possibility ? true : false;
	};

	for (int i = 0; i < times; i++)
	{
		m_iterations++;

		//initilise
		for (int j = 0; j < (int)m_gangs.size(); j++)
			m_gangs[j]->RemoteSpy();

		// does it exist a spy
		bool isExistSpy = processEvent(IsInPossibility,m_generateSpyPossible);
		if (isExistSpy)
		{
			//create spy
			m_gangs[rand() % m_gangs.size()]->GenerateSpy();

			//finding spy
			if (_SpyFinding())
				continue; // when it finds a spy, it doesn't have to generate selection 
		}


		//get selection
		for (int j = 0; j < (int)m_gangs.size(); j++)
			if (!m_gangs[j]->GenerateSelection())
				return false;

		//get total agreement
		//any gang which is not totally agreement will turn it into false
		bool isTotalAgreement = true;
		for (int j = 0; j < (int)m_gangs.size(); j++)
			isTotalAgreement = isTotalAgreement && m_gangs[j]->IsTotalAgreement();

		if (isTotalAgreement)
		{
			//total agreement
			_AgreementResult();
		}
		else
		{
			//not total agreement
			_NotAgreementResult();
		}

	}
	return true;
}

int GangGame::GetIterations()
{
	return m_iterations;
}

void GangGame::_AgreementResult()
{
	int silence = 0, betrary = 0;
	for (int j = 0; j < (int)m_gangs.size(); j++)
	{
		if (m_gangs[j]->GetAllSelection()[0] == SELECTION::BETRAY)
			betrary++;
		else if (m_gangs[j]->GetAllSelection()[0] == SELECTION::SILENCE)
			silence++;
	}

	int compare = betrary - silence;

	if (betrary == 0)
	{
		for (int j = 0; j < (int)m_gangs.size(); j++)
		{
			const vector<Player*>& players = m_gangs[j]->GetAllMenbers();
			for (int k = 0; k < (int)players.size(); k++)
			{
				players[k]->SetScore(players[k]->GetScore() + m_punishmentRule.AllSliencePunish);
				players[k]->SetAllOutcomeW(players[k]->GetAllOutcomeW() + 1);
			}
			
		}
	}
	else if (silence == 0)
	{
		for (int j = 0; j < (int)m_gangs.size(); j++)
		{
			const vector<Player*>& players = m_gangs[j]->GetAllMenbers();
			for (int k = 0; k < (int)players.size(); k++)
			{
				players[k]->SetScore(players[k]->GetScore() + m_punishmentRule.AllBetraryPunish);
				players[k]->SetAllOutcomeZ(players[k]->GetAllOutcomeZ() + 1);
			}

		}
	}
	else if (compare == 0)
	{
		for (int j = 0; j < (int)m_gangs.size(); j++)
		{
			const vector<Player*>& players = m_gangs[j]->GetAllMenbers();
			const vector<SELECTION>& selections = m_gangs[j]->GetAllSelection();

			if (selections[0] == SELECTION::BETRAY)
			{
				for (int k = 0; k < (int)players.size(); k++)
				{
					players[k]->SetScore(players[k]->GetScore() + m_punishmentRule.BetraryPubnish);
					players[k]->SetAllOutcomeY(players[k]->GetAllOutcomeY() + 1);
				}
			}
			else if (selections[0] == SELECTION::SILENCE)
			{
				for (int k = 0; k < (int)players.size(); k++)
				{
					players[k]->SetScore(players[k]->GetScore() + m_punishmentRule.BeBetraryedPunish);
					players[k]->SetAllOutcomeX(players[k]->GetAllOutcomeX() + 1);
				}
			}
		}
	}

}

void GangGame::_NotAgreementResult()
{
	if (m_gangs[0]->GetBetrayNum() == m_gangs[1]->GetBetrayNum() 
		&& m_gangs[0]->GetSilenceNum() == m_gangs[1]->GetSilenceNum())
	{
		for (int j = 0; j < (int)m_gangs.size(); j++)
		{
			const vector<Player*>& players = m_gangs[j]->GetAllMenbers();
			for (int k = 0; k < (int)players.size(); k++)
			{
				players[k]->SetScore(players[k]->GetScore() + m_punishmentRule.EquivalentDisagreePunish);
				players[k]->SetAllOutcomeC(players[k]->GetAllOutcomeC() + 1);
			}
		}
	}
	else
	{
		int mostBetrayOne = m_gangs[0]->GetBetrayNum() > m_gangs[1]->GetBetrayNum() ? 0 : 1;
		int mostSilenceOne = m_gangs[0]->GetSilenceNum() > m_gangs[1]->GetSilenceNum() ? 0 : 1;

		//handle situation of A
		const vector<Player*>& mostBetrayplayers = m_gangs[mostBetrayOne]->GetAllMenbers();
		for (int k = 0; k < (int)mostBetrayplayers.size(); k++)
		{
			mostBetrayplayers[k]->SetScore(mostBetrayplayers[k]->GetScore() + m_punishmentRule.MoreBetrayDisagreePunish);
			mostBetrayplayers[k]->SetAllOutcomeA(mostBetrayplayers[k]->GetAllOutcomeA() + 1);
		}

		//handle situation of B
		const vector<Player*>& mostSilenceplayers = m_gangs[mostSilenceOne]->GetAllMenbers();
		for (int k = 0; k < (int)mostSilenceplayers.size(); k++)
		{
			mostSilenceplayers[k]->SetScore(mostSilenceplayers[k]->GetScore() + m_punishmentRule.LessBetrayDisagreePunish);
			mostSilenceplayers[k]->SetAllOutcomeB(mostSilenceplayers[k]->GetAllOutcomeB() + 1);
		}
	}
}

bool GangGame::_SpyFinding()
{
	//find spy
	bool isCorrect = false;
	int choise = 1; //0 is leader who is impossible to become a spy;
	int findingSpyGangNum = -1;
	for (int j = 0; j < (int)m_gangs.size(); j++)
	{
		choise = 1;
		if (m_isChangeChoise)
		{
			int reveal = m_gangs[j]->RevealNotSpy(choise);
			//change choise
			for (int k = 1; k < m_gangs[j]->GetMenbersNum(); k++)
			{
				//get one choise except pervious choise and reveal menber
				if (k != choise && k != reveal)
				{
					isCorrect = m_gangs[j]->IsSpy(k);
					choise = k;
					break;
				}
			}
		}
		else
		{
			//insist on original choise
			isCorrect = m_gangs[j]->IsSpy(choise);
		}

		//if find a spy
		if (isCorrect)
		{
			//record  gang num
			findingSpyGangNum = j;
			break;
		}
	}

	if (!isCorrect) // is not correct then return false and generate selection
		return false;
	else
	{
		// punishment
		float changePunishment = m_isChangeChoise ? m_punishmentRule.ChangeChoisePunish : m_punishmentRule.InsistChoisePunish;
		for (int j = 0; j < (int)m_gangs.size(); j++)
		{
			const vector<Player*>& players = m_gangs[j]->GetAllMenbers();
			if (findingSpyGangNum == j) // the gang which find a spy
			{
				for (int k = 0; k < (int)players.size(); k++)
				{
					if (k != choise)
					{
						//is not spy
						players[k]->SetScore(players[k]->GetScore() + m_punishmentRule.FindSpyGangPunish + changePunishment);
					}
					else
					{
						//is spy
						players[k]->SetScore(players[k]->GetScore() + m_punishmentRule.SpyBeFoundPunish + changePunishment);
					}
					players[k]->SetAllOutcomeW(players[k]->GetAllOutcomeW() + 1);
				}
			}
			else // the opposing gang 
			{
				for (int k = 0; k < (int)players.size(); k++)
				{
					//is not spy
					players[k]->SetScore(players[k]->GetScore() + m_punishmentRule.FindSpyOpposingGangPunish);
					players[k]->SetAllOutcomeW(players[k]->GetAllOutcomeW() + 1);
				}
			}
		}

		return true;
	}
	return false;
}

bool GangGame::processEvent(function<int(int)> fun, int possibility)
{
	return fun(possibility);
}


