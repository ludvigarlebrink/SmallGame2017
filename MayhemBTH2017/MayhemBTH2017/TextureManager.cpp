#include "TextureManager.h"



TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

GLuint TextureManager::GetTextureID(std::string name)
{
	return m_textureIDArray.at(name);
}

void TextureManager::AddTexture(std::string name, const char* filepath)
{
	SDL_Surface* img = SDL_LoadBMP(filepath);

	GLuint terxtureID = 0;

	glGenTextures(1, &terxtureID);
	glBindTexture(GL_TEXTURE_2D, terxtureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w,
		img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_textureIDArray.insert(std::pair<std::string, GLuint>(name, terxtureID));


}
