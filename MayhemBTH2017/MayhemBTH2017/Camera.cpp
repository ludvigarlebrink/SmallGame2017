#include "Camera.h"

//::.. DUMMY CONSTRUCTORS ..:://

Camera::Camera()
{
}


Camera::~Camera()
{
}

//::.. GET FUNCTIONS ..:://

glm::mat4 Camera::GetMvp()const
{
	return m_mvp;
}

glm::mat4 Camera::GetModel()const
{
	return m_model;
}

glm::mat4 Camera::GetProjection()const
{
	return m_projection;
}

glm::mat4 Camera::GetView()const
{
	return m_view;
}

glm::vec3 Camera::GetCameraPos()const
{
	//TBA
}

//::.. SET FUNCTIONS ..:://

void Camera::SetEye(glm::vec3 eye)
{
	m_eye = eye;
}

void Camera::SetCenter(glm::vec3 center)
{
	m_center = center;
}

void Camera::SetUp(glm::vec3 up)
{
	m_up = up;
}


//::.. HELPER FUNCTIONS ..:://
void Camera::Init()
{
	m_eye = glm::vec3(1);
	m_center = glm::vec3(1);
	m_up = glm::vec3(1);


	m_view = glm::lookAt(m_eye, m_center, m_up);
	m_projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600,
		0.1f, 100.0f);

	m_model = glm::mat4(1);
	m_mvp = m_projection * m_view * m_model;

}

void Camera::Update()
{

	m_view = glm::lookAt(m_eye, m_center, m_up);
	m_projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600,
		0.1f, 100.0f);

	m_model = glm::mat4(1);
	m_mvp = m_projection * m_view * m_model;
}