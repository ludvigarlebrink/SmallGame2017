#ifndef __GUIIMAGE_H__
#define __GUIIMAGE_H__


#include "Mesh.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "glut.h"


#include <cstring>
#include <string>


class GUIImage
{
public:
	GUIImage();
	virtual ~GUIImage();

	void Render();

private:
	int m_Height, m_Width;
};


#endif