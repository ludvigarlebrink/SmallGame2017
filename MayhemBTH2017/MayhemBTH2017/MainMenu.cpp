#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu()
{
	AddChild(GameState::LEVEL_EDITOR);
	std::cout << "MAIN MENU" << std::endl;
}


MainMenu::~MainMenu()
{

}
