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
	virtual void update() = 0;

	LFixedAnime& anime() { return m_player; }

protected:
	LFixedAnime m_player;
};

class LEmptyPlayerMocel : public LPlayerModel
{
public:
	void load(LGraphHandle texture) override final {}
	void update() override final {}
	static LEmptyPlayerMocel s_instance;
};

class LTHPlayerModel : public LPlayerModel
{
public:
	using LPlayerModel::LPlayerModel;

	void load(LGraphHandle texture) override;
	void update() override final;

protected:
	LGraphHandle m_privateImg;
};
