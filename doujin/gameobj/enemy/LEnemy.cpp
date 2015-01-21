#include "stdafx.h"
#include "LEnemy.h"
#include "Globle.h"
#include "shooter/LShooters.h"
#include "resource.h"
#include "Engine.h"
#include <cmath>
#include "LPainter.h"
#include "LImage.h"
#include <QString>
#include "shooter/LShooters.h"

LEnemy::LEnemy(IGameObject* pParent, int _enemyStyle)
	: LGameObject(pParent)
{
	m_spShooters.reset(new LShooters);
	m_phyData.position.Init(256, 256);
	m_enemyStyle = _enemyStyle;
	m_counter = 0;
	m_imgCount = 0;
	m_bFace = true;
}

LEnemy::~LEnemy(void)
{
}

void LEnemy::Update()
{
	m_counter++;
	m_imgCount = (m_counter >> 3) & 0x3;	// 8f/pic && 4pic
	if (m_phyData.speed.y() > 0)
		m_imgCount += 8;

	m_spShooters->Update();
}

void LEnemy::Draw()
{
	Painter.drawRotaGraphF(m_phyData.position, 1, Radian0, Resource::enemy(m_enemyStyle, m_imgCount), true, m_bFace);
	Painter.drawString(m_phyData.position, QString("%1, %2").arg(m_phyData.position.x()).arg(m_phyData.position.y()).utf16w(), LRgb::White);
}

const LGraphHandle LEnemy::GetGraphHandle() const
{
	return Resource::enemy(m_enemyStyle, m_imgCount);
}
