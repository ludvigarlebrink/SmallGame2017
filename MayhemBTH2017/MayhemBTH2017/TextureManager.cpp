#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


std::map<std::string, TextureManager::Texture> TextureManager::m_textureArray = { {"none", Texture() } };
TextureManager * TextureManager::m_instance = nullptr;

std::map<const char *, TextureManager::Texture> m_textureArray;


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
	}
}

void TextureManager::ShutDown()
{
	std::map<std::string, Texture>::iterator it;

	for (it = m_textureArray.begin(); it != m_textureArray.end(); it++)
	{
		TextureManager::FreeTexture(it->second.ID);
	}
}

TextureManager TextureManager::Get()
{
	return *m_instance;
}

TextureManager::Texture TextureManager::GetTexture(const char * name)
{
	return m_textureArray.at(name);
}

GLuint TextureManager::GetTextureID(const char * name)
{
	return m_textureArray[name].ID;
}

void TextureManager::AddTexture(const char * name, const char* filepath)
{
	SDL_Surface* img = SDL_LoadBMP(filepath);

	Texture texture;

	texture.ID = 0;

	texture.width = img->w;
	texture.height = img->h;

	glGenTextures(1, &texture.ID);
	glBindTexture(GL_TEXTURE_2D, texture.ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w,
		img->h, 0, GL_BGR, GL_UNSIGNED_BYTE, img->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_textureArray.insert(std::pair<const char *, Texture>(name, texture));

	SDL_FreeSurface(img);


}


GLuint TextureManager::Load(MrTexture * texture)
{
	GLuint id;

	int hej = texture->width;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width,
		texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete texture;

	return id;
}


void TextureManager::FreeTexture(GLuint id)
{
	glDeleteTextures(1, &id);
}

void TextureManager::FreeTexture(const char * name)
{
	glDeleteTextures(1, &m_textureArray.at(name).ID);
}

void TextureManager::DeleteTextureFromMap(const char * name)
{
	std::map<std::string, Texture>::iterator it;
	it = m_textureArray.find(name);
	m_textureArray.erase(it);
}

