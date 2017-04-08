#include "AMenu.h"

#include <iostream>

AMenu::AMenu()
	: m_isActive(false)
{
	// Do nothing...
	m_stateManager = StateManager::Get();
	m_currentSelection = 0;
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

void AMenu::GoForward()
{
	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->GoForward();
		return;
	}

	if (m_type[m_currentSelection] == SUBMENU)
	{
		m_subMenu[m_index[m_currentSelection]]->SetIsActive(true);
		m_isActive = false;

	}
	else if (m_type[m_currentSelection] == GAMESTATE)
	{
		m_stateManager->SetCurrentState(m_gameState[m_index[m_currentSelection]]);
		FreeChildren();
	}
}

void AMenu::GoBack()
{
	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->GoBack();
		return;
	}

	if (m_parent == nullptr)
	{
		return;
	}

	m_parent->SetIsActive(true);
	m_isActive = false;
}

//::.. MODIFY FUNCTIONS ..:://
void AMenu::MoveUp()
{

	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->MoveUp();
		return;
	}

	++m_currentSelection;

	if (m_currentSelection >= m_index.size())
	{
		m_currentSelection = m_index.size() - 1;
	}
}

void AMenu::MoveDown()
{
	if (!m_isActive)
	{
		m_subMenu[m_activeSubMenu]->MoveDown();
		return;
	}

	--m_currentSelection;

	if (m_currentSelection < 0)
	{
		m_currentSelection = 0;
	}

}


//::.. GET FUNCTIONS ..:://
AMenu * AMenu::GetParent()
{
	return m_parent;
}

bool AMenu::GetIsActive()
{
	return m_isActive;
}

//::.. SET FUNCTIONS ..:://
void AMenu::SetParent(AMenu * parent)
{
	m_parent = parent;
}

void AMenu::SetIsActive(bool value)
{
	m_isActive = value;
}


//::.. PROTECTED FUNCTIONS ..:://
void AMenu::AddChild(AMenu *subMenu)
{
	m_subMenu.push_back(subMenu);
	m_index.push_back(m_subMenu.size() - 1);
	m_type.push_back(SUBMENU);
}

void AMenu::AddChild(GameState gameState)
{
	m_gameState.push_back(gameState);
	m_index.push_back(m_gameState.size() - 1);
	m_type.push_back(GAMESTATE);
}

AMenu * AMenu::GetChildAt(uint32_t index)
{
	return m_subMenu[index];
}

void AMenu::FreeChildren()
{
	if (m_parent == nullptr)
	{
		m_isActive = true;
		return;
	}

	m_isActive = false;
	m_parent->FreeChildren();
}

