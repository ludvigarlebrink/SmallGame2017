#ifndef __TEXTURE_H__
#define __TEXTURE_H__


#include <glew.h>
#include <cstdint>


class Texture
{
public:
	Texture();
	virtual ~Texture();

	void LoadTexture(uint32_t id);

	//::.. GET FUNCTIONS ..:://
	GLuint GetId() const;
	GLuint GetHeight() const;
	GLuint GetWidth() const;

	//::.. SET FUNCTIONS ..:://
	void SetHeight(GLuint y);
	void SetWidth(GLuint x);

private:
	GLuint m_id;
	GLuint m_height;
	GLuint m_width;


};


#endif // __TEXTURE_H__