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

	m_player.getState(stLeft).setLoopPos(2);
	m_player.getState(stRight).setLoopPos(2);

	m_player.changeState(stNormal);
// 	LSize szTexture;
// 	texture.getSize(szTexture);
// 	m_privateImg = texture.subGraph(0, 3 * sz.height(), sz.width(), sz.height());
}

void LTHPlayerModel::update()
{
	anime().next();
}
