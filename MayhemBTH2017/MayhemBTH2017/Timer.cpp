#include "Timer.h"



Timer::Timer()
{
	m_timeManager = TimeManager::Get();
}


Timer::~Timer()
{
}

void Timer::SetTimer(float time, bool start, bool resetWhenDonw)
{
	m_setTime = time;
	m_hasStarted = true;
	m_resetWhenDone = resetWhenDonw;
	
}

void Timer::StartTimer()
{
	m_currentTime = 0.0f;
	m_hasStarted = true;
}

void Timer::Reset()
{

}

bool Timer::Update()
{
	if (!m_hasStarted)
	{
		return false;
	}

	m_currentTime += m_timeManager->GetDeltaTime();

	if (m_currentTime > m_setTime)
	{
		m_currentTime = 0.0f;
		return true;
	}

	return false;
}

bool Timer::HasElapsed()
{
	return false;
}


