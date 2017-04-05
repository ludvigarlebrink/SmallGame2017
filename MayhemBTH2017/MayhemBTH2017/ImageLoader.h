#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__

#include "GLTexture.h"
#include "FileManager.h"

#include <glew.h>
#include "String.h" 
#include <string>
#include <SDL.h>
#include <iostream>
#include "Textures.h"
#include <cassert>

class ImageLoader
{
public:
	ImageLoader();
	virtual ~ImageLoader();
	void loadBMP(const std::string& filepath, Textures& texture);
	void Bind(unsigned int id);

	GLuint GetTex()const;

private:
private:
	GLuint m_texture;
	int test;
};


#endif
