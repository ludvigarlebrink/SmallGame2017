#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <glew.h>
#include "GUIQuad.h"

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void init(float x, float y, float width, float height);

	void draw();

private:
	GLuint m_vboID;
	GUIQuad m_quad;


};





#endif // !__SPRITE_H__


