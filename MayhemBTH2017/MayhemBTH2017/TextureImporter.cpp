#include "TextureImporter.h"
#include <stb_image.h>


#include <iostream>

TextureImporter::TextureImporter()
{
}

TextureImporter::~TextureImporter()
{
}

Texture& TextureImporter::Import(const char * filepath)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(filepath, &width, &height, &numComponents, STBI_rgb_alpha);
	unsigned char length = sizeof(imageData) / sizeof(*imageData);
	GLuint * imageData2 = (GLuint*)malloc(sizeof(GLuint) * length);

	std::cout << length << std::endl;

//	for (size_t i = 0; i < length; i++)
//	{
//		imageData2[i] = static_cast<GLuint>(imageData[i]);
//	}
//
//	stbi_image_free(imageData);
//
	Texture texture;

	texture.LoadTexture((GLuint*)imageData, width, height, numComponents);

	return texture;
}

