#include "stdafx.h"
#include "LPlayerModel.h"
#include "LSize.h"

LEmptyPlayerMocel LEmptyPlayerMocel::s_instance;

LPlayerModel::LPlayerModel()
{
}

LPlayerModel::~LPlayerModel()
{
}

void LTHPlayerModel::load(LGraphHandle texture)
{
	const LSize sz(32, 48);
	const int row = 3;
	const int col = 8;
	for (int i = 0; i < StateCount; ++i)
		m_player.registerState();

	m_player.getState(stNormal).assign(texture.split(0, stNormal * sz.height(), col, col, 1, sz.width(), sz.height()));
	m_player.getState(stLeft).assign(texture.split(0, stLeft * sz.height(), col, col, 1, sz.width(), sz.height()));
	m_player.getState(stRight).assign(texture.split(0, stRight * sz.height(), col, col, 1, sz.width(), sz.height()));

	const int moveLoopPos = 4;
	m_player.getState(stLeft).setLoopPos(moveLoopPos);
	m_player.getState(stRight).setLoopPos(moveLoopPos);

	m_curState = stNormal;
	m_player.changeState(m_curState);
}

void LTHPlayerModel::update(uint state)
{
	anime().next();
	if (m_curState != state)
	{
		m_curState = state;
		m_player.changeState(state);
	}
}
