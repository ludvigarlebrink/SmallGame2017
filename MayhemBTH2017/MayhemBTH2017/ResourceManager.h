#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__


#include "TextureCache.h"


class ResourceManager
{
public:
	static GLTexture GetTexture(std::string texturePath);

private:
	static TextureCache m_textureCache;

};

#endif