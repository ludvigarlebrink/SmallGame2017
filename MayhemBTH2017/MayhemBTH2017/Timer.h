#ifndef __TIMER_H__
#define __TIMER_H__


#include "TimeManager.h"


class Timer
{
public:
	Timer();
	virtual ~Timer();

	void SetTimer(float time, bool start = false, bool resetWhenDonw = false);
	void StartTimer();
	void Reset();
	bool Update();
	bool HasElapsed();

private:
	TimeManager * m_timeManager;

	bool m_resetWhenDone;
	bool m_hasStarted;

	float m_currentTime;
	float m_setTime;
};


#endif