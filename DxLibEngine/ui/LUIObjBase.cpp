#include "stdafx.h"
#include "LUIObjBase.h"
#include "render/LRender.h"

LUIObjBase::LUIObjBase(LUIObjBase* parent /*= nullptr*/)
	: m_pParent(parent)
	, m_bAutoDelete(false)
{
// 	if (!m_pParent)
// 		m_pParent = LEngine::rootUI();

	if (m_pParent)
		m_pParent->pushChild(this);

	m_renderArg.uDepth = RenderDepthBase::DepthUI;
}

LUIObjBase::~LUIObjBase()
{
	clearChildren();
}

void LUIObjBase::Update()
{
	for (LUIObjBase* pChild : m_children)
		pChild->Update();
}

void LUIObjBase::draw(LPainter& painter)
{
	for (LUIObjBase* pChild : m_children)
		pChild->draw(painter);
}

LUIObjBase* LUIObjBase::pushChild(LUIObjBase* pChild, bool bAutoDel /*= false*/)
{
	LAssert(pChild);

	LUIObjBase* pOldParent = pChild->m_pParent;
	if (this == pOldParent)
		return pChild;
	else if (pOldParent)
		pOldParent->takeChild(pChild);
	LAssert(!pOldParent || pChild->autoDelete() == bAutoDel);

	pChild->m_pParent = this;
	pChild->setAutoDelete(bAutoDel);
	m_children.push_back(pChild);
	return pChild;
}

void LUIObjBase::popChild()
{
	if (m_children.empty())
		return;

	LUIObjBase* pChild = m_children.back();
	m_children.pop_back();
	if (pChild->autoDelete())
		delete pChild;
}

bool LUIObjBase::removeChild(LUIObjBase* pChild)
{
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if (*iter == pChild)
		{
			m_children.erase(iter);
			if (pChild->autoDelete())
				delete pChild;
			return true;
		}
	}
	return false;
}

bool LUIObjBase::takeChild(const LUIObjBase* pChild)
{
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if (*iter == pChild)
		{
			m_children.erase(iter);
			return true;
		}
	}
	return false;
}

void LUIObjBase::clearChildren()
{
	for (LUIObjBase* pChild : m_children)
	{
		if (pChild->autoDelete())
			delete pChild;
	}
	m_children.clear();
}
