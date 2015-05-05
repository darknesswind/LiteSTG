#include "stdafx.h"
#include "DebugInfo.h"
#include "Globle.h"
#include "shooter/LShooter.h"
#include "player/player.h"
#include "Engine.h"
#include "bullet/Bullet.h"
#include "LPainter.h"
#include "QString"
#include "Input.h"
#include "Vector3.hpp"
#include "resource.h"

#define TH_X 430
#define TH_Y 15
#define TH_DY 15

void DebugInfo::Draw()
{
	Player* pPlayer = Engine.GetActivePlayer();
	if (pPlayer)
	{
		Painter.drawString(
			TH_X, TH_Y,
			QWSTR(QString("Player (%1, %2)").arg(pPlayer->position().x()).arg(pPlayer->position().y())),
			LRgb::White);
	}
	Painter.drawString(
		TH_X, TH_Y + TH_DY,
		QWSTR(QString("Bullet: %1").arg(Engine.GetBullets()->GetCount())),
		LRgb::White);
	Painter.drawString(
		0, 0,
		QWSTR(QString::number(Engine.unifiedTimer().fps(), 'f', 2)),
		LRgb::White);
}

void DebugInfo::Update()
{
}
