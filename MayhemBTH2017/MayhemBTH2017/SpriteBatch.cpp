#include "SpriteBatch.h"




SpriteBatch::SpriteBatch()
{

}


SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::init()
{

}

void SpriteBatch::begin()
{

}

void SpriteBatch::end()
{

}

void SpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth)
{

	
}

void SpriteBatch::renderBatch()
{

}

void SpriteBatch::createVertexArray()
{

	if (m_vbo == 0)
	{
		glGenVertexArrays(1, &m_vbo);
	}

	if (m_vao == 0)
	{
		glGenVertexArrays(1, &m_vao);
	}



}
