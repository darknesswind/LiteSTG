#include "stdafx.h"
#include "LUIMenu.h"
#include "Input.h"

LUIMenu::LUIMenu()
	: m_activeIdx(0)
	, m_bEnable(true)
	, m_bCanMove(true)
	, m_timeCount(0)
{
}

LUIMenu::~LUIMenu()
{
	for each (LUIMenuItem* pItem in m_items)
		delete pItem;
}

LUIMenuItem* LUIMenu::addMenuItem(LGraphHandle hActive, LGraphHandle hDeactive)
{
	LUIMenuItem* pItem = new LUIMenuItem(hActive, hDeactive);
	m_items.push_back(pItem);
	return pItem;
}

void LUIMenu::Update()
{
	if (!m_bEnable)
		return;

	LInput* pInput = LEngine::input();
	if (pInput->isLogicKeyPress(BaseKey::Ok))
	{
		return OnOk();
	}
	else if (pInput->isLogicKeyPress(BaseKey::Cancel))
	{
		return OnCancel();
	}

	int step = 0;
	if (pInput->isLogicKeyPress(BaseKey::Down))
		++step;
	if (pInput->isLogicKeyPress(BaseKey::Up))
		--step;


	if (!m_bCanMove) // ËÙ¶È¿ØÖÆ
	{
		if (m_timeCount++ > 8)
		{
			m_timeCount = 0;
			m_bCanMove = true;
		}
		return;
	}
	else if (!step)
	{
		if (pInput->isLogicKeyDown(BaseKey::Down))
			++step;
		if (pInput->isLogicKeyDown(BaseKey::Up))
			--step;
	}

	if (step)
	{
		m_activeIdx += step;
		if (m_activeIdx >= (int)m_items.size())
			m_activeIdx = 0;
		else if (m_activeIdx < 0)
			m_activeIdx = m_items.size() - 1;

		m_bCanMove = false;
	}
}

void LUIMenu::Draw(LPainter& painter)
{
	int x = pos().x();
	int y = pos().y();
	for (uint i = 0; i < m_items.size(); ++i)
	{
		LUIMenuItem* pItem = m_items[i];
		if (i == m_activeIdx)
			painter.drawGraph(x, y, pItem->activeImg(), true);
		else
			painter.drawGraph(x, y, pItem->deactiveImg(), true);
		y += pItem->size().height();
	}
}

LUIMenuItem::LUIMenuItem(LGraphHandle hActive, LGraphHandle hDeactive)
	: m_hActive(hActive), m_hDeactive(hDeactive)
{
	m_hActive.getSize(&m_size.rwidth(), &m_size.rheight());
}
