#ifndef __LIMAGE_H__
#define __LIMAGE_H__
#pragma once
#include <QSize>
#include "LHandle.h"

class LPainter;

class LImage
{
public:
	LImage(void);
	LImage(LGraphHandle handle);
	LImage(int width, int height, bool bNotUse3D = false);
	LImage(LPCWSTR FileName, bool bNotUse3D = false);
	LImage(const LImage& other) { m_handle = other.m_handle; }
	~LImage(void);
	friend LPainter;

public:
	void operator=(LGraphHandle handle) { m_handle = handle; }

public:
	int width() const;
	int height() const;
	QSize size() const;

public:
	static void ReloadFileGraphAll();

private:

private:
	const DxLib::IMAGEDATA2* innerData() const;

private:
	LGraphHandle m_handle;	// 仅作引用，不管理生命周期；
};

#endif // !__LIMAGE_H__