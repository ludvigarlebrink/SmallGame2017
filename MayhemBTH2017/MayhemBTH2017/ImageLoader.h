#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__

#include <string>
#include <SDL.h>

#include "GLTexture.h"
#include "FileManager.h"

class ImageLoader
{
public:
	static GLTexture loadBMP(std::string filepath);
};


#endif

