#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__


#include <SDL.h>
#include <cstdint>


class TimeManager
{
public:
	TimeManager();
	virtual ~TimeManager();

	void StartUp();
	void ShutDown();

	void UpdateDeltaTime();

	float GetDeltaTime();

	static TimeManager * Get();

private:
	static TimeManager * m_instance;

	float m_lastFrame;
	float m_deltaTime;
};


#endif