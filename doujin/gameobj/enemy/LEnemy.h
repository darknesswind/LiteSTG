#ifndef _ENEMY_H_
#define _ENEMY_H_
#pragma once
#include "LGameObject.h"

class LShooters;
class LEnemy : public LGameObject
{
public:
	explicit LEnemy(IGameObject* pParent, int _enemyStyle = 0);
	virtual ~LEnemy(void);

public:	// IGameObject
	virtual void	Update();
	virtual void	Draw();
	virtual const LGraphHandle GetGraphHandle() const;

public:
	LShooters* GetShooters() { return m_spShooters.get(); }

private:
	std::auto_ptr<LShooters> m_spShooters;
	std::auto_ptr<IWalker> m_spWalker;

	bool m_bFace;
	int m_counter;
	int m_imgCount;
	int m_enemyStyle;
};

#endif