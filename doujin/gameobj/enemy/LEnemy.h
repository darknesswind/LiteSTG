#ifndef _ENEMY_H_
#define _ENEMY_H_
#pragma once
#include "LGameObject.h"

class LShooters;
class LEnemy : public LGameObject
{
public:
	explicit LEnemy(IGameObject* pParent, int _enemyStyle = 0);
	virtual ~LEnemy(void) override;

public:	// IGameObject
	virtual void	Update() override;
	virtual void Draw(LPainter& painter) override;
	virtual const LGraphHandle GetGraphHandle() const override;

public:
	LShooters* GetShooters() { return m_spShooters.get(); }

private:
	std::auto_ptr<LShooters> m_spShooters;
	destory_ptr<IWalker> m_spWalker;

	bool m_bFace;
	int m_counter;
	int m_imgCount;
	int m_enemyStyle;
};

#endif