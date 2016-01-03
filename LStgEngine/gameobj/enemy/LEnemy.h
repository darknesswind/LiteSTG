#ifndef _ENEMY_H_
#define _ENEMY_H_
#pragma once
#include "LGameObject.h"
#include "LHandle.h"

class LShooters;
class LEnemy : public LCollideObject
{
public:
	explicit LEnemy(IGameObject* pParent, int _enemyStyle = 0);
	virtual ~LEnemy(void) override;

public:	// IGameObject
	virtual void	Update() override;
	virtual void Draw(LPainter& painter) override;
	virtual uint GetSortKey() const override;

public:
	LShooters* GetShooters() { return m_spShooters.get(); }

private:
	std::unique_ptr<LShooters> m_spShooters;
	destory_ptr<IWalker> m_spWalker;
	const LGraphHandles* m_pGraphGroup;

	bool m_bFace;
	int m_counter;
	int m_imgCount;
	int m_enemyStyle;
};

#endif