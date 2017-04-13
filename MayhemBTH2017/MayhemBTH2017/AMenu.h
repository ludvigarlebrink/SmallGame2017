#ifndef __AMENU_H__
#define __AMENU_H__


#include "StateManager.h"
#include "AShader.h"
#include "Texture.h"
#include "TextureImporter.h"
#include "Text.h"

#include <iostream>
#include <vector>


class AMenu
{
public:
	AMenu();
	virtual ~AMenu();

	virtual void Render();

	//::.. MODIFY FUNCTIONS ..:://
	void GoForward();
	void GoBack();
	void MoveUp();
	void MoveDown();

	//::.. GET FUNCTIONS ..:://
	AMenu * GetParent();
	bool GetIsActive();

	//::.. SET FUNCTIONS ..:://
	void SetParent(AMenu * parent);
	void SetIsActive(bool value);

protected:
	//::.. PROTECTED FUNCTIONS ..:://
	void AddChild(AMenu* subMenu, char* title);
	void AddChild(GameState gameState, char* title);
	AMenu* GetChildAt(uint32_t index);

	void FreeChildren();

private:
	enum 
	{
		SUBMENU = 0,
		GAMESTATE
	};

	struct Button
	{
		Text * text;
		Texture * texture;
		bool isActive;
	};

	std::vector<Button *>	m_button;

	bool					m_isActive;

	AMenu *					m_parent;
	std::vector<AMenu*>		m_subMenu;
	std::vector<GameState>	m_gameState;
	std::vector<uint32_t>	m_index;
	std::vector<uint32_t>	m_type;
	int						m_currentSelection;
	uint32_t				m_activeSubMenu;

	StateManager *			m_stateManager;

	AShader					m_shader;
	Transform				m_transform;
};


#endif