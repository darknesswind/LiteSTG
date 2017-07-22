#pragma once

class LFixedAnimeCut;
class LStgMoveState
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
	LStgMoveState();
	~LStgMoveState();

public:
	void enter(State st);
	void exec(State st);
	void exit(State st);

private:
	std::array<LFixedAnimeCut*, StateCount> m_anime;
};

