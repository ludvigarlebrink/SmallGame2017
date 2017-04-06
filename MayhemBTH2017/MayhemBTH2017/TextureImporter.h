#ifndef __TEXTUREIMPORTER_H__
#define __TEXTUREIMPORTER_H__
#define STB_IMAGE_IMPLEMENTATION

#include <cstdint>
#include <cstdlib>
#include <glew.h>
#include <stb_image.h>


class TextureImporter
{
public:
	TextureImporter();
	virtual ~TextureImporter();

	void Import(const char* filepath);
};


#endif // __TEXTUREIMPORTER_H__