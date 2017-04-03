#ifndef __GUIQUAD_H__
#define __GUIQUAD_H__


#include "Mesh.h"
#include "GLTexture.h"


struct GUIVertex
{

	glm::vec2 m_position;
	glm::vec2 m_UV;

};


struct GUIQuad
{

	GLTexture m_texture;

	float depth;

	GUIVertex m_arr[4];

};

#endif // !__GUIQUAD_H__
