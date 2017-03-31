#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__

#include "GLTexture.h"
#include "FileManager.h"
#include "String.h"


#include <string>
#include <SDL.h>

class ImageLoader
{
public:
	static GLTexture loadBMP(String filepath);
};


#endif

