#include "ShadowShader.h"

//::.. CONSTRUCTORS ..:://

ShadowShader::ShadowShader()
{
}


ShadowShader::~ShadowShader()
{
}


//::.. HELP FUNCTIONS ..:://

void ShadowShader::Init(std::string shaderName)
{
	m_shader.Init(".\\Assets\\GLSL\\" + shaderName, false, false);




}

void ShadowShader::UpdateShadows(Camera camera, Transform trans)
{
	const int SIZE_X = 84;

	const int SIZE_Y = 48;

	Camera cam;
	cam.SetPosition(glm::vec3(((SIZE_X / 2)), ((SIZE_Y / 2)), -51.2f));
	//cam.SetPosition(glm::vec3(((SIZE_X / 2)), ((SIZE_Y / 2)), -30.2f));
	//float temp = 35;
	//float temp2 = 22;
	m_shader.Bind();//fel
	m_shader.Update(trans, camera);
	glm::mat4 lightProjection, lightView;
	GLfloat nearPlane = 1.0f, farPlane = 750.5f;
	//lightProjection = glm::ortho(-temp - (SIZE_X / 2), temp - (SIZE_X / 2), -temp2 + ((SIZE_Y / 2)), temp2 + ((SIZE_Y / 2)), nearPlane, farPlane);
	lightProjection = glm::ortho(-(SIZE_X / 2.0f), (SIZE_X / 2.0f), (-(SIZE_Y / 2.0f)), ((SIZE_Y / 2.0f)), nearPlane, farPlane);
	//lightView = glm::lookAt(glm::vec3(200, 0, -30), (glm::vec3(0, 0, 1) + glm::vec3(8, 8, -24)), glm::vec3(0, 1, 0));

	lightView = cam.GetViewShadow();
	m_lightSpaceMatrix = lightProjection * lightView;
	GLint LocLightSpaceMatrix = glGetUniformLocation(m_shader.GetProgramID(), "LightSpaceMatrix");
	glUniformMatrix4fv(LocLightSpaceMatrix, 1, GL_FALSE, &m_lightSpaceMatrix[0][0]);
	glUniform1f(glGetUniformLocation(m_shader.GetProgramID(), "nearPlane"),nearPlane);
	glUniform1f(glGetUniformLocation(m_shader.GetProgramID(), "farPlane"), farPlane);
}
