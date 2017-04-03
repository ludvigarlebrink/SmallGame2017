#include "Sprite.h"



Sprite::Sprite()
{
	m_vboID = 0;
}


Sprite::~Sprite()
{
}

void Sprite::init(float x, float y, float width, float height)
{

	m_quad.m_arr[0].m_position = glm::vec2(x, y);

	m_quad.m_arr[0].m_position = glm::vec2(x + width, y);

	m_quad.m_arr[0].m_position = glm::vec2(x, y + height);

	m_quad.m_arr[0].m_position = glm::vec2(x + width, y + height);


	if (m_vboID == 0)
	{
		glGenBuffers(1, &m_vboID);
	}
	//sdf

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(m_quad.m_arr[0]), &m_quad.m_arr[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(2 * sizeof(GL_FLOAT)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
