#pragma once

#include "StrategyCreator.h"

#ifndef _GANGSTRATEGYCREATOR_
#define _GANGSTRATEGYCREATOR_

class GangStrategyCreator : public StrategyCreator
{
public :
	//singleton pattern
	static GangStrategyCreator* GetInstance()
	{
		return &m_instance;
	}

protected :

	//guarantee user only use GetInstance to get object
	GangStrategyCreator();
	virtual ~GangStrategyCreator(){}

	//prevent duplication
	GangStrategyCreator& operator=(const GangStrategyCreator& rhs) {}

	//instance
	static GangStrategyCreator m_instance;
};

#endif // !_GANGSTRATEGYCREATOR_