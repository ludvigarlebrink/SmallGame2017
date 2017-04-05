#include "Textures.h"



Textures::Textures()
{
}


Textures::~Textures()
{
}


void Textures::createTexture(GLuint id)
{
	m_id = id;
}

//::.. GET FUNCTIONS ..:://

GLuint Textures::GetId()const
{
	return m_id;
}

GLuint Textures::GetHeight()const
{
	return m_height;
}

GLuint Textures::GetWidth()const
{
	return m_width;

}

//::.. SET FUNCTIONS ..:://

void Textures::SetHeight(GLuint y)
{
	m_height = y;
}

void Textures::SetWidth(GLuint x)
{
	m_width = x;
}