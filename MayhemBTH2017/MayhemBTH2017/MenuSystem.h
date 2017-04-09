#ifndef __MENUSYSTEM_H__
#define __MENUSYSTEM_H__


#include "AMenu.h"
#include "MainMenu.h"
#include "InputManager.h"
#include "StateManager.h"

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
	AMenu *			m_rootMenu;
	InputManager *	m_inputManager;
	StateManager *	m_stateManager;


};


#endif // __MENUSYSTEM_H__