#include "stdafx.h"
#include "SegmentLaser.h"
#include "render/LPainter.h"

void SegmentLaser::Update()
{
	Vector2 tpos = m_phyData.position;
	Bullet::Update();
	if (m_curScale < m_maxScale)
	{
		m_phyData.position = (tpos + m_phyData.position) / 2;
		int width, height;
		float len = (m_phyData.position - tpos).length();
		DxLib::GetGraphSize(m_visual.hGraph, &width, &height);
		m_curScale += 5 * len / height;
		if (m_curScale > m_maxScale)
		{
			m_curScale = m_maxScale;
		}
		m_entity.halfHeight = m_originHalfHeight * m_curScale;
		m_entity.center.setY(m_entity.halfHeight - m_originHalfHeight);
	}
}

void SegmentLaser::draw( LPainter& painter )
{
	painter.drawExtRotaGraph(m_phyData.position, 0.5f, m_curScale, m_phyData.radian + Radian90, m_visual.hGraph, true);
	DrawHitBox(painter);
}

SegmentLaser& SegmentLaser::setLength(float length)
{
	int x, y;
	DxLib::GetGraphSize(m_visual.hGraph, &x, &y);
	m_maxScale = length / y;
	return *this;
}

