#include "stdafx.h"
#include "Globle.h"
#include "CurveLaser.h"
#include "resource.h"
#include "LPainter.h"
#include "LImage.h"
#include "Input.h"

void CurveLaser::Update()
{
	Vector2 curPos(Input.mousePos());

	if (m_grids.empty())
	{
		m_grids.push_front(LaserGrid(curPos));
	}
	else
	{
		Vector2& lastPos = m_grids.front().trunkPos;
		Vector2 dir(curPos - lastPos);
		if (dir.isFuzzyNull())
			return;

		dir.rotate(Radian270);
		dir.normalize();
		dir *= m_nWidth;
		if (1 == m_grids.size())
		{
			m_grids.front().leftPos = lastPos + dir;
			m_grids.front().rightPos = lastPos - dir;
		}
		else if (m_grids.size() >= 2)
		{
			Vector2 prevDir = (curPos - m_grids[1].trunkPos) / 2;
			prevDir.rotate(Radian270);
			prevDir.normalize();
			prevDir *= m_nWidth;
			m_grids.front().leftPos = lastPos + prevDir;
			m_grids.front().rightPos = lastPos - prevDir;
		}
		m_grids.push_front(LaserGrid(curPos, curPos + dir, curPos - dir));
	}

	if (m_grids.size() > g_MaxGridSize)
		m_grids.pop_back();
}

void CurveLaser::Draw( LPainter& painter )
{
	if (m_grids.size() <= 1)
		return;

	const static VERTEX2D g_vertexTemplate = { { 0.0f, 0.0f }, 1.0f, { 0xFF, 0xFF, 0xFF, 0xFF }, 0.0f, 0.0f };
	static VERTEX2D vertexs[2 * g_MaxGridSize];
	memset(vertexs, 0, sizeof(VERTEX2D) * 2 * g_MaxGridSize);

	int i = 0;
	for (LaserGrids::iterator iter = m_grids.begin();
		iter != m_grids.end();
		++iter)
	{
		vertexs[i] = g_vertexTemplate;
		vertexs[i].pos = iter->leftPos;
		vertexs[i + 1] = g_vertexTemplate;
		vertexs[i + 1].pos = iter->rightPos;

		int nMain = i / 2;
		float pres = (float)nMain / (g_MaxGridSize - 1);
		vertexs[i].u = pres;
		vertexs[i].v = 0;
		vertexs[i + 1].u = pres;
		vertexs[i + 1].v = 1.0 / 16;

		i += 2;
	}

// 	painter.setDrawBlendMode(DxBlendMode::Add, 100);
//  painter.setDrawMode(DxDrawMode::Bilinear);
	painter.drawPrimitive2D(vertexs, 2 * g_MaxGridSize, PrimitiveType::TriangleStrip, Resource::bullet(BulletStyle(曲线激光)), true);
//  painter.setDrawMode(DxDrawMode::Nearest);
// 	painter.setDrawBlendMode(DxBlendMode::NoBlend, 0);
}

