#include "stdafx.h"
#include "LPlayers.h"
#include "LPlayer.h"
#include "LAssets.h"
#include "protobuf.h"

std::vector<PlayerCharaData> LPlayers::s_datas;

LPlayers::LPlayers()
	: m_pActiveItem(nullptr)
{

}

void LPlayers::LoadAssets(LPCWSTR path, bool bBinary /*= true*/)
{
	PlayerDataBuf buff;
	bool bSucc = bBinary ? buff.load(LAssets::LoadRawData(path))
		: buff.loadFromText(LAssets::LoadRawData(path));
	if (!bSucc)
		return;

	auto players = buff.msg()->players();
	for (auto& player : players)
	{
		s_datas.emplace_back(PlayerCharaData());

		PlayerCharaData& data = s_datas.back();
		data.name = LString::fromUtf8(player.name());
		data.collide.fromConfig(player.collide());
		data.graze.fromConfig(player.graze());
		data.normalSpeed = player.normalspeed();
		data.slowSpeed = player.slowspeed();
		data.texture = LString::fromUtf8(player.texture());
	}
}

LPlayer* LPlayers::Add(uint characterID, LPlayer::InputType type)
{
	LPlayer* pPlayer = new LPlayer(type);
	if (characterID < s_datas.size())
		pPlayer->setCharacter(characterID, s_datas[characterID]);

	m_thisList.push_back(pPlayer);
	if (!m_pActiveItem)
		m_pActiveItem = pPlayer;
	return pPlayer;
}
