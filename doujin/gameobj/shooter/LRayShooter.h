#ifndef _TLASERSHOOTER_H_
#define _TLASERSHOOTER_H_
#pragma once
#include "LShooter.h"

class LRayShooter : public LShooter
{
	enum State
	{
		None,
		Warning,
		Shooting,
	};
public:
	LRayShooter(IGameObject* pParent);
	virtual ~LRayShooter(void);

public:
	virtual void Update();
	virtual void Draw(LPainter& painter);

public:
	LRayShooter& setDirection(Degree deg)
	{
		m_fireDegree = deg;
		m_warningLine.InitFromPolar(600, deg);
	}
	void setWarningTime(int time)		{ m_warningTime = time; }
	void setDurationTime(int time)		{ m_durationTime = time; }
	void setLoop(bool loop)				{ m_bLoop = loop; }
	void setWidthExtRange(float wid)	{ m_widthExt = wid; }
	void setLengthExtRange(float len)	{ m_lengthExt = len; }
	void setTurnFlag(bool f)			{ m_bTurnFlag = f; }

protected:
	void ChangeState(State targetState);
	void EntryShootingState();
	void EntryWarningState();
	void ExecShooting();
	void ExecWarning();

private:
	bool m_bLoop;
	bool m_bTurnFlag;
	int m_warningTime;	// 预警时间
	int m_durationTime;	// 持续时间
	float m_widthExt;		// 宽度倍率
	float m_lengthExt;		// 长度倍率
	State m_currState;

	Vector2 m_warningLine;
	int m_counter;
};
#endif