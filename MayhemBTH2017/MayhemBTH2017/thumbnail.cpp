#include "thumbnail.h"



Thumbnail::Thumbnail()
{
	
}


Thumbnail::~Thumbnail()
{
}

void Thumbnail::Import(const char * FilePath)
{
	std::ifstream file(".\\Assets\\Levels\\NewFormat.mrlevel", std::ios::binary);

	if (!file.is_open())
	{
		return;
	}

	int size = 84 * 48 * 4;

	unsigned char * textureData = new unsigned char[84 * 48 * 4];
	file.ignore(sizeof(bool) * (84 * 48));
	file.ignore(sizeof(bool) * (84 * 48));
	file.ignore(sizeof(glm::vec2) * (84 * 48));
	for (size_t i = 0; i < 84 * 48 * 4; i++)
	{
		file.read(reinterpret_cast<char*>(&textureData[i]), sizeof(unsigned char));
	}


	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 84, 48, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned int*)textureData);
	glBindTexture(GL_TEXTURE_2D, 0);

	file.close();
	delete textureData;
}

std::vector<std::uint8_t> Thumbnail::GetPixels() const
{
	return m_pixels;
}

std::uint32_t Thumbnail::GetWidth() const
{
	return m_width;
}

std::uint32_t Thumbnail::GetHeight() const
{
	return m_height;
}

bool Thumbnail::HasAlphaChannel()
{
	return m_bitsPerPixel == 32;
}



