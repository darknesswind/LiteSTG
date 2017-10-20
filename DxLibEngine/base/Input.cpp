#include "stdafx.h"
#include "Input.h"

LInput::LInput(void)
	: m_nJoyNum(0)
{
	m_curKeyState.fill(0);
	m_keyList.fill(KeyState::None);
	m_logicKeyMap.fill(Keys::None);

	m_nJoyNum = DxLib::GetJoypadNum();
}

LInput::~LInput(void)
{
}

bool LInput::update()
{
	const bool bSucceed = (0 == DxLib::GetHitKeyStateAll(m_curKeyState.data()));
	for (int i = 0; i < KeyCount; ++i)
	{
// 		keyList[i] = (KeyState)(((keyList[i] | 2) == 2 ? 0 : 2) | curKeyState[i]);
		m_keyList[i] = static_cast<KeyState>(((static_cast<uchar>(m_keyList[i]) << 1) & 0x2) | m_curKeyState[i]);
	}
	CheckRes(DxLib::GetMousePoint(&m_mousePos.rx(), &m_mousePos.ry()));
	return bSucceed;
}
