#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <glew.h>
#include "GUIQuad.h"

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	void Init(float x, float y, float width, float height);

	void Update(int mouse_x, int mouse_y);

	void Draw();

private:

	glm::vec4 m_BB;

	GLuint m_vboID;
	GUIQuad m_quad;


};





#endif // !__SPRITE_H__


