#ifndef _LPLAYERS_H_
#define _LPLAYERS_H_
#pragma once
#include "Manager/SpriteManager.h"
#include "LPlayer.h"

class LPlayer;
class LPlayers : public SpriteManager<LPlayer>
{
public:
	LPlayers();

	LPlayer* Add(PlayerType type);
	LPlayer* GetActiveItem() { return m_pActiveItem; }

protected:
	LPlayer* m_pActiveItem;
};
#endif