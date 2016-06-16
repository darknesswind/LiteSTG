#include "stdafx.h"
#include "LPlayerModle.h"
#include "LSize.h"

LPlayerModle::LPlayerModle()
{
}


LPlayerModle::~LPlayerModle()
{
}

void LTHPlayerModle::Load(LGraphHandle texture)
{
	const LSize sz(32, 48);
	const int row = 3;
	const int col = 8;
	m_playerImgs = texture.split(0, 0, row * col, col, row, sz.width(), sz.height());

	LSize szTexture;
	texture.getSize(szTexture);
	m_privateImg = texture.subGraph(0, 3 * sz.height(), szTexture.width(), szTexture.height());
}
