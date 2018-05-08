#include "GangStrategyCreator.h"

GangStrategyCreator GangStrategyCreator::m_instance;

GangStrategyCreator::GangStrategyCreator()
{
	m_outcomeKeyword.push_back("A ");
	m_outcomeKeyword.push_back("B ");
	m_outcomeKeyword.push_back("C ");
}
