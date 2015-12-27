#ifndef _LPLAYERS_H_
#define _LPLAYERS_H_
#pragma once
#include "Manager/SpriteManager.h"
#include "player.h"

class Player;
class LPlayers : public SpriteManager<Player>
{
public:
	LPlayers();

	Player* Add(PlayerType type);
	Player* GetActiveItem() { return m_pActiveItem; }

protected:
	Player* m_pActiveItem;
};
#endif