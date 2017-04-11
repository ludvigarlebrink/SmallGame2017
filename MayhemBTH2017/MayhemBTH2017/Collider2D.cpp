#include "Collider2D.h"



Collider2D::Collider2D()
{
	m_shader = new AShader("leo", false, false);
}


Collider2D::~Collider2D()
{
}

void Collider2D::SetBoxCollider(glm::vec2 min, glm::vec2 max)
{
	m_min = min;
	m_max = max;

	m_verts[0] = m_min;
	m_verts[1] = glm::vec2(m_max.x, m_min.y);
	m_verts[2] = glm::vec2(m_min.x, m_max.y);
	m_verts[3] = m_max;

	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(m_verts[0]), m_verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Collider2D::DrawCollider()
{
	m_shader->Bind();

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

