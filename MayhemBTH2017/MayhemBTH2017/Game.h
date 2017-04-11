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
private:
	Mesh m_player;
	Level m_level;
public:
	void Update(Camera cam);
private:
public:

};

#endif __GAME_H__
