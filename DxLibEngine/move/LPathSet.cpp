#include "stdafx.h"
#include "LPathSet.h"
#include "base/LAssets.h"
#include "protobuf.h"
#include "LPathNodes.h"

LPathSet::LPathSet()
{
	LPathNodes* pPath = new LPathNodes();
	m_paths.push_back(pPath);
	pPath->setID(0);
	pPath->setName(L"NULL");
}

LPathSet::~LPathSet()
{
}

bool LPathSet::load(LPCWSTR lpFile)
{
	if (!lpFile)
		return false;
	
	PathSetBuf buff;
	buff.load(LAssets::LoadRawData(lpFile));
	buff.saveText(LString(lpFile).append(L".json").c_str());
	auto& paths = buff.pathset()->path();
	for (auto iter = paths.begin(); iter != paths.end(); ++iter)
	{
		LPathNodes* pPath = new LPathNodes();
		m_paths.push_back(pPath);

		pPath->setID(m_paths.size());
		pPath->setName(LString::fromUtf8(iter->name()));
		auto& node = iter->node();
		for (auto itNode = node.begin(); itNode != node.end(); ++itNode)
		{
			if (itNode->has_emptynode())
				parse(pPath, itNode->emptynode());
			else if (itNode->has_linenode())
				parse(pPath, itNode->linenode());
			else if (itNode->has_sinenode())
				parse(pPath, itNode->sinenode());
			else
				LAssert(!"unknown node");
		}
	}
	return true;
}

const LPathNodes* LPathSet::getPath(uint id)
{
	if (id < m_paths.size())
		return m_paths[id];
	else
		return nullptr;
}

void LPathSet::clear()
{
	for (auto iter = m_paths.begin(); iter != m_paths.end(); ++iter)
	{
		delete *iter;
		*iter = nullptr;
	}
	m_paths.clear();
}

void LPathSet::parse(LPathNodes* pPath, const proto::EmptyNode& node)
{
	LAssert(pPath);
	pPath->AddEmptyNode(node.time());
}

void LPathSet::parse(LPathNodes* pPath, const proto::LineNode& node)
{
	LAssert(pPath);
	Vector2 detla(node.xdetla(), node.ydetla());
	pPath->AddLineNode(detla, node.time());
}

void LPathSet::parse(LPathNodes* pPath, const proto::SineNode& node)
{
	LAssert(pPath);
	Vector2 detla(node.xdetla(), node.ydetla());
	Vector2 scale(node.xscale(), node.yscale());
	pPath->AddSineNode(detla, scale, node.time());
}
