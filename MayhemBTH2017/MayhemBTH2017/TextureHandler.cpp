#include "TextureHandler.h"


#include <stb_image.h>




TextureHandler::TextureHandler()
{
}

TextureHandler::~TextureHandler()
{
}

Texture* TextureHandler::Import(const char * filepath)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(filepath, &width, &height, &numComponents, STBI_rgb_alpha);
	
	Texture* texture = new Texture;

	texture->LoadTexture((GLuint*)imageData, width, height, numComponents);
	stbi_image_free(imageData);

	return texture;
}

