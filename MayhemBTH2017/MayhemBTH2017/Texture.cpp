#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}


void Texture::LoadTexture(uint32_t id)
{
	m_id = id;
}

//::.. GET FUNCTIONS ..:://
GLuint Texture::GetId()const
{
	return m_id;
}

GLuint Texture::GetHeight()const
{
	return m_height;
}

GLuint Texture::GetWidth()const
{
	return m_width;

}


//::.. SET FUNCTIONS ..:://
void Texture::SetHeight(GLuint y)
{
	m_height = y;
}

void Texture::SetWidth(GLuint x)
{
	m_width = x;
}