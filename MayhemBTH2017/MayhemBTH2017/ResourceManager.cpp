#include "ResourceManager.h"

TextureCache ResourceManager::m_textureCache;

GLTexture ResourceManager::GetTexture(String texturePath)
{
	return m_textureCache.GetTexture(texturePath);
}
