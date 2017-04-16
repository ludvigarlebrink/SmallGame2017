#include "MenuSystem.h"



MenuSystem::MenuSystem()
{
	Init();
	
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
//	m_rootMenu->SetIsActive(true);
//	m_stateManager->SetCurrentState(GameState::MAIN_MENU);
	
}

void MenuSystem::Init()
{
	m_inputManager = InputManager::Get();
	m_stateManager = StateManager::Get();

	m_rootMenu = new Menu;
	m_rootMenu->SetIsActive(true);
	m_rootMenu->SetParent(nullptr);

	InitPlayMenu(m_rootMenu->AddChild( "Play"));
	
	m_rootMenu->AddChild(GameState::GAME, "Create");
	m_rootMenu->AddChild(GameState::GAME, "Options");
	m_rootMenu->AddChild(GameState::GAME, "Credits");
	m_rootMenu->AddChild(GameState::GAME, "Exit");
}

void MenuSystem::InitMainMenu()
{
	InitPlayMenu(m_rootMenu->AddChild("Play"));

	m_rootMenu->AddChild(GameState::GAME, "Create");
	m_rootMenu->AddChild(GameState::GAME, "Options");
	m_rootMenu->AddChild(GameState::GAME, "Credits");
	m_rootMenu->AddChild(GameState::GAME, "Exit");
}

void MenuSystem::InitPlayMenu(Menu* menu)
{
	menu->AddChild(GameState::GAME, "Create");
	menu->AddChild(GameState::GAME, "Create");
	menu->AddChild(GameState::GAME, "Create");
}

void MenuSystem::InitCreateMenu(Menu* menu)
{
}

void MenuSystem::InitOptionsMenu(Menu* menu)
{
}
