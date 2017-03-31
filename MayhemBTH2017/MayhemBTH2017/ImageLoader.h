#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__

#include "GLTexture.h"

#include <string>
#include "PicoPNG.h"

class ImageLoader
{
public:
	GLTexture loadPNG(std::string filepath);
};


#endif

