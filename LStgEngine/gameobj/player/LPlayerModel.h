#pragma once
#include "anime/LAnime.h"

class LPlayerModel
{
public:
	enum State
	{
		stNormal,
		stLeft,
		stRight,

		StateCount
	};

public:
	LPlayerModel();
	virtual ~LPlayerModel();

	virtual void load(LGraphHandle texture) = 0;
	virtual void update(uint state) = 0;

	LFixedAnime& anime() { return m_player; }

protected:
	LFixedAnime m_player;
};

class LEmptyPlayerMocel : public LPlayerModel
{
public:
	void load(LGraphHandle) override final {}
	void update(uint) override final {}
	static LEmptyPlayerMocel s_instance;
};

class LTHPlayerModel : public LPlayerModel
{
public:
	using LPlayerModel::LPlayerModel;

	void load(LGraphHandle texture) override final;
	void update(uint state) override final;

protected:
	LGraphHandle m_privateImg;
	uint m_curState{ 0 };
};
