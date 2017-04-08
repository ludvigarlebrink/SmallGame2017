#ifndef __STARTMENU_H__
#define __STARTMENU_H__


#include "AMenu.h"
#include "MainMenu.h"


class StartMenu : public AMenu
{
public:
	StartMenu();
	virtual ~StartMenu();

private:

	MainMenu*	m_mainMenu;
};


#endif