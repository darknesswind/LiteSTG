#include "stdafx.h"
#include "LPlayers.h"
#include "player.h"
#include "LControlledPlayer.h"

LPlayers::LPlayers()
	: m_pActiveItem(nullptr)
{

}

Player* LPlayers::Add(PlayerType type)
{
	Player* pPlayer = nullptr;
	switch (type)
	{
	case PlayerType::Controlled:
		pPlayer = new LControlledPlayer;
		break;
	default:
		pPlayer = new Player;
		break;
	}

	m_thisList.push_back(pPlayer);
	if (!m_pActiveItem)
		m_pActiveItem = pPlayer;
	return pPlayer;
}
