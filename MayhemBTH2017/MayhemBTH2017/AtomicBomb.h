#ifndef __ATOMICBOMB_H__
#define __ATOMICBOMB_H__


#include "PrefabManager.h"
#include "VideoManager.h"
#include "Timer.h"
#include "Camera.h"
#include "PostProcessingManager.h"
#include "Background.h"


class AtomicBomb
{
public:
	AtomicBomb();
	virtual ~AtomicBomb();

	static void StartBombSequence();
	void Update(Camera &cam);


private:
	enum States
	{
		FLYING = 0,
		BOMB_DROPPED,
		BOMB_EXPLOSION
	};

	enum Uniforms
	{
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		T,
		NUM_UNIFORMS
	};

	uint32_t	m_currState;

	Prefab *	m_bomber;
	Prefab *	m_atomicBomb;

	static bool		m_sequenceStarted;

	GLuint m_shader;
	GLuint m_vao;
	GLuint m_buffer;
	GLuint m_uniforms[NUM_UNIFORMS];
	float m_t;
	bool m_shakeEffect;

};

#endif // !__ATOMICBOMB_H__