#pragma once


#include <map>
#include <string>

#include "GLTexture.h"
#include "ImageLoader.h"


class TextureCache
{
public:
	TextureCache();
	virtual ~TextureCache();

	GLTexture GetTexture(std::string texturePath);

private:
	std::map<std::string, GLTexture> m_textureMap;


};

