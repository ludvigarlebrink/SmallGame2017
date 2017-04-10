#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu()
{
	AddChild(GameState::LEVEL_EDITOR, "Play");
	AddChild(GameState::LEVEL_EDITOR, "Create");
	AddChild(GameState::LEVEL_EDITOR, "Options");
	AddChild(GameState::LEVEL_EDITOR, "Exit");
}


MainMenu::~MainMenu()
{

}
