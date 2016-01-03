#include "stdafx.h"
#include "LUIObjBase.h"
#include "painting/LRender.h"

LUIObjBase::LUIObjBase(LUIObjBase* parent /*= nullptr*/, bool bAutoDel /*= false*/)
	: m_pParent(parent)
	, m_bAutoDelete(bAutoDel)
{
// 	if (!m_pParent)
// 		m_pParent = LEngine::rootUI();

	if (m_pParent)
		m_pParent->m_children.push_back(this);

	m_renderArg.uDepth = RenderDepthBase::DepthUI;
}

LUIObjBase::~LUIObjBase()
{
	clearChildren();
}

void LUIObjBase::Update()
{
	for each (LUIObjBase* pChild in m_children)
		pChild->Update();
}

void LUIObjBase::Draw(LPainter& painter)
{
	for each (LUIObjBase* pChild in m_children)
		pChild->Draw(painter);
}

bool LUIObjBase::addChild(LUIObjBase* pChild)
{
	if (!pChild)
		return false;

	LUIObjBase* pOldParent = pChild->m_pParent;
	if (this == pOldParent)
		return true;
	else if (pOldParent)
		pOldParent->removeChild(pChild);

	pChild->m_pParent = this;
	m_children.push_back(pChild);
	return true;
}

bool LUIObjBase::removeChild(LUIObjBase* child)
{
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if (*iter == child)
		{
			m_children.erase(iter);
			return true;
		}
	}
	return false;
}

void LUIObjBase::clearChildren()
{
	for each (LUIObjBase* pChild in m_children)
	{
		if (pChild->autoDelete())
			delete pChild;
	}
	m_children.clear();
}

void LUIObjBase::commitRender(LRender* pRender)
{
	pRender->PushItem(this);
	for each (LUIObjBase* pChild in m_children)
		pChild->commitRender(pRender);
}

void LUIRoot::commitRender()
{
	LUIObjBase::commitRender(LEngine::render());
}
