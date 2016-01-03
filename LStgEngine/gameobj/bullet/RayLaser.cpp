#include "stdafx.h"
#include "RayLaser.h"
#include "Graph.h"
#include "LPainter.h"
#include "LHandle.h"

RayLaser::RayLaser(IGameObject* pParent)
	: Bullet(pParent)
{
	m_width = 1;
	m_length = 70;
	m_state = RayExpand;
	m_nExpandCount = m_nCollapseCount = g_nPlayTime;
	m_renderArg.paintArg.blendMode = DxBlendMode::Add;
	m_renderArg.paintArg.blendParam = 250;
}

RayLaser::~RayLaser()
{

}

void RayLaser::Update()
{
	Bullet::Update();
	switch (m_state)
	{
	case RayExpand:
		if (--m_nExpandCount)
			t_wid = m_width * (1 - (float)m_nExpandCount / g_nPlayTime);
		else
			m_state = RayHold;// (RayState)(cnt_open != 0);
		break;
	case RayHold:
		if (m_life < m_nCollapseCount)
			m_state = RayCollapse;
		break;
	case RayCollapse:
		if (--m_nCollapseCount)
			t_wid = m_width * (float)m_nCollapseCount / g_nPlayTime;
		else
			m_state = RayStop;
		break;
	default:
		break;
	}
}

void RayLaser::Draw( LPainter& painter )
{
	int bulletWidth = 0;
	m_visual.hGraph.getSize(&bulletWidth, nullptr);
	bulletWidth /= 16;
	painter.drawExtRotaGraph(m_phyData.position, t_wid, m_length, m_phyData.radian + Radian90, m_visual.hGraph, turnFlag);
// 	painter.drawRotaGraphF(m_phyData.position, bulletWidth * t_wid, Radian0, LImage(Resource::laserEffect((m_style.color + 15) & 0x7/*%8*/)), true);

	DrawHitBox(painter);
}

