#include "stdafx.h"
#include "LEnemy.h"
#include "shooter/LShooters.h"
#include "shooter/LShooters.h"
#include "move/LPathWalker.h"
#include "LAssets.h"

LEnemy::LEnemy(IGameObject* pParent, int _enemyStyle)
	: LCollideObject(pParent)
	, m_pGraphGroup(nullptr)
{
	m_spShooters = std::make_unique<LShooters>();
	m_phyData.position.reset(256, 256);
	m_enemyStyle = _enemyStyle;
	m_counter = 0;
	m_imgCount = 0;
	m_bFace = true;

	m_pGraphGroup = &LEngine::assets()->GetSubGraphGroup(_T("������"));
	m_spWalker = LWalker::CreatePathWalker(1);
}

LEnemy::~LEnemy(void)
{
}

void LEnemy::Update()
{
	m_spWalker->nextStep(m_phyData);

	m_counter++;
	m_imgCount = (m_counter >> 3) & 0x3;	// 8f/pic && 4pic
	if (m_phyData.speed.y() > 0)
		m_imgCount += 8;

	m_spShooters->update();
}

void LEnemy::draw( LPainter& painter )
{
	painter.drawRotaGraphF(m_phyData.position, 1, Radian0, m_pGraphGroup->at(m_imgCount), true, m_bFace);
#ifdef _DEBUG
	LString sPos = LStrBuilder(L"%1, %2").arg(m_phyData.position.x()).arg(m_phyData.position.y()).apply();
	painter.drawString(m_phyData.position, sPos.c_str(), LRgb::White);
#endif
}
