#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__


#include "TextureCache.h"
#include "String.h"


class ResourceManager
{
public:
	static GLTexture GetTexture(String texturePath);

private:
	static TextureCache m_textureCache;

};

#endif