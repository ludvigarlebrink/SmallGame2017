#include "ResourceManager.h"

GLTexture ResourceManager::GetTexture(std::string texturePath)
{
	return m_textureCache.GetTexture(texturePath);
}
