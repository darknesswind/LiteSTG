#include "stdafx.h"
#include "LAnime.h"

void LAnimePart::EnterCut()
{
	m_curIdx = 0;
}

void LAnimePart::Update()
{
	++m_curIdx;
	if (m_curIdx >= m_graphs.size())
		m_curIdx = m_loopPos;
}
