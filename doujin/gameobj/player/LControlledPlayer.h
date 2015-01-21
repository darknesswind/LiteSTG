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
	virtual void	Update();
	virtual void	Draw();
	virtual void	DrawHitBox();
	virtual const LGraphHandle GetGraphHandle() const;

public:	// Player
	virtual PlayerType GetType() const { return PlayerType::Controlled; }

public:

private:
	std::auto_ptr<IWalker> m_spWalker;

	int m_CharacterID;
	int m_imgCount;
	int m_counter;
	int m_actionState;
	int m_nStarImg;
	int m_nEndImg;
	bool m_bCanShot;
};
#endif