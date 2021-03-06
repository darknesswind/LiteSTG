﻿#pragma once
#define USE_PPL 0
#if _DEBUG
#	define USE_ASSERT 1
#endif

#include <cassert>

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef long long int64;
typedef unsigned long long uint64;
typedef std::vector<uchar> LByteArray;

#include "tools/Vector2.hpp"
#include "enumations.h"

#if USE_PPL
#	include <ppl.h>
#	include <concurrent_vector.h>
using namespace Concurrency;
#endif

class LGraphHandle;
class LPainter;
struct RenderArgument;
struct PhysicData;

#if USE_ASSERT
#	define LAssert(x) {assert(x);}
#	define LASSERT(x) LAssert(x)
#	define CheckRes(DxLibFunc)		\
	{								\
		const int hr = (DxLibFunc);	\
		assert(0 == hr);			\
	}
#else
#	define LAssert(x)
#	define CheckRes(DxLibFunc) DxLibFunc;
#endif // USE_ASSERT

#define AssertSizeEqual(Type1, Type2) static_assert(sizeof(Type1) == sizeof(Type2), "sizeof(" #Type1 ") != sizeof(" #Type2 ")");

#ifndef _MSC_VER
#	define __interface __declspec(novtable) struct
#endif

#define Q2WSTR(qstr) ((const TCHAR*)qstr.utf16())
#define W2QSTR(wstr) (QString::fromUtf16((const ushort*)(wstr)))

#if USE_PPL
#	define parallel_begin(range)	begin(range)
#	define parallel_end(range)		end(range)
#else
#	define parallel_for_each(begin, end, func)\
	{\
		for (auto iter = (begin); iter != (end); ++iter)\
		{\
			func(*iter);\
		}\
	}
#	define parallel_begin(range)	(range).begin()
#	define parallel_end(range)		(range).end()
#endif

#ifndef UNUSED
#	define UNUSED(x) (x);
#endif // !UNUSED

template <class T>
class destory_ptr
{
	typedef destory_ptr<T> _ThisType;
public:
	destory_ptr(T* _ptr = nullptr) : m_ptr(_ptr) {}
	~destory_ptr() { if (m_ptr) m_ptr->destory(); }

	destory_ptr(const _ThisType& other) = delete;
	void operator=(const _ThisType& other) = delete;

	destory_ptr(_ThisType&& other)
	{
		if (m_ptr) m_ptr->destory();
		m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
	}
	void operator=(_ThisType&& other)
	{
		if (m_ptr) m_ptr->destory();
		m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
	}

	T& operator*() { return *m_ptr; }
	T* operator->() { return m_ptr; }
// 	operator T*() { return m_ptr; }
	const T& operator*() const { return *m_ptr; }
	const T* operator->() const { return m_ptr; }


	T* get() { return m_ptr; }
	const T* get() const { return m_ptr; }
	void reset(T* _ptr = nullptr)
	{
		if (m_ptr) m_ptr->destory();
		m_ptr = _ptr;
	}

private:
	T* m_ptr;
};

__interface IDestructible
{
	virtual void destory() = 0;
};

__interface IDrawable
{
	virtual void draw(LPainter& painter) = 0;
};

__interface IDrawableObj : public IDrawable
{
	virtual const RenderArgument& GetRenderArgument() const = 0;
};

__interface IUIObject : public IDrawableObj
{
	virtual void Update() = 0;
};

__interface IWalker : IDestructible
{
	virtual void nextStep(PhysicData& data) = 0;
};

__interface IGameObject : public IDrawableObj
{
	virtual void			Update()				= 0;
	virtual bool			IsValid() const			= 0;
	virtual void			SetValid(bool bValid)	= 0;
	virtual IGameObject*	GetParent()				= 0;
	virtual const Vector2&	GetPosition()			= 0;
};

struct PhysicData
{
	Vector2	position;	// 位置		[in][out]
	Radian	radian;		// 方向		[in][out]
	Vector2	speed;		// 速度		[in][out]
	Vector2	acceleration;// 加速度	[in]
	float	friction;	// 摩擦		[in]

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
		const uint lMode = rawMode();
		const uint rMode = rhs.rawMode();

		if (lMode < rMode)
			return true;
		else if (lMode > rMode)
			return false;
		else
			return (blendParam < rhs.blendParam);
	}
private:
	uint rawMode() const { return *reinterpret_cast<const uint*>(this); }
};
static_assert(sizeof(PaintArgument) == sizeof(ushort) * 2 + sizeof(int), "PaintArgument Layout Error!");

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

