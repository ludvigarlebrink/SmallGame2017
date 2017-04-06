#include "TextureImporter.h"



TextureImporter::TextureImporter()
{
}

TextureImporter::~TextureImporter()
{
}

void TextureImporter::Import(const char * filepath)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(filepath, &width, &height, &numComponents, STBI_rgb_alpha);
	unsigned char* m_imageData = (unsigned char*)malloc(width * height * numComponents);

	//glGenTextures(1, &m_texture);
	//glBindTexture(GL_TEXTURE_2D, m_texture);
	//
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
	//	height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

