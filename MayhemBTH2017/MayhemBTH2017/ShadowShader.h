#ifndef __SHADOWSHADER_H__
#define __SHADOWSHADER_H__

#include "AShader.h"

class ShadowShader
{
public:
	//::.. CONSTRUCTORS ..:://
	ShadowShader();
	virtual ~ShadowShader();

	//::.. HELP FUNCTIONS ..:://
	void Init();

	void UpdateShadows();

private:

private:
	AShader m_shader;

	glm::mat4 m_lightSpaceMatrix;
	GLuint m_LocLightSpaceMatrix;
};

#endif // !__SHADOWSHADER_H__
