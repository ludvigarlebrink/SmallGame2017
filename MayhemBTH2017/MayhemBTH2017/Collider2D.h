#pragma once

#include "AShader.h"

#include <glm.hpp>
#include <box2d.h>

#include <glew.h>

class Collider2D
{
public:
	Collider2D();
	virtual ~Collider2D();

	void SetBoxCollider(glm::vec2 min, glm::vec2 max);

	void DrawCollider();

private:
	glm::vec2	m_min;
	glm::vec2	m_max;
	glm::vec2	m_verts[4];

	GLuint		m_bufferID;
	AShader*	m_shader;
};

