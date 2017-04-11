#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu()
{
	AddChild(GameState::GAME, "Play");
	AddChild(GameState::LEVEL_EDITOR, "Create");
	AddChild(GameState::LEVEL_EDITOR, "Options");
	AddChild(GameState::LEVEL_EDITOR, "Exit");
}


MainMenu::~MainMenu()
{

}
