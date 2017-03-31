#include "ImageLoader.h"

GLTexture ImageLoader::loadBMP(std::string filepath)
{
	GLTexture texture = {};

	unsigned long width, height;

	SDL_Surface* img = SDL_LoadBMP(filepath.c_str());
	texture.width = img->w;
	texture.height = img->h;
	
	if (!img) 
	{
		// SDL_GetError();
	}

	glGenTextures(1, &texture.ID);

	glBindTexture(GL_TEXTURE_2D, texture.ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_free(img);

	return texture;
}
