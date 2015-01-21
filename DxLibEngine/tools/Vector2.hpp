#ifndef _VECTOR2_H_
#define _VECTOR2_H_
#pragma once

#include <utility>
#include <iostream>
#include "LPoint.h"
#include "Angle.h"
#include "DxLib.h"

#pragma warning(disable:4244)
class Vector2
{
public:
	Vector2() : cx(0), cy(0) { }

	template<typename T1, typename T2>
	explicit Vector2(T1 xpos, T2 ypos)
		: cx((float)xpos), cy((float)ypos)
	{
	}

	template<typename posType>
	explicit Vector2(const posType& point)
		: cx((float)point.x()), cy((float)point.y())
	{
	}

	explicit operator LPoint() { return LPoint(cx, cy); }
	operator DxLib::VECTOR() { return *((DxLib::VECTOR*)this); }

	~Vector2(void){};
	
	float x() const { return cx; }
	float y() const { return cy; }
	float& rx() { return cx; }
	float& ry() { return cy; }
	void setX(float fx) { cx = fx; }
	void setY(float fy) { cy = fy; }

	void reset()	{ memset(this, 0, sizeof(Vector2)); }

	void Init(float xpos, float ypos)
	{
		cx = xpos;
		cy = ypos;
	}

	void InitFromPolar(float len, Degree deg)	// 用极坐标方式初始化
	{
		float sine = 0, cosine = 0;
		deg.getSinCos(sine, cosine);
		cx = len * cosine;
		cy = len * sine;
	}
	void InitFromPolar(float len, Radian rad)
	{
		float sine = 0, cosine = 0;
		rad.getSinCos(sine, cosine);
		cx = len * cosine;
		cy = len * sine;
	}	

	static Vector2 fromPolarRad(const float len, const float rad)
	{
		float sine = 0, cosine = 0;
		SinCos(rad, sine, cosine);
		return Vector2(len * cosine, len * sine);
	}
	static Vector2 fromPolarDeg(const float len, const float deg)
	{
		float sine = 0, cosine = 0;
		SinCosDeg(deg, sine, cosine);
		return Vector2(len * cosine, len * sine);
	}

	Vector2 rotated(Radian rad) const	// 返回旋转rad后的向量
	{
		float tx(cx), ty(cy);
		float sine, cosine;
		rad.getSinCos(sine, cosine);
		return Vector2(tx * cosine + ty * sine, tx * sine - ty * cosine);
	}
	Vector2& rotate(Radian rad)	// 将向量旋转rad
	{
		float tx(cx), ty(cy);
		float sine = 0, cosine = 0;
		rad.getSinCos(sine, cosine);
		cx = tx * cosine + ty * sine;
		cy = tx * sine - ty * cosine;
		return *this;
	}
	Vector2& rotateAt(const Vector2 &origin, Radian rad)
	{
		float tx(cx - origin.cx), ty(cy - origin.cy);
		float sine = 0, cosine = 0;
		rad.getSinCos(sine, cosine);
		cx = tx * cosine - ty * sine + origin.cx;
		cy = tx * sine + ty * cosine + origin.cy;
		return *this;
	}

	void negate()	// 取负
	{
		cx = -cx;
		cy = -cy;
	}

	const float dotProduct(const Vector2 &vect2)	// 点积
	{
		return cx * vect2.cx + cy * vect2.cy;
	}
	static const float dotProduct(const Vector2 &vect1, const Vector2 &vect2)	// 点积
	{
		return vect1.cx * vect2.cx + vect1.cy * vect2.cy;
	}

	const Vector2 normalized() const	// 返回向量的单位向量
	{
		double len = double(cx) * double(cx) +
			double(cy) * double(cy);
		if (qFuzzyIsNull(len - 1.0f))
			return *this;
		else if (!qFuzzyIsNull(len))
			return *this / sqrt(len);
		else
			return Vector2();
	}
	const Vector2 normalized(float times) const	// 返回向量的单位向量的times倍
	{
		double len = double(cx) * double(cx) +
			double(cy) * double(cy);
		if (qFuzzyIsNull(len - 1.0f))
			return *this * times;
		else if (!qFuzzyIsNull(len))
			return *this * times / sqrt(len);
		else
			return Vector2();
	}
	void normalize()	// 将向量单位化
	{
		double len = double(cx) * double(cx) +
			double(cy) * double(cy);
		if (qFuzzyIsNull(len - 1.0f) || qFuzzyIsNull(len))
			return;

		len = sqrt(len);

		cx /= len;
		cy /= len;
	}
	void fixFuzzyNull()
	{
		if (qFuzzyIsNull(cx)) cx = 0;
		if (qFuzzyIsNull(cy)) cy = 0;
	}

	const Degree degree() const	// 返回角度形式的向量方向
	{
		return Degree(radian().degree());
	}
	const Radian radian() const	// 返回弧度形式的向量方向
	{
		return Radian(atan2(cy, cx));
	}

	const float length() const	// 返回长度
	{
		return sqrt(cx * cx + cy * cy);
	}
	const float manhattanLength() const	// 曼哈顿距离
	{
		return std::abs(cx) + std::abs(cy);
	}
	const float lengthSquared() const	// 返回长度的平方
	{
		return cx * cx + cy * cy;
	}

