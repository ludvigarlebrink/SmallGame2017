#include "StartMenu.h"
#include <iostream>


StartMenu::StartMenu()
{
	m_mainMenu = new MainMenu;
	m_mainMenu->SetIsActive(false);
	m_mainMenu->SetParent(this);
	AddChild(m_mainMenu);
	std::cout << "START MENU" << std::endl;
}


StartMenu::~StartMenu()
{
}
