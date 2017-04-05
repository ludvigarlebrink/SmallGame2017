#include "ImageLoader.h"

ImageLoader::ImageLoader()
{

}

ImageLoader::~ImageLoader()
{
	//glDeleteTextures(1, &m_texture);
}


void ImageLoader::loadBMP(const std::string& filepath, Textures& texture)
{
	SDL_Surface *img = SDL_LoadBMP(filepath.c_str());
	texture.SetHeight(img->h);
	texture.SetWidth(img->w);
	if (img == NULL)
	{
		std::cout << "BMP Error\n";
	}

	
	if (!img) 
	{
		// SDL_GetError();
	}
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_BGR, GL_UNSIGNED_BYTE, img->pixels);
	//glGenerateMipmap(GL_TEXTURE_2D);

	SDL_free(img);

	//glBindTexture(GL_TEXTURE_2D, 0);
	//return texture;
}


void ImageLoader::Bind(unsigned int id)
{
	assert(id >= 0 && id <= 31);
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, m_texture);


}
