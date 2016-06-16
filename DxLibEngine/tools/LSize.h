#pragma once
class LSize
{
public:
	LSize(int width, int height) : m_width(width), m_height(height) {}
	LSize() : LSize(0, 0) {}

	int width() const { return m_width; }
	int height() const { return m_height; }
	int& rwidth() { return m_width; }
	int& rheight() { return m_height; }

private:
	int m_width;
	int m_height;
};