	/*
	返回与向量v2的距离
	*/
	const float distance(const Vector2 &v2) const
	{
		return (*this - v2).length();
	}
	/// <summary>
	/// 返回与向量v2的距离的平方
	/// </summary>
	const float distanceSquared(const Vector2 &v2) const
	{
		return (*this - v2).lengthSquared();
	}
	/// <summary>
	/// 返回与向量v2的曼哈顿距离
	/// </summary>
	const float manhattanDistance(const Vector2 &v2) const
	{
		return std::abs(cx - v2.cx) + std::abs(cy - v2.cy);
	}

	static Vector2 reflect(const Vector2 &enter, const Vector2 &normal)
	{
		return enter - 2 * dotProduct(enter, normal) / normal.lengthSquared() * normal;
	}
	/// <summary>
	/// 返回在镜面法向量normal上的反射
	/// </summary>
	/// <param name="normal">法向量</param>
	/// <returns>反射向量</returns>
	Vector2 reflect(const Vector2 &normal)
	{
		return *this - 2 * dotProduct(normal) / normal.lengthSquared() * normal;
	}

	/// <summary>
	/// 返回src在dest上的投影长度
	/// </summary>
	static const float project(const Vector2 &src, const Vector2 &dest)
	{
		return dotProduct(src, dest) / dest.length();
	}
	/// <summary>
	/// 返回在dest上的投影长度
	/// </summary>
	const float project(const Vector2 &dest)
	{
		return dotProduct(dest) / dest.length();
	}

	/// <summary>
	/// 到向量dest的角度夹角（弧度转角度）
	/// </summary>
	Degree degreeBetween(const Vector2& dest) const
	{
		float dx = dest.cx - cx;
		float dy = dest.cy - cy;
		return Degree(Rad2Deg(atan2(dy, dx)));
	}
	/// <summary>
	/// 到向量dest的弧度夹角
	/// </summary>
	Radian radianBetween(const Vector2& dest) const
	{
		float dx = dest.cx - cx;
		float dy = dest.cy - cy;
		return Radian(atan2(dy, dx));
	}


	const Vector2 absed() const	// 对x,y取绝对值后的向量
	{
		return Vector2(std::abs(cx), std::abs(cy));
	}
	void abs()	// 向量绝对值化
	{
		cx = std::abs(cx);
		cy = std::abs(cy);
	}

	bool isNull() const	// 是否为0值
	{
		return qIsNull(cx) && qIsNull(cy);
	}
	bool isFuzzyNull() const	// 约等于0
	{
		return qFuzzyIsNull(cx)
			&& qFuzzyIsNull(cy);
	}
	bool fuzzyCompare(const Vector2 &vect2)	const //  近似比较
	{
		return qFuzzyCompare(cx, vect2.cx)
			&& qFuzzyCompare(cy, vect2.cy);
	}

	bool isDirFuzzyEqual(const Vector2 &vect2) const
	{
		if (isFuzzyNull() || vect2.isFuzzyNull())
			return true;
		bool bVert = qFuzzyIsNull(cx);
		bool bOtherVert = qFuzzyIsNull(vect2.cx);
		if (!bVert && !bOtherVert)
			return qFuzzyCompare(cy / cx, vect2.cy / vect2.cx);
		else if (bVert && bOtherVert)
			return true;
		else
			return false;
	}

public:
	static const Vector2 zero()
	{
		return Vector2(0.0f, 0.0f);
	}

#pragma region 操作符重载

	const bool operator< (const Vector2 &other) const
	{
		return this->manhattanLength() < other.manhattanLength();
	}
	const bool operator> (const Vector2 &other) const
	{
		return this->manhattanLength() > other.manhattanLength();
	}

	const bool operator== (const Vector2 &vect2)const
	{
		return (cx == vect2.cx && cy == vect2.cy);
	}
	const bool operator!= (const Vector2 &vect2)const
	{
		return !operator==(vect2);
	}
	const Vector2 operator+ (const Vector2 &vect2)const
	{
		return Vector2(cx + vect2.cx, cy + vect2.cy);
	}
	const Vector2 operator* (const Vector2 &vect2)const
	{		
		return Vector2(cx * vect2.cx, cy * vect2.cy);
	}

	const Vector2 operator- (const Vector2 &vect2)const
	{		
		return Vector2(cx-vect2.cx, cy-vect2.cy);
	}
	Vector2 &operator+= (const Vector2 &vect2)
	{
		cx += vect2.cx;
		cy += vect2.cy;
		return *this;
	}
	Vector2 &operator-= (const Vector2 &vect2)
	{
		cx -= vect2.cx;
		cy -= vect2.cy;
		return *this;
	}
	Vector2 &operator*= (const Vector2 &vect2)
	{
		cx *= vect2.cx;
		cy *= vect2.cy;
		return *this;
	}
	const Vector2 operator- ()
	{
		return Vector2(-cx, -cy);
	}

	template <class U>
	friend const Vector2 operator*(U u, Vector2 vect2)
	{
		return Vector2(u * vect2.cx, u * vect2.cy);
	}
	template <class U>
	friend const Vector2 operator*(Vector2 vect2, U u)
	{
		return Vector2(u * vect2.cx, u * vect2.cy);
	}
	template <class U>
	friend const Vector2 operator/(Vector2 vect2, U u)
	{
		return Vector2(vect2.cx / u, vect2.cy / u);
	}
	template <class U>
	Vector2& operator*=(U u)
	{
		cx *= u;
		cy *= u;
		return *this;
	}
	template <class U>
	Vector2& operator/=(U u)
	{
		cx /= u;
		cy /= u;
		return this;
	}

#pragma endregion

protected:
	float cx, cy;
};

#endif