#include "stdafx.h"
#include "LAnime.h"

LFixedAnimeCut g_emptyCut;
LFixedAnimeCut::Iterator::Iterator(LFixedAnimeCut* pAnimeCut)
	: m_pAnimeCut(pAnimeCut)
{
	if (m_pAnimeCut->size() > 0)
		m_curGraph = m_pAnimeCut->getGraph(0);
}

void LFixedAnimeCut::Iterator::next()
{
	++m_counter;
	if (m_counter >= m_pAnimeCut->interval())
	{
		m_counter = 0;
		++m_curIdx;
		uint size = m_pAnimeCut->size();
		if (m_curIdx >= size)
			m_curIdx = m_pAnimeCut->loopPos();

		if (size > 0)
			m_curGraph = m_pAnimeCut->getGraph(m_curIdx);
	}
}

//////////////////////////////////////////////////////////////////////////
LFixedAnime::LFixedAnime()
	: m_iterator(g_emptyCut.createIterator())
{

}

bool LFixedAnime::changeState(uint state)
{
	if (state < m_states.size())
	{
		m_iterator = m_states[state].createIterator();
		return true;
	}
	else
	{
		LLogger::Warning(L"Invalid state number!");
		return false;
	}
}
