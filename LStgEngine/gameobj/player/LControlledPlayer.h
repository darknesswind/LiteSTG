#ifndef __LCONTROLLEDPLAYER_H__
#define __LCONTROLLEDPLAYER_H__
#pragma once
#include "player.h"

class LControlledPlayer : public Player
{
public:
	explicit LControlledPlayer(int x = 220, int y = 400);
	virtual ~LControlledPlayer(void);
	
public:	// IGameobj
	virtual void	Update() override;
	virtual void	Draw(LPainter& painter) override;
	virtual uint GetSortKey() const override;

public:	// Player
	virtual PlayerType GetType() const override { return PlayerType::Controlled; }

public:

private:
	int m_CharacterID;
	int m_imgCount;
	int m_counter;
	int m_actionState;
	int m_nStarImg;
	int m_nEndImg;
	bool m_bCanShot;

	LGraphHandles m_playerImg;
	LGraphHandle m_hitBoxImg;
	LInput* m_pInput;
};
#endif