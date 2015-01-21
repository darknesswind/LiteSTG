#ifndef __TYPEDEFINE_H__
#define __TYPEDEFINE_H__

#pragma region Include
#include <cassert>
#pragma endregion

#pragma region TypeDefine

typedef unsigned int uint;
typedef unsigned char uchar;

#pragma endregion

#pragma region Switcher

#if _DEBUG
#	define USE_ASSERT 1
#endif

#pragma endregion

#pragma region MacroDefine

#if USE_ASSERT
#	define LAssert(x) assert(x)
#	define LASSERT(x) LAssert(x)
#	define CheckRes(DxLibFunc)		\
	{								\
		int hr = (DxLibFunc);		\
		assert(0 == hr);			\
	}
#else
#	define LAssert(x)
#	define CheckRes(DxLibFunc) DxLibFunc;
#endif // USE_ASSERT

#if _MSC_VER >= 1800
#	define DeleteFunc(FuncDef)	FuncDef = delete;
#else
#	define DeleteFunc(FuncDef)	FuncDef;
#endif

#ifndef _MSC_VER
#	define __interface __declspec(novtable) struct
#endif
#define PURE = 0

#pragma endregion

#include "Vector2.hpp"
#include "enumations.h"

#pragma region Interfaces
class LGraphHandle;
struct RenderArgument;
struct PhysicData;

__interface IDrawable
{
	virtual void Draw() PURE;
	virtual void DrawHitBox() PURE;
};

__interface IDrawableObj : public IDrawable
{
	virtual const LGraphHandle GetGraphHandle() const PURE;
	virtual const RenderArgument& GetRenderArgument() const PURE;
};

__interface IWalker
{
	virtual void nextStep(PhysicData& data) PURE;
};

__interface IGameObject : public IDrawableObj
{
	virtual void Update() PURE;
	virtual bool IsValid() const PURE;
	virtual void SetValid(bool bValid) PURE;
	virtual IGameObject* GetParent() PURE;
	virtual const Vector2& GetPosition() PURE;
};
#pragma endregion

#pragma region Structs

struct PhysicData
{
	Vector2	position;	// 位置		[in][out]
	Vector2	speed;		// 速度		[in][out]
	Vector2	acceleration;// 加速度	[in]
	float	friction;	// 摩擦		[in]
	Radian	radian;		// 方向		[in][out]

	PhysicData() : friction(0)
	{
	}
};

struct PaintArgument
{
	DxDrawMode drawMode;
	DxBlendMode blendMode;
	int blendParam;

	PaintArgument()
		: drawMode(DxDrawMode::Nearest)
		, blendMode(DxBlendMode::NoBlend)
		, blendParam(0)
	{
	}

	bool operator< (const PaintArgument& rhs) const
	{
		if (drawMode < rhs.drawMode)
			return true;
		else if (drawMode > rhs.drawMode)
			return false;
		else if (blendMode < rhs.blendMode)
			return true;
		else if (blendMode > rhs.blendMode)
			return false;
		else
			return (blendParam < rhs.blendParam);
	}
};

struct RenderArgument
{
	uint uDepth;
	PaintArgument paintArg;

	RenderArgument() : uDepth(0)
	{
	}
	bool operator<(const RenderArgument& rhs) const
	{
		if (uDepth < rhs.uDepth)
			return true;
		else if (uDepth == rhs.uDepth)
			return (paintArg < rhs.paintArg);
		else
			return false;
	}
};

#pragma endregion

#endif
