#ifndef __POSTPROCESSING_H__
#define __POSTPROCESSING_H__
#include <SDL.h>
#include <glew.h>


class PostProcessing
{
public:
	enum PostProcessingStates
	{
		NOTHING = 0,
		SHAKE = 1,
		CHAOS = 2,
	};

	PostProcessing();
	virtual ~PostProcessing();

	void StartUp();
	void ShutDown();

	static bool IsShaking();
	static bool IsChaos();

	//::..HELPFUNCTIONS..:://
	static void StartTimer();
	static void Shake();
	static void Update(int state);

	static PostProcessing * Get();
private:
	static PostProcessing * m_instance;
	static float m_currentFrame;
	static float m_deltaTime;
	static float m_lastFrame;
	static float m_shakeTime;
	static bool m_shake;
	static bool m_chaos;
};

#endif // !__POSTPROCESSING_H__
