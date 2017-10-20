#include "stdafx.h"
#include "LStage.h"
#include "enemy/LEnemys.h"
#include "bullet/LBullets.h"
#include "player/LPlayers.h"

LStage::LStage()
	: m_timeCount(0)
{
	m_spBullets = std::make_unique<LBullets>();
	m_spEnemys = std::make_unique<LEnemys>();
	m_spPlayers = std::make_unique<LPlayers>();
}

LStage::~LStage(void)
{
}

void LStage::loadStage()
{

}

void LStage::Update()
{
	if (!m_bRunning)
		return;

	m_spEnemys->update();
	m_spBullets->update();
	m_spPlayers->update();

	while (!m_timeLine.empty() && m_timeLine.front().startTime == m_timeCount)
	{
		m_spEnemys->Add();
		m_timeLine.pop_front();
	}
	++m_timeCount;
}
