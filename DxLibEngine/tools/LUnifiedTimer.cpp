#include "stdafx.h"
#include "LUnifiedTimer.h"

int64 LPerformanceTimer::s_counterFrequency = 0;

LPerformanceTimer::LPerformanceTimer()
{
	if (0 == s_counterFrequency)
	{
		LARGE_INTEGER frequency;
		BOOL bSucceed = QueryPerformanceFrequency(&frequency);
		LAssert(bSucceed);
		s_counterFrequency = frequency.QuadPart;
	}
}

int64 LPerformanceTimer::ticksToNanoseconds(int64 ticks)
{
	// QueryPerformanceCounter uses an arbitrary frequency
	int64 seconds = ticks / s_counterFrequency;
	int64 nanoSeconds = (ticks - seconds * s_counterFrequency) * 1000000000 / s_counterFrequency;
	return seconds * 1000000000 + nanoSeconds;
}

int64 LPerformanceTimer::start()
{
	m_tBegin = getTickCount();
	return m_tBegin;
}

int64 LPerformanceTimer::getTickCount()
{
	LARGE_INTEGER counter;
	// On systems that run Windows XP or later, the function will always succeed and will thus never return zero.
	BOOL bSucceed = QueryPerformanceCounter(&counter);
	LAssert(bSucceed);
	return counter.QuadPart;
}

int64 LPerformanceTimer::elapsed()
{
	int64 elapsed = getTickCount() - m_tBegin;
	return ticksToNanoseconds(elapsed) / 1000000;
}

//////////////////////////////////////////////////////////////////////////
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

	int64 spendTime = m_timer.elapsed() - m_startTime;
	int nSleepTime = 17 - spendTime;
	if (nSleepTime > 1)
		Sleep(nSleepTime);

	int64 curTime = m_timer.elapsed();
	// 覆盖最旧的数据，更新总和
	spendTime = curTime - m_startTime;
	m_totalMsec += spendTime - m_cache[m_cursor];
	m_cache[m_cursor] = spendTime;
	m_startTime = curTime; 
}
