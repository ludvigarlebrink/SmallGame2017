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

	static void UpdateDeltaTime();

	static void ResetDeltaTime();

	//::.. GET FUNCTIONS ..:://
	static float GetDeltaTime();

	static TimeManager * Get();

	
private:
	static TimeManager * m_instance;

	static float m_lastFrame;
	static float m_deltaTime;
};


#endif