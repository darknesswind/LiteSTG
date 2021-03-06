#ifndef _LPLAYERS_H_
#define _LPLAYERS_H_
#pragma once
#include "Manager/SpriteManager.h"
#include "LPlayer.h"

class LPlayers : public SpriteManager<LPlayer>
{
public:
	LPlayers();

	static void LoadAssets(LPCWSTR path, bool bBinary = true);

	LPlayer* Add(uint characterID, LPlayer::InputType type);
	LPlayer* GetActiveItem() { return m_pActiveItem; }

protected:
	LPlayer* m_pActiveItem;

	static std::vector<PlayerCharaData> s_datas;
};
#endif