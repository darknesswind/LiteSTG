#ifndef __LUNIFIEDTIMER_H__
#define __LUNIFIEDTIMER_H__
#pragma once
#include <QElapsedTimer>

// 计算Fps与帧率控制
class LUnifiedTimer
{
public:
	LUnifiedTimer(void);
	~LUnifiedTimer(void);

	void update();
	void start();	
	float fps() const { return m_fps; }
	qint64 curFrame() const { return m_currentFrame; }

private:
	static const int FpsUpdateInterval = 30;
	static const int cacheSize = 30;
	qint64 m_cache[cacheSize];
	qint64 m_totalMsec;
	qint64 m_nFpsUpdateFrame;
	qint64 m_cursor;
	qint64 m_startTime;
	qint64 m_currentFrame;
	float m_fps;
	QElapsedTimer m_timer;
};

#endif	// __LUNIFIEDTIMER_H__