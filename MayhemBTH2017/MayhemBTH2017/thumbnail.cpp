#include "thumbnail.h"



Thumbnail::Thumbnail()
{
	
}


Thumbnail::~Thumbnail()
{
}

void Thumbnail::Import(const char * FilePath)
{
	std::ifstream file(".\\Assets\\Levels\\MUST.mrlevel", std::ios::binary);

	if (!file.is_open())
	{
		return;
	}

	///int size = m_height * 48 * 4;

	unsigned char * textureData = new unsigned char[m_height * m_widht * 4];
	file.ignore(sizeof(bool) * (84 * 48));
	file.ignore(sizeof(bool) * (84 * 48));
	file.ignore(sizeof(glm::vec2) * (84 * 48));
	file.read(reinterpret_cast<char*>(textureData), sizeof(unsigned char) * ((m_height * m_widht) * 4));

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_height, m_widht, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned int*)textureData);
	glBindTexture(GL_TEXTURE_2D, 0);

	file.close();
	delete textureData;
}



