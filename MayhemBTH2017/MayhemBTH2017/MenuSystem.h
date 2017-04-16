#ifndef __MENUSYSTEM_H__
#define __MENUSYSTEM_H__


#include "Menu.h"
#include "InputManager.h"
#include "StateManager.h"
#include "UIImage.h"
#include <vector>


class MenuSystem
{
public:
	MenuSystem();
	virtual ~MenuSystem();

	void Update();
	void Reset();

	void Init();

private:
	//::.. HELP FUNCTIONS ..:://
	void InitMainMenu(Menu* menu);
	void InitPlayMenu(Menu* menu);
	void InitCreateMenu(Menu* menu);
	void InitOptionsMenu(Menu* menu);

	void Input();

private:
	Menu *			m_rootMenu;
	InputManager *	m_inputManager;
	StateManager *	m_stateManager;
	UIImage			m_background;

};


#endif // __MENUSYSTEM_H__