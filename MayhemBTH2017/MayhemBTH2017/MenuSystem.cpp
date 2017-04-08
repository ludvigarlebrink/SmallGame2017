#include "MenuSystem.h"



MenuSystem::MenuSystem()
{
	m_inputManager = InputManager::Get();
	m_stateManager = StateManager::Get();
	m_rootMenu = new StartMenu;
	m_rootMenu->SetIsActive(true);
	m_rootMenu->SetParent(nullptr);
}


MenuSystem::~MenuSystem()
{

}

void MenuSystem::Update()
{
	
	if (m_inputManager->GetButtonDown(CONTROLLER_BUTTON_DPAD_DOWN))
	{
		m_rootMenu->MoveDown();
	}
	else if (m_inputManager->GetButtonDown(CONTROLLER_BUTTON_DPAD_UP))
	{
		m_rootMenu->MoveUp();
	}

	if (m_inputManager->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_rootMenu->GoForward();
	}

	if (m_inputManager->GetButtonDown(CONTROLLER_BUTTON_B))
	{
		m_rootMenu->GoBack();
	}

	m_rootMenu->Render();
}

void MenuSystem::Reset()
{
	m_rootMenu->SetIsActive(true);
	m_stateManager->SetCurrentState(GameState::MAIN_MENU);
	
}

void MenuSystem::Init()
{
}
