#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Load(){

	//Import current loaded level
	lvlImport.ImportLevel(m_level);

}