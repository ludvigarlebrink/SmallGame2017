#include "Menu.h"

#include <iostream>

Menu::Menu()
	: m_isActive(false)
{
	// Do nothing...
	m_stateManager = StateManager::Get();
	m_currentSelection = 0;
	m_selection.SetTexture(".\\Assets\\Sprites\\Selection.png");
	m_selection.SetSize(336 * 0.8f, 78 * 0.8f);
	
	// Init title.
	m_title.SetSize(FONT_SIZE + 12);
	m_title.SetPositon(0, 170);
	m_title.SetColor(229, 122, 16, 255);
	m_title.SetText("MAIN MENU");
}


Menu::~Menu()
{
	// Do nothing...
}


void Menu::Render()
{
	if (!m_isActive)
	{
		m_button[m_activeSubMenu]->subMenu->Render();
		return;
	}

	m_selection.Render();
	m_title.Render();

	for (int i = 0; i < m_button.size(); i++)
	{
		if (m_button[i]->isSelected)
		{
			m_selection.SetPositon(0, (-i * (FONT_SIZE + 16)) + 70);
		}

		m_button[i]->text->SetSize(FONT_SIZE);
		m_button[i]->text->SetPositon(0, (-i * (FONT_SIZE + 16)) + 70);
		m_button[i]->text->Render();
	}

}

void Menu::GoForward()
{
	if (!m_isActive)
	{
		m_button[m_currentSelection]->subMenu->GoForward();
		return;
	}

	if (m_button[m_currentSelection]->type == SUBMENU)
	{

		m_activeSubMenu = m_currentSelection;
		m_button[m_activeSubMenu]->subMenu->SetIsActive(true);
		m_isActive = false;

	}
	else if (m_button[m_currentSelection]->type == GAMESTATE)
	{
		m_stateManager->SetCurrentState(m_button[m_currentSelection]->gameState);
		FreeChildren();
	}
}

void Menu::GoBack()
{
	if (!m_isActive)
	{
		m_button[m_activeSubMenu]->subMenu->GoBack();
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
void Menu::MoveUp()
{
	if (!m_isActive)
	{
		m_button[m_activeSubMenu]->subMenu->MoveUp();
		return;
	}

	m_button[m_currentSelection]->isSelected = false;

	--m_currentSelection;

	if (m_currentSelection < 0)
	{
		m_currentSelection = 0;
	}

	m_button[m_currentSelection]->isSelected = true;
}

void Menu::MoveDown()
{
	if (!m_isActive)
	{
		m_button[m_activeSubMenu]->subMenu->MoveDown();
		return;
	}

	// TEMP
	m_button[m_currentSelection]->isSelected = false;

	++m_currentSelection;

	if (m_currentSelection >= m_button.size())
	{
		m_currentSelection = m_button.size() - 1;
	}

	m_button[m_currentSelection]->isSelected = true;
}


//::.. GET FUNCTIONS ..:://
Menu * Menu::GetParent()
{
	return m_parent;
}

bool Menu::GetIsActive()
{
	return m_isActive;
}

//::.. SET FUNCTIONS ..:://
void Menu::SetParent(Menu * parent)
{
	m_parent = parent;
}

void Menu::SetIsActive(bool value)
{
	m_isActive = value;
}

void Menu::SetTitle(const char * title)
{
	m_title.SetText(title);
}


//::.. PROTECTED FUNCTIONS ..:://
Menu* Menu::AddChild(char* title)
{
	Button * button = new Button;

	Menu * menu = new Menu;
	menu->SetParent(this);

	UIText * text = new UIText;
	text->SetText(title);
	text->SetSize(FONT_SIZE);
	text->SetColor(235, 235, 180, 255);

	button->type = SUBMENU;
	button->gameState = GameState::START;
	button->isSelected = false;
	button->subMenu = menu;
	button->text = text;

	if (m_button.size() == 0)
	{
		button->isSelected = true;
	}
	else
	{
		button->isSelected = false;
	}

	m_button.push_back(button);

	return menu;
}

Menu * Menu::AddChild(Menu * menu, char * title)
{
	return nullptr;
}

void Menu::AddChild(GameState gameState, char* title)
{
	Button * button = new Button;

	UIText * text = new UIText;
	text->SetText(title);
	text->SetSize(FONT_SIZE);
	text->SetColor(235, 235, 180, 255);

	button->type = GAMESTATE;
	button->gameState = gameState;
	button->isSelected = false;
	button->subMenu = nullptr;
	button->text = text;

	if (m_button.size() == 0)
	{
		button->isSelected = true;
	}
	else
	{
		button->isSelected = false;
	}

	m_button.push_back(button);
}

Menu * Menu::GetChildAt(uint32_t index)
{
	return nullptr;
}

void Menu::FreeChildren()
{
	if (m_parent == nullptr)
	{
		m_isActive = true;
		return;
	}

	m_isActive = false;
	m_parent->FreeChildren();
}

