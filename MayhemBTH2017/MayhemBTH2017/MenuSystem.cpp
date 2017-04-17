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
	Input();
	m_background.Render();
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

	InitMainMenu(m_rootMenu);

	// Init the background.
	m_background.SetSize(640, 640);
	m_background.SetPositon(20, 0);
	m_background.SetTexture(".\\Assets\\Sprites\\MainMenu.png");
}

void MenuSystem::InitMainMenu(Menu* menu)
{
	InitPlayMenu(menu->AddChild("Play"));
	InitCreateMenu(menu->AddChild("Create"));
	InitOptionsMenu(menu->AddChild("Options"));
	InitCreateMenu(menu->AddChild("Credits"));
	menu->AddChild(GameState::EXIT, "Exit");
}

void MenuSystem::InitPlayMenu(Menu* menu)
{
	menu->AddChild(GameState::GAME, "Quick Match");
	menu->AddChild(GameState::GAME, "Random Playlist");
	menu->AddChild(GameState::GAME, "Select Playlist");
}

void MenuSystem::InitCreateMenu(Menu* menu)
{
	menu->AddChild(GameState::LEVEL_EDITOR, "Level");
	menu->AddChild(GameState::GAME, "Playlist");
}

void MenuSystem::InitOptionsMenu(Menu* menu)
{
	menu->AddChild(GameState::GAME, "Video");
	menu->AddChild(GameState::GAME, "Sound");
	menu->AddChild(GameState::GAME, "Game");
	menu->AddChild(GameState::GAME, "Controlls");
}

void MenuSystem::Input()
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
}
