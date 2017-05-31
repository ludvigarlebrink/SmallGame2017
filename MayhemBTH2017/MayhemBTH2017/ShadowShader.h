#ifndef __SHADOWSHADER_H__
#define __SHADOWSHADER_H__

#include "AShader.h"
#include "Camera.h"


class ShadowShader
{
public:
	//::.. CONSTRUCTORS ..:://
	ShadowShader();
	virtual ~ShadowShader();

	//::.. HELP FUNCTIONS ..:://
	void Init(std::string shaderName);

	void UpdateShadows(Camera camera, Transform trans);

private:

private:
	AShader m_shader;

	glm::mat4 m_lightSpaceMatrix;
	GLuint m_LocLightSpaceMatrix;
};

#endif // !__SHADOWSHADER_H__
