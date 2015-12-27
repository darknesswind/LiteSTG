#include "stdafx.h"
#include "LStage.h"
#include "Engine.h"
#include "enemy/LEnemys.h"

LStage::LStage(IGameObject* pParent)
	: LGameObject(pParent)
	, m_timeCount(0)
{
	m_spEnemys.reset(new LEnemys);
}

LStage::~LStage(void)
{
}

void LStage::loadStage()
{

}

void LStage::Update()
{
	while (m_timeLine.front().startTime == m_timeCount)
	{
		m_spEnemys->Add();
		m_timeLine.pop_front();
	}
	++m_timeCount;
}
