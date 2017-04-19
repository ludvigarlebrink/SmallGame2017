#ifndef __TIMER_H__
#define __TIMER_H__


#include "TimeManager.h"


class Timer
{
public:
	Timer();
	virtual ~Timer();

	bool Update();
	
	//::.. GET FUNCTIONS ..:://
	float GetElapsed();

	//::.. SET FUNCTIONS ..:://
	void SetTimer(float time, bool start = false, bool resetWhenDone = false);
	void StartTimer(float time);
	void StartTimer();

	void Reset();
	bool HasElapsed();

private:
	TimeManager * m_timeManager;

	bool m_resetWhenDone;
	bool m_hasStarted;

	float m_currentTime;
	float m_setTime;
};


#endif