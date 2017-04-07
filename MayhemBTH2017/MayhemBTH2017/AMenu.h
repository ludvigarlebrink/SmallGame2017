#ifndef __AMENU_H__
#define __AMENU_H__


#include "StateManager.h"

#include <iostream>
#include <vector>


class AMenu
{
public:
	AMenu();
	virtual ~AMenu();

	//::.. PURE VIRTUAL FUNCTIONS ..:://
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render();

	//::.. MODIFY FUNCTIONS ..:://
	void OnPressed();
	void MoveUp();
	void MoveDown();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetParentID();

	//::.. SET FUNCTIONS ..:://
	void SetParentID(uint32_t parentID);

protected:
	//::.. PROTECTED FUNCTIONS ..:://
	void AddChild(AMenu* subMenu);
	void AddChild(GameState gameState);
	AMenu* GetChildAt(uint32_t index);

private:
	enum
	{
		SUBMENU = 0,
		GAMESTATE
	};

	bool					m_isActive;

	uint32_t				m_parentID;
	std::vector<AMenu*>		m_subMenu;
	std::vector<GameState>	m_gameState;
	std::vector<uint32_t>	m_index;
	std::vector<uint32_t>	m_type;
	uint32_t				m_currentSelection;
	uint32_t				m_activeSubMenu;
};


#endif