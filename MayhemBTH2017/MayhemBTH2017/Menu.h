#ifndef __AMENU_H__
#define __AMENU_H__


#include "StateManager.h"
#include "AShader.h"
#include "Texture.h"
#include "TextureImporter.h"
#include "UIText.h"

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
	void AddChild(GameState gameState, char* title);
	Menu* GetChildAt(uint32_t index);

	//::.. GET FUNCTIONS ..:://
	Menu * GetParent();
	bool GetIsActive();

	//::.. SET FUNCTIONS ..:://
	void SetParent(Menu * parent);
	void SetIsActive(bool value);

	void FreeChildren();

private:
	enum 
	{
		SUBMENU = 0,
		GAMESTATE
	};

	struct Button
	{
		UIText *	text;
		bool		isActive;
		uint32_t	type;
		Menu *		subMenu;
		GameState	gameState;

	};

	std::vector<Button *>	m_button;

	bool					m_isActive;

	Menu *					m_parent;

	std::vector<Menu*>		m_subMenu;
	std::vector<GameState>	m_gameState;
	std::vector<uint32_t>	m_index;
	std::vector<uint32_t>	m_type;
	int32_t					m_currentSelection;
	uint32_t				m_activeSubMenu;

	StateManager *			m_stateManager;
};


#endif