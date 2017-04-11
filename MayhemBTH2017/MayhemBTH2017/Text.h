#ifndef __TEXT_H__
#define __TEXT_H__


#include "Mesh.h"


#include <SDL_ttf.h>


class Text
{
public:
	Text();
	virtual ~Text();

	void Init();
	void Render();

private:
	Vertex verts[6];
	Mesh m_mesh;
};


#endif // __TEXT_H__