#include "stdafx.h"
#include "LUnifiedTimer.h"

LUnifiedTimer::LUnifiedTimer(void)
	: m_startTime(0), m_fps(0), m_totalMsec(0)
	, m_cursor(0), m_nFpsUpdateFrame(FpsUpdateInterval), m_currentFrame(0)
{	
	for (int i = 0; i < cacheSize; i++)
	{
		if (i % 3 == 0)
			m_cache[i] = 17;
		else
			m_cache[i] = 16;
		m_totalMsec += m_cache[i];
	}
}

LUnifiedTimer::~LUnifiedTimer(void)
{
}

void LUnifiedTimer::start()
{	
	m_timer.start();
	m_startTime = m_timer.elapsed();
}

void LUnifiedTimer::update()
{
	const int nMsecPreSec = 1000;

	++m_currentFrame;
	if (++m_cursor == cacheSize)
		m_cursor = 0;

	// 更新fps数值
	if (m_nFpsUpdateFrame == m_currentFrame)
	{
		m_nFpsUpdateFrame += FpsUpdateInterval;
		m_fps = cacheSize * 1000.0f / m_totalMsec;
	}

	qint64 spendTime = m_timer.elapsed() - m_startTime;
	int nSleepTime = 17 - spendTime;
	if (nSleepTime > 1)
		Sleep(nSleepTime);

	qint64 curTime = m_timer.elapsed();
	// 覆盖最旧的数据，更新总和
	spendTime = curTime - m_startTime;
	m_totalMsec += spendTime - m_cache[m_cursor];
	m_cache[m_cursor] = spendTime;
	m_startTime = curTime; 
}