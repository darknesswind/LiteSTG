#include "stdafx.h"
#include "LImage.h"
#include "DxHandle.h"

LImage::LImage(void)
	: m_handle(0)
{
}

LImage::LImage( int width, int height, bool bNotUse3D /*= false*/ )
{
	m_handle = DxLib::MakeGraph(width, height, bNotUse3D);
	LAssert(m_handle);
}

LImage::LImage(const TCHAR* FileName, bool bNotUse3D /*= false*/)
{
	m_handle = DxLib::LoadGraph(FileName, bNotUse3D);
	LAssert(m_handle);
}

LImage::LImage(LGraphHandle handle)
	: m_handle(handle)
{
	LAssert(handle);
}

LImage::~LImage(void)
{
// 	if (m_handle)
// 		CheckRes(DxLib::DeleteGraph(m_handle));
}

const DxLib::IMAGEDATA2* LImage::innerData() const
{
	return m_handle.innerData();
}

#pragma region StaticFunction

void LImage::ReloadFileGraphAll()
{
	CheckRes(DxLib::ReloadFileGraphAll());
}

#pragma endregion

int LImage::width() const
{
	int result = 0;
	CheckRes(DxLib::GetGraphSize(m_handle, &result, nullptr));
	return result;
}

int LImage::height() const
{
	LAssert(m_handle);
	int result = 0;
	CheckRes(DxLib::GetGraphSize(m_handle, nullptr, &result));
	return result;
}

QSize LImage::size() const
{
	LAssert(m_handle);
	int w = 0;
	int h = 0;
	CheckRes(DxLib::GetGraphSize(m_handle, &w, &h));
	return QSize(w, h);
}
