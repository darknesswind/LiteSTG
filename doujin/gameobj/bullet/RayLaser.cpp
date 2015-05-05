#include "stdafx.h"
#include "Globle.h"
#include "RayLaser.h"
#include "Graph.h"
#include "resource.h"
#include "LPainter.h"
#include "LImage.h"

RayLaser::RayLaser(IGameObject* pParent)
	: Bullet(pParent)
{
	m_width = 1;
	m_length = 70;
	m_state = RayExpand;
	m_nExpandCount = m_nCollapseCount = g_nPlayTime;

	m_pOriginEntity = EntityFactory::getLaserEntity(0);
	m_pMutableEntity = new RectEntity(*m_pOriginEntity);
	m_pEntity = m_pMutableEntity;

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

void RayLaser::Draw()
{
	LImage imgBullet(GetGraphHandle());
	int bulletWidth = imgBullet.width();
	bulletWidth /= 16;
	Painter.drawExtRotaGraph(m_phyData.position, t_wid, m_length, m_phyData.radian + Radian90, imgBullet, turnFlag);
	Painter.drawRotaGraphF(m_phyData.position, bulletWidth * t_wid, Radian0, LImage(Resource::laserEffect((m_style.color + 15) & 0x7/*%8*/)), true);

	m_pEntity->draw(m_phyData.position, m_phyData.radian + Radian90);
}

