#ifndef __POSTPROCESSINGMANAGER_H__
#define __POSTPROCESSINGMANAGER_H__
#include <SDL.h>
#include <glew.h>
#include <iostream>

class PostProcessingManager
{
public:
	enum PostProcessingStates
	{
		NOTHING = 0,
		SHAKE = 1,
		CHAOS = 2,
	};

	PostProcessingManager();
	virtual ~PostProcessingManager();

	void StartUp();
	void ShutDown();

	static bool IsShaking();
	static bool IsChaos();
	static float GetTime();

	//::..HELPFUNCTIONS..:://
	static void StartTimer();
	static void Shake();
	static void Update(int state);

	static PostProcessingManager * Get();
private:
	static PostProcessingManager * m_instance;
	static float m_currentFrame;
	static float m_deltaTime;
	static float m_lastFrame;
	static float m_shakeTime;
	static bool m_shake;
	static bool m_chaos;
};

#endif // !__POSTPROCESSINGMANAGER_H__
