#ifndef __THUMBNAIL_H__
#define __THUMBNAIL_H__

#include <vector>
#include <fstream>
#include <iostream>

#include <glew.h>

typedef union PixelInfo
{
	std::uint32_t Color;
	struct 
	{
		std::uint8_t R, G, B, A;
			 
	};
}*PPixelInfo;

class Thumbnail
{
public:
	Thumbnail(const char* FilePath);
	virtual ~Thumbnail();

	std::vector<std::uint8_t> GetPixels()const;
	std::uint32_t GetWidth()const;
	std::uint32_t GetHeight()const;
	bool HasAlphaChannel();

	void Import();

private:
	std::vector<std::uint8_t> m_pixels;
	std::uint32_t m_width, m_height, m_size, m_bitsPerPixel;
	//uint8_t * textureData;
	GLuint m_texture;
};

#endif