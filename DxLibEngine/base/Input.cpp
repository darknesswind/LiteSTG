#include "stdafx.h"
#include "Input.h"

LInput::LInput(void)
	: m_nJoyNum(0)
{
	memset(m_curKeyState, 0, KeyCount);
	memset(m_keyList, 0, KeyCount);

	m_nJoyNum = DxLib::GetJoypadNum();

}

LInput::~LInput(void)
{
}

bool LInput::update()
{
	bool bSucceed = (0 == DxLib::GetHitKeyStateAll(m_curKeyState));
	for (int i = 0; i < KeyCount; ++i)
	{
// 		keyList[i] = (KeyState)(((keyList[i] | 2) == 2 ? 0 : 2) | curKeyState[i]);
		m_keyList[i] = (KeyState)((((char)m_keyList[i] << 1) & 0x2) | m_curKeyState[i]);
	}
	CheckRes(DxLib::GetMousePoint(&m_mousePos.rx(), &m_mousePos.ry()));
	return bSucceed;
}