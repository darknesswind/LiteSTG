#ifndef _PLAYER_H_
#define _PLAYER_H_
#pragma once
#include "LGameObject.h"

enum class PlayerType
{
	Void,
	Controlled,
};

class LPlayerModel;
class LPlayer : public LCollideObject
{
public:
	explicit LPlayer(int x = 220, int y = 400);
	virtual ~LPlayer(void);

	void setModel(LPlayerModel* pModel);

public:	// IGameobj
	virtual void Update() override;
	virtual void draw(LPainter& painter) override;

public:	// Player
	virtual PlayerType GetType() const { return PlayerType::Void; }

protected:
	destory_ptr<IWalker> m_spWalker;
	LPlayerModel* m_pModel = nullptr;
};
#endif