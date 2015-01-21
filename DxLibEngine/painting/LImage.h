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
	~LImage(void);
	friend LPainter;

public:
	int width() const;
	int height() const;
	QSize size() const;

public:
	static void ReloadFileGraphAll();

private:
	DeleteFunc(LImage(const LImage& other));
	DeleteFunc(void operator=(const LImage& other));

private:
	const DxLib::IMAGEDATA2* innerData() const;

private:
	LGraphHandle m_handle;
};

#endif // !__LIMAGE_H__