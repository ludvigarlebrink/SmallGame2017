#ifndef __POSTPROCESSING_H__
#define __POSTPROCESSING_H__
#include <SDL.h>
#include <glew.h>


class PostProcessing
{
public:
	PostProcessing();
	virtual ~PostProcessing();

	void StartUp();
	void ShutDown();

	bool* GetBools();

	//::..HELPFUNCTIONS..:://
	void StartTimer();
	void Shake();
	void Update(int state);

	static PostProcessing * Get();
private:
	static PostProcessing * m_instance;
	float currentFrame;
	float m_deltaTime = 0.0f;
	float m_lastFrame = 0.0f;
	GLfloat m_shakeTime = 0.0f;
	bool m_shake = false;
	bool m_chaos = false;
	bool m_bools[2] = { m_shake, m_chaos };
};

#endif // !__POSTPROCESSING_H__
