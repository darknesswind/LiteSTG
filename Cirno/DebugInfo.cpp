#include "stdafx.h"
#include "DebugInfo.h"
#include "shooter/LShooter.h"
#include "player/LPlayer.h"
#include "CirnoEngine.h"
#include "bullet/LBullets.h"
#include "render/LPainter.h"
#include "Input.h"
#include "Vector3.hpp"

#define TH_X 430
#define TH_Y 15
#define TH_DY 15

void DebugInfo::Draw( LPainter& painter )
{
	LPlayer* pPlayer = LStgEngine::engine()->getActivePlayer();
	if (pPlayer)
	{
		painter.drawString(
			TH_X, TH_Y,
			LStrBuilder(L"Player (%1, %2)").arg(pPlayer->position().x()).arg(pPlayer->position().y()).apply().c_str(),
			LRgb::White);
	}
	painter.drawString(
		TH_X, TH_Y + TH_DY,
		LStrBuilder(L"Bullet: %1").arg(LStgEngine::bullets()->size()).apply().c_str(),
		LRgb::White);
	painter.drawString(
		0, 0,
		LString::number(LStgEngine::engine()->unifiedTimer().fps(), 2).c_str(),
		LRgb::White);
}

void DebugInfo::Update()
{
}
