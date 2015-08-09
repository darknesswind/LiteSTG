#include "stdafx.h"
#include "Globle.h"
#include "SegmentLaser.h"
#include "resource.h"
#include "CollideEntity/RectEntity.h"
#include "LPainter.h"
#include "LImage.h"

void SegmentLaser::Update()
{
	Vector2 tpos = m_phyData.position;
	Bullet::Update();
	if (m_curScale < m_maxScale)
	{
		m_phyData.position = (tpos + m_phyData.position) / 2;
		int width, height;
		float len = (m_phyData.position - tpos).length();
		DxLib::GetGraphSize(Resource::bullet(m_style), &width, &height);
		m_curScale += 5 * len / height;
		if (m_curScale > m_maxScale)
		{
			m_curScale = m_maxScale;
		}
		m_pMutableEntity->halfOfHeight = m_pOriginEntity->halfOfHeight * m_curScale;
		m_pMutableEntity->center.setY(m_pMutableEntity->halfOfHeight - m_pOriginEntity->halfOfHeight);
	}
}

void SegmentLaser::Draw( LPainter& painter )
{
	painter.drawExtRotaGraph(m_phyData.position, 0.5f, m_curScale, m_phyData.radian + Radian90, LImage(Resource::bullet(m_style)), true);
	m_pEntity->draw(painter, m_phyData.position, m_phyData.radian + Radian90);
}

SegmentLaser& SegmentLaser::setLength(float length)
{
	int x, y;
	DxLib::GetGraphSize(Resource::bullet(m_style), &x, &y);
	m_maxScale = length / y;
	return *this;
}

