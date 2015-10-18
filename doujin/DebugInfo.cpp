#include "stdafx.h"
#include "DebugInfo.h"
#include "Globle.h"
#include "shooter/LShooter.h"
#include "player/player.h"
#include "Engine.h"
#include "bullet/LBullets.h"
#include "LPainter.h"
#include "QString"
#include "Input.h"
#include "Vector3.hpp"
#include "resource.h"

#define TH_X 430
#define TH_Y 15
#define TH_DY 15

void DebugInfo::Draw( LPainter& painter )
{
	Player* pPlayer = StgEngine::engine()->GetActivePlayer();
	if (pPlayer)
	{
		painter.drawString(
			TH_X, TH_Y,
			Q2WSTR(QString("Player (%1, %2)").arg(pPlayer->position().x()).arg(pPlayer->position().y())),
			LRgb::White);
	}
	painter.drawString(
		TH_X, TH_Y + TH_DY,
		Q2WSTR(QString("Bullet: %1").arg(StgEngine::bullets()->GetCount())),
		LRgb::White);
	painter.drawString(
		0, 0,
		Q2WSTR(QString::number(StgEngine::engine()->unifiedTimer().fps(), 'f', 2)),
		LRgb::White);
}

void DebugInfo::Update()
{
}
