#pragma once
#include "dulpexmap.h"

struct Texture : public DulpexMapItem<Texture>
{
	typedef DulpexMapItem<Texture> Base;
public:
	Texture(const QString& name, const QString& _path)
		: Base(name), path(_path)
	{	}
	Texture(const std::string& name, const std::string& _path)
		: Base(QString::fromUtf8(name.c_str()))
		, path(QString::fromUtf8(_path.c_str()))
	{	}
public:
	QString path;
};
typedef DulpexMap<Texture> TextureMap;

//////////////////////////////////////////////////////////////////////////
struct SubGraphData : public DulpexMapItem<SubGraphData>
{
	typedef DulpexMapItem<SubGraphData> Base;
public:
	enum { ParamCount = 7 };
	using Base::Base;
	bool updateData(const SubGraphData& other)
	{
		iTexture = other.iTexture;
		memcpy(raw, other.raw, sizeof(raw));
		return true;
	}
public:
	uint iTexture{ 0 };
	union
	{
		struct
		{
			uint srcX, srcY;
			uint allNum;
			uint numX, numY;
			uint sizeX, sizeY;
		};
		int raw[ParamCount]{ 0 };
	};
	static_assert(sizeof(decltype(raw)) == sizeof(uint) * ParamCount, "ParamCount may be error");
};
typedef DulpexMap<SubGraphData> SubGraphInfos;
template <> void SubGraphInfos::onErase(uint id, IContainer*)
{
	for (auto& pair : m_entryMap)
	{
		if (pair.second.iTexture == id)
			pair.second.iTexture = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
struct BulletStyle : public DulpexMapItem<BulletStyle>
{
	typedef DulpexMapItem<BulletStyle> Base;
public:
	enum BulletType
	{
		tGeneral,
		tRay,
		tSegment,
		tCurve,
	};
	enum CollideType
	{
		cCircle,
		cRectangle,
	};
	using Base::Base;
	bool updateData(const BulletStyle& other)
	{
		type = other.type;
		collide = other.collide;
		centerX = other.centerX;
		centerY = other.centerY;
		radianX = other.radianX;
		radianY = other.radianY;
		iSubGraph = other.iSubGraph;
		return true;
	}

public:
	BulletType type{ tGeneral };
	CollideType collide{ cCircle };
	qreal centerX{ 0 };
	qreal centerY{ 0 };
	qreal radianX{ 0 };
	qreal radianY{ 0 };

	uint iSubGraph{ 0 };
};
typedef DulpexMap<BulletStyle> BulletStyles;
template <> void BulletStyles::onErase(uint id, IContainer*)
{
	for (auto& pair : m_entryMap)
	{
		if (pair.second.iSubGraph == id)
			pair.second.iSubGraph = 0;
	}
};
