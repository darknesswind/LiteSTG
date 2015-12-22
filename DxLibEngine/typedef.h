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

#define USE_PPL 0

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
#	define AssertSizeEqual(Type1, Type2) static_assert(sizeof(Type1) == sizeof(Type2), "sizeof(" #Type1 ") != sizeof(" #Type2 ")");
#else
#	define DeleteFunc(FuncDef)	FuncDef;
#	define AssertSizeEqual(Type1, Type2)
#endif

#ifndef _MSC_VER
#	define __interface __declspec(novtable) struct
#endif
#ifdef PURE
#	undef PURE
#endif
#ifndef PURE
#	define PURE =0
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

#pragma endregion

#include "Vector2.hpp"
#include "enumations.h"

#if USE_PPL
#	include <ppl.h>
#	include <concurrent_vector.h>
using namespace Concurrency;
#endif

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

#pragma region Interfaces
class LGraphHandle;
class LPainter;
struct RenderArgument;
struct PhysicData;

__interface IDestructible
{
	virtual void destory() PURE;
};

__interface IDrawable
{
	virtual void Draw(LPainter& painter) PURE;
	virtual void DrawHitBox(LPainter& painter) PURE;
};

__interface IDrawableObj : public IDrawable
{
	virtual const LGraphHandle GetGraphHandle() const PURE;
	virtual const RenderArgument& GetRenderArgument() const PURE;
};

__interface IWalker : IDestructible
{
	virtual void nextStep(PhysicData& data) PURE;
};

__interface IGameObject : public IDrawableObj
{
	virtual void			Update()				PURE;
	virtual bool			IsValid() const			PURE;
	virtual void			SetValid(bool bValid)	PURE;
	virtual IGameObject*	GetParent()				PURE;
	virtual const Vector2&	GetPosition()			PURE;
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
