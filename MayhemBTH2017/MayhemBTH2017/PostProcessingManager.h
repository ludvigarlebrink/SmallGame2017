#ifndef __POSTPROCESSINGMANAGER_H__
#define __POSTPROCESSINGMANAGER_H__


#include "TimeManager.h"


#include <SDL.h>
#include <glew.h>


class PostProcessingManager
{
public:
	enum PostProcessingStates
	{
		NOTHING = 0,
		SHAKE = 1,
		CHAOS = 2,
		ATOMIC = 4
	};

	PostProcessingManager();
	virtual ~PostProcessingManager();

	void StartUp();
	void ShutDown();

	static bool IsShaking();
	static bool IsChaos();
	static bool IsAtomic();
	static float GetShakingTime();
	static float GetChaosTime();
	static float GetAtmoicTime();

	static void Shake();
	static void Update();
	static void SetState(int state);

	static PostProcessingManager * Get();
private:
	static PostProcessingManager * m_instance;
	static float m_currentFrame;
	static float m_deltaTime;
	static float m_lastFrame;
	static float m_shakeTime;
	static float m_chaosTime;
	static float m_atomicTime;

	static bool m_shake;
	static bool m_chaos;
	static bool m_atomic;
};
#endif // !__POSTPROCESSINGMANAGER_H__
