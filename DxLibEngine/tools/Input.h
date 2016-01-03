#ifndef __INPUT_H__
#define __INPUT_H__
#pragma once
#include "LPoint.h"

#pragma region Enum Define

enum class Keys : uchar
{
	Back = 0x0E,	// 退格键
	Tab = 0x0F,	// Tab
	Return = 0x1C,	// 回车键

	LShift = 0x2A,	// 左Shift
	RShift = 0x36,	// 右Shift
	LControl = 0x1D,	// 左Control
	RControl = 0x9D,	// 右Control
	Escape = 0x01,	// Esc
	Space = 0x39,	// Space
	PageUp = 0xC9,	// PageUp
	PageDown = 0xD1,	// PageDown
	End = 0xCF,	// End
	Home = 0xC7,	// Home
	Left = 0xCB,	// 左
	Up = 0xC8,	// 上
	Right = 0xCD,	// 右
	Down = 0xD0,	// 下
	Insert = 0xD2,	// Insert
	Delete = 0xD3,	// Delete

	Minus = 0x0C,	// －
	Dollar = 0x7D,	// $
	Prevtrack = 0x90,	// ＾
	Period = 0x34,	// ．
	Slash = 0x35,	// ／
	LAlt = 0x38,	// 左Alt
	RAlt = 0xB8,	// 右Alt
	Scroll = 0x46,	// ScrollLock
	Semicolon = 0x27,	// ；
	Colon = 0x92,	// ：
	LBracket = 0x1A,	// ［
	RBracket = 0x1B,	// ］
	At = 0x91,	// ＠
	BackSlash = 0x2B,	// ＼
	Comma = 0x33,	// ，
	KanJi = 0x94,	// 漢字キー
	Convert = 0x79,	// 変換キー
	NoConvert = 0x7B,	// 無変換キー
	KaNa = 0x70,	// カナキー
	Apps = 0xDD,	// “应用程序”菜单键
	CapsLock = 0x3A,	// CaspLock
	SysRQ = 0xB7,	// PrintScreen
	Pause = 0xC5,	// PauseBreak
	LWin = 0xDB,	// 左Win
	RWin = 0xDC,	// 右Win

	NumLock = 0x45,	// 小键盘０
	NumPad0 = 0x52,	// 小键盘０
	NumPad1 = 0x4F,	// 小键盘１
	NumPad2 = 0x50,	// 小键盘２
	NumPad3 = 0x51,	// 小键盘３
	NumPad4 = 0x4B,	// 小键盘４
	NumPad5 = 0x4C,	// 小键盘５
	NumPad6 = 0x4D,	// 小键盘６
	NumPad7 = 0x47,	// 小键盘７
	NumPad8 = 0x48,	// 小键盘８
	NumPad9 = 0x49,	// 小键盘９
	Multiply = 0x37,	// 小键盘＊
	Add = 0x4E,	// 小键盘＋
	Subtrack = 0x4A,	// 小键盘－
	Decimal = 0x53,	// 小键盘．
	Divide = 0xB5,	// 小键盘／
	NumPadEnter = 0x9C,	// 小键盘Enter

	F1 = 0x3B,	// Ｆ１
	F2 = 0x3C,	// Ｆ２
	F3 = 0x3D,	// Ｆ３
	F4 = 0x3E,	// Ｆ４
	F5 = 0x3F,	// Ｆ５
	F6 = 0x40,	// Ｆ６
	F7 = 0x41,	// Ｆ７
	F8 = 0x42,	// Ｆ８
	F9 = 0x43,	// Ｆ９
	F10 = 0x44,	// Ｆ１０
	F11 = 0x57,	// Ｆ１１
	F12 = 0x58,	// Ｆ１２

	A = 0x1E,	// Ａ
	B = 0x30,	// Ｂ
	C = 0x2E,	// Ｃ
	D = 0x20,	// Ｄ
	E = 0x12,	// Ｅ
	F = 0x21,	// Ｆ
	G = 0x22,	// Ｇ
	H = 0x23,	// Ｈ
	I = 0x17,	// Ｉ
	J = 0x24,	// Ｊ
	K = 0x25,	// Ｋ
	L = 0x26,	// Ｌ
	M = 0x32,	// Ｍ
	N = 0x31,	// Ｎ
	O = 0x18,	// Ｏ
	P = 0x19,	// Ｐ
	Q = 0x10,	// Ｑ
	R = 0x13,	// Ｒ
	S = 0x1F,	// Ｓ
	T = 0x14,	// Ｔ
	U = 0x16,	// Ｕ
	V = 0x2F,	// Ｖ
	W = 0x11,	// Ｗ
	X = 0x2D,	// Ｘ
	Y = 0x15,	// Ｙ
	Z = 0x2C,	// Ｚ

	D0 = 0x0B,	// ０
	D1 = 0x02,	// １
	D2 = 0x03,	// ２
	D3 = 0x04,	// ３
	D4 = 0x05,	// ４
	D5 = 0x06,	// ５
	D6 = 0x07,	// ６
	D7 = 0x08,	// ７
	D8 = 0x09,	// ８
	D9 = 0x0A,	// ９
};

enum class KeyState : char
{
	None,	// 00
	Down,	// 01	上升沿
	Up,		// 10	下降沿
	Hold,	// 11
};

#pragma endregion

class LInput
{
public:
	LInput(void);
	~LInput(void);

public:
	bool update();	// 更新状态
	void registerKey(uchar logicKey, Keys physicKey) { m_logicKeyMap[logicKey] = physicKey; }

public: // Physic Input
	bool isKeyPress(Keys key)	const	{ return (KeyState::Down == m_keyList[(uchar)key]); }		// 按键被按下
	bool isKeyRelease(Keys key)	const	{ return (KeyState::Up == m_keyList[(uchar)key]); }			// 按键被松开
	bool isKeyDown(Keys key)	const	{ return (0 != m_curKeyState[(uchar)key]); }				// 按键这帧处于按下状态
	bool isKeyHold(Keys key)	const	{ return (KeyState::Hold == m_keyList[(uchar)key]); }		// 按键被按住
	KeyState keyState(Keys key) const	{ return m_keyList[(uchar)key]; }							// 按键状态
	
public: // Logic Input
	bool isLogicKeyPress(uchar key)		const { return isKeyPress(m_logicKeyMap[key]); }
	bool isLogicKeyRelease(uchar key)	const { return isKeyRelease(m_logicKeyMap[key]); }
	bool isLogicKeyDown(uchar key)		const { return isKeyDown(m_logicKeyMap[key]); }
	bool isLogicKeyHold(uchar key)		const { return isKeyHold(m_logicKeyMap[key]); }
	KeyState logicKeyState(uchar key)	const { return keyState(m_logicKeyMap[key]); }

public: // Mouse
	LPoint mousePos() const { return m_mousePos; }

private:
	LInput(const LInput&) = delete;
	void operator=(const LInput&) = delete;

protected:
	const static int KeyCount = 256;

	char m_curKeyState[KeyCount];
	KeyState m_keyList[KeyCount];
	std::array<Keys, 0x100> m_logicKeyMap;

	LPoint m_mousePos;

	int m_nJoyNum;
};

#endif // __INPUT_H__