#include "stdafx.h"
#include "LPathNodes.h"

LPathNodes::LPathNodes()
	: m_id(0)
{

}

LPathNodes::~LPathNodes()
{
	clear();
}

LPathNode* LPathNodes::AddEmptyNode(uint frames)
{
	LPathNode* pNode = new LPathNode(frames);
	m_nodes.push_back(pNode);
	return pNode;
}

LLinePathNode* LPathNodes::AddLineNode(const Vector2& detla, uint frames)
{
	LLinePathNode* pNode = new LLinePathNode(detla, frames);
	m_nodes.push_back(pNode);
	return pNode;
}

LSinePathNode* LPathNodes::AddSineNode(const Vector2& detla, const Vector2& scale, uint frames)
{
	LSinePathNode* pNode = new LSinePathNode(detla, scale, frames);
	m_nodes.push_back(pNode);
	return pNode;
}

void LPathNodes::clear()
{
	for (NodeList::iterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter)
	{
		delete *iter;
		*iter = nullptr;
	}
	m_nodes.clear();
	// 这里出现迭代器错误，证明有迭代器没释放
}

//////////////////////////////////////////////////////////////////////////

LPathNode::LPathNode(uint frames)
	: m_frames(frames)
{
}

Vector2 LPathNode::exec(const Vector2& beginPos, uint curFrame) const
{
	UNUSED(curFrame);
	return beginPos;
}

//////////////////////////////////////////////////////////////////////////

LLinePathNode::LLinePathNode(const Vector2& detla, uint frames)
	: LPathNode(frames)
	, m_detla(detla)
{
	m_speed = m_detla / frames;
}

Vector2 LLinePathNode::exec(const Vector2& beginPos, uint curFrame) const
{
	if (curFrame < m_frames)
		return beginPos + curFrame * m_speed;
	else
		return beginPos + m_detla;
}

//////////////////////////////////////////////////////////////////////////

LSinePathNode::LSinePathNode(const Vector2& detla, const Vector2& scale, uint frames)
	: LPathNode(frames)
	, m_detla(detla)
	, m_scale(scale)
{
	m_fSpeed = m_detla.length() / frames;
	m_dir = detla.radian();
	if (0 == m_scale.x())
		m_scale.setX(1);

	m_endPos.setX(m_detla.length());
	m_endPos.setY(m_scale.y() * Sin(m_endPos.x() / m_scale.x()));
	m_endPos.rotate(m_dir);
}

Vector2 LSinePathNode::exec(const Vector2& beginPos, uint curFrame) const
{
	if (curFrame < m_frames)
	{
		Vector2 res;
		res.setX(curFrame * m_fSpeed);
		res.setY(m_scale.y() * Sin(res.x() / m_scale.x()));
		res.rotate(m_dir);
		return beginPos + res;
	}
	else
	{
		return beginPos + m_endPos;
	}
}
