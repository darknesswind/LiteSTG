#include "stdafx.h"
#include "LPathWalker.h"
#include "base/LEngine.h"
#include "move/LPathSet.h"

LPathWalker::LPathWalker()
	: LPathWalker(0)
{
}

LPathWalker::LPathWalker(uint id)
	: m_curFrame(0)
{
	setPath(id);
	if (m_pPath)
		m_curNode = m_pPath->cend();
}

LPathWalker::~LPathWalker()
{
}

void LPathWalker::nextStep(PhysicData& data)
{
	if (!m_pPath || m_pPath->empty())
		return;

	if (m_pPath->cend() == m_curNode)
	{
		m_curNode = m_pPath->cbegin();
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

void LPathWalker::setPath(uint id)
{
	m_pPath = LStgEngine::engine()->pathSet()->getPath(id);
}
