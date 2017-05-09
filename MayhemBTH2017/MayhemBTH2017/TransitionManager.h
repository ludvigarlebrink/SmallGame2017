#ifndef __TRANSITIONMANAGER_H__
#define __TRANSITIONMANAGER_H__


#include "ShaderManager.h"
#include "TimeManager.h"

#include <glm.hpp>


class TransitionManager
{
public:
	TransitionManager();
	virtual ~TransitionManager();

	void StartUp();
	void ShutDown();

	static void Update();

	static void StartFadingOut();
	static void StartFadingIn();
	 
	static bool GetIsFadingIn();
	static bool GetIsFadingOut();
	static bool GetIsBlack();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	enum Uniforms
	{
		T,
		NUM_UNIFORMS
	};

	static TransitionManager * m_instance;

	static GLuint m_shader;
	static GLuint m_vao;
	static GLuint m_buffer;
	static GLuint m_uniforms[NUM_UNIFORMS];

	static GLfloat m_t;

	static bool m_isFadingIn;
	static bool m_isFadingOut;
	static bool m_isBlack;



};


#endif // !__TRANSITIONMANAGER_H__