#include "AMenu.h"



AMenu::AMenu()
	: m_isActive(false)
{
	// Do nothing...
}


AMenu::~AMenu()
{
	// Do nothing...
}


void AMenu::Render()
{
	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->Render();
	}

	// ELSE RENDER THIS MENU


}

void AMenu::OnPressed()
{
	if (m_type[m_currentSelection] == SUBMENU)
	{
		// LOAD SUBMENU

	}
	else if (m_type[m_currentSelection] == GAMESTATE)
	{
		// CHANGE GAME STATE
	}
}

//::.. MODIFY FUNCTIONS ..:://
void AMenu::MoveUp()
{
	++m_currentSelection;

	if (m_currentSelection >= m_index.size())
	{
		m_currentSelection = m_index.size() - 1;
	}
}

void AMenu::MoveDown()
{
	--m_currentSelection;

	if (m_currentSelection < 0)
	{
		m_currentSelection = 0;
	}

}


//::.. GET FUNCTIONS ..:://
uint32_t AMenu::GetParentID()
{
	return m_parentID;
}

//::.. SET FUNCTIONS ..:://
void AMenu::SetParentID(uint32_t parentID)
{
	m_parentID = parentID;
}


//::.. PROTECTED FUNCTIONS ..:://
void AMenu::AddChild(AMenu *subMenu)
{
	m_subMenu.push_back(subMenu);
	m_index.push_back(m_index.size());
	m_type.push_back(SUBMENU);
}

void AMenu::AddChild(GameState gameState)
{
	m_gameState.push_back(gameState);
	m_index.push_back(m_index.size());
	m_type.push_back(GAMESTATE);
}

AMenu * AMenu::GetChildAt(uint32_t index)
{
	return m_subMenu[index];
}

