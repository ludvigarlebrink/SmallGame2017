#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include <glew.h>


class Textures
{
public:
	Textures();
	virtual ~Textures();

	void createTexture(GLuint id);

	//::.. GET FUNCTIONS ..:://
	GLuint GetId()const;
	GLuint GetHeight()const;
	GLuint GetWidth()const;

	//::.. SET FUNCTIONS ..:://
	void SetHeight(GLuint y);
	void SetWidth(GLuint x);


private:
	GLuint m_id;
	GLuint m_height;
	GLuint m_width;
};

#endif // !__TEXTURE_H__
