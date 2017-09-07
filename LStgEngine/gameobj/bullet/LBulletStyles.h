#ifndef __LBULLETSTYLES_H__
#define __LBULLETSTYLES_H__

#pragma once
#include "physic/physic.h"

enum class BulletType
{
	Generic,
	SegmentLaser,
	RayLaser,
	CurveLaser,
	Count
};

class LBulletStyle;
struct LBulletVisual
{
	LBulletStyle* pStyle = nullptr;
	LGraphHandle hGraph;
};

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
	void LoadAssets(LPCWSTR path);
	LBulletStyle* getDefaultStyle(BulletType type) { return getStyle(m_defStyles[(uint)type]); }
	LBulletStyle* getStyle(LPCWSTR name);
	LBulletStyle* getStyle(uint idx) { return &m_styles[idx]; }

private:
	std::vector<LBulletStyle> m_styles;
	std::map<std::wstring, uint> m_nameMap;
	std::array<uint, (uint)BulletType::Count> m_defStyles;
};

#endif	// !__LBULLETSTYLES_H__
