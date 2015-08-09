#include "stdafx.h"
#include "LGameObject.h"
#include "LHandle.h"

LGameObject::LGameObject(IGameObject* pParent /*= nullptr*/)
	: m_bValid(true)
	, m_pParent(pParent)
{

}

void LGameObject::DrawHitBox( LPainter& painter )
{

}

const LGraphHandle LGameObject::GetGraphHandle() const
{
	return LGraphHandle::NoneGraph;
}
