#include "TextureCache.h"



TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::GetTexture(std::string texturePath)
{
	// Find the texture.
	auto iterator = m_textureMap.find(texturePath);

	if (iterator == m_textureMap.end())
	{
		// Load the texture.
		GLTexture tempTexture = ImageLoader::loadBMP(texturePath);

		std::pair<std::string, GLTexture> tempPair(texturePath, tempTexture);

		// Insert in map.
		m_textureMap.insert(tempPair);

		return tempTexture;

	}

	return iterator->second;

}
