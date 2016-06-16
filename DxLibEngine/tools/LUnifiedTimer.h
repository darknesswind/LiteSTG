#ifndef __LUNIFIEDTIMER_H__
#define __LUNIFIEDTIMER_H__
#pragma once

class LPerformanceTimer
{
public:
	LPerformanceTimer();

	inline int64 start();
	inline int64 getTickCount();
	inline int64 elapsed();

public:
	static inline int64 ticksToNanoseconds(int64 ticks);

private:
	static int64 s_counterFrequency;

	int64 m_tBegin = 0;
};

// 计算Fps与帧率控制
class LUnifiedTimer
{
public:
	LUnifiedTimer(void);
	~LUnifiedTimer(void);

	void update();
	void start();

	float fps() const { return m_fps; }
	int64 curFrame() const { return m_currentFrame; }

private:
	static const int FpsUpdateInterval = 30;
	static const int cacheSize = 30;
	int64 m_cache[cacheSize];
	int64 m_totalMsec;
	int64 m_nFpsUpdateFrame;
	int64 m_cursor;
	int64 m_startTime;
	int64 m_currentFrame;
	float m_fps;
	LPerformanceTimer m_timer;
};

#endif	// __LUNIFIEDTIMER_H__