#include "stdafx.h"
#include "LPlayers.h"
#include "LPlayer.h"
#include "LControlledPlayer.h"

LPlayers::LPlayers()
	: m_pActiveItem(nullptr)
{

}

LPlayer* LPlayers::Add(PlayerType type)
{
	LPlayer* pPlayer = nullptr;
	switch (type)
	{
	case PlayerType::Controlled:
		pPlayer = new LControlledPlayer;
		break;
	default:
		pPlayer = new LPlayer;
		break;
	}

	m_thisList.push_back(pPlayer);
	if (!m_pActiveItem)
		m_pActiveItem = pPlayer;
	return pPlayer;
}
