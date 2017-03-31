#include "ResourceManager.h"

TextureCache ResourceManager::m_textureCache;

GLTexture ResourceManager::GetTexture(std::string texturePath)
{
	return m_textureCache.GetTexture(texturePath);
}
