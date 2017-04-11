#ifndef __GAME_H__
#define __GAME_H__

#include "Level.h"
#include "LevelEditor.h"
#include "Mesh.h"


class Game
{
public:
	Game();
	virtual ~Game();
	void Update(Camera cam);
	void Render();
private:
private:
	Mesh m_player;
	Level m_level;
	Vertex3D m_vertices[6];
public:
private:
public:

};

#endif __GAME_H__
