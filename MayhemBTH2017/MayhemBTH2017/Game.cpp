#include "Game.h"



Game::Game()
{
	LevelImporter imp;
	imp.ImportLevel(m_level);
}


Game::~Game()
{
}

void Game::Update(Camera cam){

	
	m_level.Render(cam);
}