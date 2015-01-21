#include "stdafx.h"
#include "LPathWalker.h"

LPathWalker::LPathWalker()
	: m_curFrame(0)
{
	m_curNode = m_nodes.end();
}

LPathWalker::~LPathWalker()
{

}

void LPathWalker::nextStep(PhysicData& data)
{
	if (m_nodes.empty())
		return;

	if (m_nodes.end() == m_curNode)
	{
		m_curNode = m_nodes.begin();
		m_curFrame = 0;
		m_nodeBegin = data.position;
	}

	LPathNode* pNode = (*m_curNode);
	data.position = pNode->exec(m_nodeBegin, m_curFrame);

	if (++m_curFrame > pNode->getFrames())
	{
		++m_curNode;
		m_curFrame = 0;
		m_nodeBegin = data.position;
	}
}
