#pragma once


#include <map>
#include <string>

#include "GLTexture.h"
#include "String.h"


class TextureCache
{
public:
	TextureCache();
	virtual ~TextureCache();

	GLTexture GetTexture(String texturePath);

private:
	std::map<std::string, uint32_t> m_textureMap;


};

