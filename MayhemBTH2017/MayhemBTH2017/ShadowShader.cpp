#include "ShadowShader.h"

//::.. CONSTRUCTORS ..:://

ShadowShader::ShadowShader()
{
}


ShadowShader::~ShadowShader()
{
}


//::.. HELP FUNCTIONS ..:://

void ShadowShader::Init()
{
	m_shader.Init("//TEMP//", false, false);
	glm::mat4 lightProjection, lightView;
	GLfloat nearPlane = 1.0f, farPlane = 75.5f;
	lightProjection = glm::ortho(8.0f, 8.0f, -30.0f, 30.0f, nearPlane, farPlane);
	lightView = glm::lookAt(glm::vec3(8, 8, -30), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	m_lightSpaceMatrix = lightProjection * lightView;
	m_LocLightSpaceMatrix = glGetUniformLocation(m_shader.GetProgramID(), "LightSpaceMatrix");
	m_shader.Bind();
	glUniformMatrix4fv(m_LocLightSpaceMatrix, 1, GL_FALSE, &m_lightSpaceMatrix[0][0]);
	glUniform1f(glGetUniformLocation(m_shader.GetProgramID(), "nearPlane"),nearPlane);
	glUniform1f(glGetUniformLocation(m_shader.GetProgramID(), "farPlane"), farPlane);


}
