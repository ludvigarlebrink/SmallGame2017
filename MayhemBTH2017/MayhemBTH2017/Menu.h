#ifndef __MENU_H__
#define __MENU_H__


#include "StateManager.h"
#include "TimeManager.h"
#include "UIText.h"
#include "UIImage.h"


#include <iostream>
#include <vector>


class Menu
{
public:
	Menu();
	virtual ~Menu();

	virtual void Render();

	//::.. MODIFY FUNCTIONS ..:://
	void GoForward();
	void GoBack();
	void MoveUp();
	void MoveDown();
	Menu* AddChild(char* title);
	Menu* AddChild(Menu* menu, char* title);
	void AddChild(GameState gameState, char* title);
	Menu* GetChildAt(uint32_t index);

	//::.. GET FUNCTIONS ..:://
	Menu * GetParent();
	bool GetIsActive();

	//::.. SET FUNCTIONS ..:://
	void SetParent(Menu * parent);
	void SetIsActive(bool value);
	void SetTitle(const char* title);

	void FreeChildren();

private:
	static const int32_t FONT_SIZE = 40;

	enum 
	{
		SUBMENU = 0,
		GAMESTATE
	};

	struct Button
	{
		UIText *	text;
		bool		isSelected;
		uint32_t	type;
		Menu *		subMenu;
		GameState	gameState;

	};


	std::vector<Button *>	m_button;

	UIText					m_title;
	bool					m_isActive;
	Menu *					m_parent;
	int32_t					m_currentSelection;
	int32_t					m_activeSubMenu;
	UIImage					m_selection;

	StateManager *			m_stateManager;
};


#endif