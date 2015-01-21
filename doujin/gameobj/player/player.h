#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once
#include "LGameObject.h"

enum class PlayerType
{
	Void,
	Controlled,
};

class CircleEntity;
class Player : public LGameObject
{
public:
	explicit Player(int x = 220, int y = 400);
	virtual ~Player(void);

public:	// IGameobj
	virtual void	Update();
	virtual void	Draw();

public:	// Player
	virtual PlayerType GetType() const { return PlayerType::Void; }

public:
	const CircleEntity* getEntity() const { return m_entity; }

protected:
	std::auto_ptr<IWalker> m_spWalker;
	const CircleEntity* m_entity;
};
#endif