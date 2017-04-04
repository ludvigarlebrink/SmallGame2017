#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__

#include "GLTexture.h"
#include "FileManager.h"


#include "String.h" 
#include <string>
#include <SDL.h>
#include <iostream>

class ImageLoader
{
public:
	static GLTexture loadBMP(const std::string& filepath);
};


#endif

