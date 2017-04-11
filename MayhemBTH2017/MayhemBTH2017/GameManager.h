#ifndef __GAMEMANAGER_H__
#define __GAMERMANAGER_H__

#include "Level.h"
#include "LevelEditor.h"
#include "Mesh.h"

class GameManager
{
public:
	GameManager();
	virtual ~GameManager();
private:
	Mesh m_player;
	LevelImporter lvlImport;
	Level m_level;
public:
	void Load();
private:
public:

};

#endif __GAMEMANAGER_H__
