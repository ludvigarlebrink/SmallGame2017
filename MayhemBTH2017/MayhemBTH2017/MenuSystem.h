#ifndef __MENUSYSTEM_H__
#define __MENUSYSTEM_H__


#include "InputManager.h"
#include "StateManager.h"
#include "UIImage.h"
#include "Menu.h"
#include "Timer.h"

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

	void HandleInput();
	void Render();

private:
	VideoManager *	m_videoManager;
	InputManager *	m_inputManager;
	StateManager *	m_stateManager;

	Menu *			m_rootMenu;
	UIImage			m_background;
	UIImage			m_paperOpen;
	UIImage			m_paperClosed1;
	UIImage			m_paperClosed2;

	bool			m_changeMenu;
	Timer			m_timer;
};


#endif // __MENUSYSTEM_H__