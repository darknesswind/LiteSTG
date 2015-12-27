#ifndef __LBULLETSTYLES_H__
#define __LBULLETSTYLES_H__

#pragma once

class LBulletStyle
{
	friend class LBulletStyles;
public:


	BulletType type = BulletType::Generic;
	EntityData entity;
	LGraphHandles elems;
};

class LBulletStyles
{
public:
	LBulletStyles();
	~LBulletStyles();

public:
	void LoadBulletStyles();

private:
	std::vector<LBulletStyle> m_styles;
	std::map<std::wstring, LBulletStyle*> m_nameMap;
};

#endif	// !__LBULLETSTYLES_H__
