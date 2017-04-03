#ifndef __GUIQUAD_H__
#define __GUIQUAD_H__

#include "Mesh.h"
#include "GLTexture.h"

struct GUIQuad
{

	GLTexture m_texture;

	float depth;

	Vertex m_bottom_left;
	Vertex m_bottom_right;
	Vertex m_top_left;
	Vertex m_top_right;

};

#endif // !__GUIQUAD_H__
