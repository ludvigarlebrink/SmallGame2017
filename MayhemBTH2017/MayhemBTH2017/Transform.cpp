#include "Transform.h"



//::.. CONSTRUCTORS ..:://
Transform::Transform()
	: m_position(glm::vec3(0)), m_rotation(glm::vec3(0)), m_scale(glm::vec3(0))
{

}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
	: m_position(pos), m_rotation(rot), m_scale(scale)
{
}

Transform::Transform(const Transform & object)
{
	// Self assignment check.
	if (&object == this)
	{
		return;
	}

	// Deep copy values.
	m_position = object.m_position;
	m_rotation = object.m_rotation;
	m_scale = object.m_scale;
}

Transform::~Transform()
{
	// Do nothing...
}


//::.. OPERATOR OVERLOADING ..:://
void Transform::operator=(const Transform & object)
{
	// Self assignment check.
	if (&object == this)
	{
		return;
	}

	// Deep copy values.
	m_position = object.m_position;
	m_rotation = object.m_rotation;
	m_scale = object.m_scale;
}


//::.. MODIFY FUNCTIONS ..:://
void Transform::Move()
{
	// TODO
}

void Transform::Rotate()
{
	// TODO
}


//::.. SET FUNCTIONS ..:://
void Transform::SetPosition(glm::vec3 pos)
{
	m_position = pos;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void Transform::SetRotation(glm::vec3 rot)
{
	m_rotation = rot;
}

void Transform::SetRotation(float x, float y, float z)
{
	m_rotation = glm::vec3(x, y, z);
}

void Transform::SetScale(glm::vec3 scale)
{
	m_scale = scale;
}

void Transform::SetScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}


//::.. GET FUNCTIONS ..:://
glm::vec3 Transform::GetPosition()
{
	return m_position;
}

glm::vec3 Transform::GetRotation()
{
	return m_rotation;
}

glm::vec3 Transform::GetScale()
{
	return m_scale;
}

glm::mat4 Transform::GetModelMatrix()
{
	glm::mat4 posMat = glm::translate(m_position);

	glm::mat4 xRot = glm::rotate(m_rotation.x, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 yRot = glm::rotate(m_rotation.y, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 zRot = glm::rotate(m_rotation.z, glm::vec3(0.0, 0.0, 1.0));

	glm::mat4 rotMat = zRot * yRot * xRot;

	glm::mat4 scaleMat = glm::scale(m_scale);

	return posMat * rotMat * scaleMat;
}