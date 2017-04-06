#ifndef __TEXTURE_H__
#define __TEXTURE_H__


#include <glew.h>
#include <cstdint>


class Texture
{
public:
	Texture();
	virtual ~Texture();

	void LoadTexture(GLuint * textureData, GLsizei width, GLsizei height, GLuint numComponents);

	//::.. GET FUNCTIONS ..:://
	uint32_t GetHeight() const;
	uint32_t GetWidth() const;

	void Bind();

private:
	GLuint m_texture;
	uint32_t m_height;
	uint32_t m_width;


};


#endif // __TEXTURE_H__