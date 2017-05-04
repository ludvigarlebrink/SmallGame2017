#include "thumbnail.h"



thumbnail::thumbnail(const char* FilePath)
{
	std::fstream file(FilePath, std::ios::binary);
	file.read(reinterpret_cast<char*>(textureData), sizeof(char) * (48 * 84));
	file.close();

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);


}


thumbnail::~thumbnail()
{
}

std::vector<std::uint8_t> thumbnail::GetPixels() const
{
	return m_pixels;
}

std::uint32_t thumbnail::GetWidth() const
{
	return m_width;
}

std::uint32_t thumbnail::GetHeight() const
{
	return m_height;
}

bool thumbnail::HasAlphaChannel()
{
	return m_bitsPerPixel == 32;
}
