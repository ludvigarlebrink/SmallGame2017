#include "StartMenu.h"
#include <iostream>


StartMenu::StartMenu()
{
	m_mainMenu = new MainMenu;
	m_mainMenu->SetIsActive(false);
	AddChild(m_mainMenu);
	std::cout << "START MENU" << std::endl;
}


StartMenu::~StartMenu()
{
}
