#ifndef __TEXTUREIMPORTER_H__
#define __TEXTUREIMPORTER_H__

#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

#include <cstdint>
#include <cstdlib>
#include <glew.h>


class TextureImporter
{
public:
	TextureImporter();
	virtual ~TextureImporter();

	Texture& Import(const char* filepath);
};


#endif // __TEXTUREIMPORTER_H__