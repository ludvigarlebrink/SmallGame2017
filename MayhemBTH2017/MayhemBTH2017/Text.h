#ifndef __TEXT_H__
#define __TEXT_H__


#include "Mesh.h"

#include <SDL_ttf.h>


class Text
{
public:

	//::.. DUMMY CONSTRUCTORS ..:://
	Text();
	virtual ~Text();

	//::.. HELP FUNCTIONS ..:://
	void Init();
	void Render();

private:
	Vertex3D verts[6];
	Mesh m_mesh;
};


#endif // __TEXT_H__