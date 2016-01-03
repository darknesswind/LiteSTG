#ifndef __INPUT_H__
#define __INPUT_H__
#pragma once
#include "LPoint.h"

#pragma region Enum Define

enum class Keys : uchar
{
	Back = 0x0E,	// �˸��
	Tab = 0x0F,	// Tab
	Return = 0x1C,	// �س���

	LShift = 0x2A,	// ��Shift
	RShift = 0x36,	// ��Shift
	LControl = 0x1D,	// ��Control
	RControl = 0x9D,	// ��Control
	Escape = 0x01,	// Esc
	Space = 0x39,	// Space
	PageUp = 0xC9,	// PageUp
	PageDown = 0xD1,	// PageDown
	End = 0xCF,	// End
	Home = 0xC7,	// Home
	Left = 0xCB,	// ��
	Up = 0xC8,	// ��
	Right = 0xCD,	// ��
	Down = 0xD0,	// ��
	Insert = 0xD2,	// Insert
	Delete = 0xD3,	// Delete

	Minus = 0x0C,	// ��
	Dollar = 0x7D,	// $
	Prevtrack = 0x90,	// ��
	Period = 0x34,	// ��
	Slash = 0x35,	// ��
	LAlt = 0x38,	// ��Alt
	RAlt = 0xB8,	// ��Alt
	Scroll = 0x46,	// ScrollLock
	Semicolon = 0x27,	// ��
	Colon = 0x92,	// ��
	LBracket = 0x1A,	// ��
	RBracket = 0x1B,	// ��
	At = 0x91,	// ��
	BackSlash = 0x2B,	// ��
	Comma = 0x33,	// ��
	KanJi = 0x94,	// �h�֥��`
	Convert = 0x79,	// ��Q���`
	NoConvert = 0x7B,	// �o��Q���`
	KaNa = 0x70,	// ���ʥ��`
	Apps = 0xDD,	// ��Ӧ�ó��򡱲˵���
	CapsLock = 0x3A,	// CaspLock
	SysRQ = 0xB7,	// PrintScreen
	Pause = 0xC5,	// PauseBreak
	LWin = 0xDB,	// ��Win
	RWin = 0xDC,	// ��Win

	NumLock = 0x45,	// С���̣�
	NumPad0 = 0x52,	// С���̣�
	NumPad1 = 0x4F,	// С���̣�
	NumPad2 = 0x50,	// С���̣�
	NumPad3 = 0x51,	// С���̣�
	NumPad4 = 0x4B,	// С���̣�
	NumPad5 = 0x4C,	// С���̣�
	NumPad6 = 0x4D,	// С���̣�
	NumPad7 = 0x47,	// С���̣�
	NumPad8 = 0x48,	// С���̣�
	NumPad9 = 0x49,	// С���̣�
	Multiply = 0x37,	// С���̣�
	Add = 0x4E,	// С���̣�
	Subtrack = 0x4A,	// С���̣�
	Decimal = 0x53,	// С���̣�
	Divide = 0xB5,	// С���̣�
	NumPadEnter = 0x9C,	// С����Enter

	F1 = 0x3B,	// �ƣ�
	F2 = 0x3C,	// �ƣ�
	F3 = 0x3D,	// �ƣ�
	F4 = 0x3E,	// �ƣ�
	F5 = 0x3F,	// �ƣ�
	F6 = 0x40,	// �ƣ�
	F7 = 0x41,	// �ƣ�
	F8 = 0x42,	// �ƣ�
	F9 = 0x43,	// �ƣ�
	F10 = 0x44,	// �ƣ���
	F11 = 0x57,	// �ƣ���
	F12 = 0x58,	// �ƣ���

	A = 0x1E,	// ��
	B = 0x30,	// ��
	C = 0x2E,	// ��
	D = 0x20,	// ��
	E = 0x12,	// ��
	F = 0x21,	// ��
	G = 0x22,	// ��
	H = 0x23,	// ��
	I = 0x17,	// ��
	J = 0x24,	// ��
	K = 0x25,	// ��
	L = 0x26,	// ��
	M = 0x32,	// ��
	N = 0x31,	// ��
	O = 0x18,	// ��
	P = 0x19,	// ��
	Q = 0x10,	// ��
	R = 0x13,	// ��
	S = 0x1F,	// ��
	T = 0x14,	// ��
	U = 0x16,	// ��
	V = 0x2F,	// ��
	W = 0x11,	// ��
	X = 0x2D,	// ��
	Y = 0x15,	// ��
	Z = 0x2C,	// ��

	D0 = 0x0B,	// ��
	D1 = 0x02,	// ��
	D2 = 0x03,	// ��
	D3 = 0x04,	// ��
	D4 = 0x05,	// ��
	D5 = 0x06,	// ��
	D6 = 0x07,	// ��
	D7 = 0x08,	// ��
	D8 = 0x09,	// ��
	D9 = 0x0A,	// ��
};

enum class KeyState : char
{
	None,	// 00
	Down,	// 01	������
	Up,		// 10	�½���
	Hold,	// 11
};

#pragma endregion

class LInput
{
public:
	LInput(void);
	~LInput(void);

public:
	bool update();	// ����״̬
	void registerKey(uchar logicKey, Keys physicKey) { m_logicKeyMap[logicKey] = physicKey; }

public: // Physic Input
	bool isKeyPress(Keys key)	const	{ return (KeyState::Down == m_keyList[(uchar)key]); }		// ����������
	bool isKeyRelease(Keys key)	const	{ return (KeyState::Up == m_keyList[(uchar)key]); }			// �������ɿ�
	bool isKeyDown(Keys key)	const	{ return (0 != m_curKeyState[(uchar)key]); }				// ������֡���ڰ���״̬
	bool isKeyHold(Keys key)	const	{ return (KeyState::Hold == m_keyList[(uchar)key]); }		// ��������ס
	KeyState keyState(Keys key) const	{ return m_keyList[(uchar)key]; }							// ����״̬
	
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