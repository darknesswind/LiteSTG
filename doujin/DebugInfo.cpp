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
			QString("Player (%1, %2)").arg(pPlayer->position().x()).arg(pPlayer->position().y()).utf16w(),
			LRgb::White);
	}
	Painter.drawString(
		TH_X, TH_Y + TH_DY,
		QString("Bullet: %1").arg(Engine.GetBullets()->GetCount()).utf16w(),
		LRgb::White);
	Painter.drawString(
		0, 0,
		QString::number(Engine.unifiedTimer().fps(), 'f', 2).utf16w(),
		LRgb::White);
}

void DebugInfo::Update()
{
}
