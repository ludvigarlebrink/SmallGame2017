#include "Camera.h"

#include <iostream>

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

void Camera::SetRotation(float x, float y)
{
	glm::vec3 direction;
	direction.x = sin(glm::radians(x))*cos(glm::radians(y));
	direction.y = sin(glm::radians(y));
	direction.z = cos(glm::radians(x))*cos(glm::radians(y));
	m_front = glm::normalize(direction);
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

glm::vec3 Camera::GetPosition()
{
	return m_pos;
}


//::.. HELP FUNCTIONS ..:://
void Camera::Init()
{
	m_pos = glm::vec3(8, 8, -24);
	m_front = glm::vec3(0, 0, 1);
	m_up = glm::vec3(0, 1, 0);

	
	m_perspective = glm::perspective(70.0f, 1280.0f/ 720.0f, 10.0f, 200.0f);
}