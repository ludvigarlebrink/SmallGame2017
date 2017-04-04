#include "Camera.h"

//::.. DUMMY CONSTRUCTORS ..:://

Camera::Camera()
{
	Init();
}


Camera::~Camera()
{
}


//::.. SET FUNCTIONS ..:://
void Camera::SetPosition(glm::vec3 pos)
{
	m_pos = pos;
}


//::.. GET FUNCTIONS ..:://
glm::mat4 Camera::GetView()
{
	return glm::lookAt(m_pos, m_pos + m_front, m_up);;
}

glm::mat4 Camera::GetProjection()
{
	return m_perspective;
}


//::.. HELP FUNCTIONS ..:://
void Camera::Init()
{
	m_pos = glm::vec3(0, 0, 0);
	m_front = glm::vec3(0, 0, 1);
	m_up = glm::vec3(0, 1, 0);

	m_perspective = glm::perspective(70.0f, 1280.0f/ 720.0f, 0.03f, 1000.0f);
}