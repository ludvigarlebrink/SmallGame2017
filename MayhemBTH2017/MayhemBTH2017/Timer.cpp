#include "Timer.h"



Timer::Timer()
{
	m_timeManager = TimeManager::Get();
}


Timer::~Timer()
{
}

void Timer::SetTimer(float time, bool start, bool resetWhenDone)
{
	m_setTime = time;
	m_hasStarted = start;
	m_resetWhenDone = resetWhenDone;
	
}

void Timer::StartTimer(float time)
{
	m_setTime = time;
	m_hasStarted = true;
}

void Timer::StartTimer()
{
	m_currentTime = 0.0f;
	m_hasStarted = true;
}

void Timer::Reset()
{
	m_currentTime = 0.0f;
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

float Timer::GetElapsed()
{
	return m_currentTime;
}

bool Timer::HasElapsed()
{
	if (!m_hasStarted)
	{
		return false;
	}

	if (m_currentTime > m_setTime)
	{
		m_currentTime = 0.0f;
		return true;
	}

	return false;
}


