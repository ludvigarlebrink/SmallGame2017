#include "MenuSystem.h"



MenuSystem::MenuSystem()
{
	Init();
	
}


MenuSystem::~MenuSystem()
{
	delete m_rootMenu;
}

void MenuSystem::Update()
{
	// First: handle input.
	
	if (!m_changeMenu)
	{
		HandleInput();
	}

	Render();
}

void MenuSystem::Reset()
{
//	m_rootMenu->SetIsActive(true);
//	m_stateManager->SetCurrentState(GameState::MAIN_MENU);
}

void MenuSystem::Init()
{


	m_videoManager = VideoManager::Get();
	m_inputManager = InputManager::Get();

	m_changeMenu = false;

	m_rootMenu = new Menu;
	m_rootMenu->SetIsActive(true);
	m_rootMenu->SetParent(nullptr);

	InitMainMenu(m_rootMenu);

	// Init the background.
	m_background.SetSize(m_videoManager->GetWidth(), m_videoManager->GetHeight());
	m_background.SetTexture(".\\Assets\\Sprites\\MenuConcept.png");

	m_paperOpen.SetSize(640, 640);
	m_paperOpen.SetPosition(20, 0);
	m_paperOpen.SetTexture(".\\Assets\\Sprites\\MainMenu.png");

	m_paperClosed1.SetSize(640, 640);
	m_paperClosed1.SetPosition(20, 0);
	m_paperClosed1.SetTexture(".\\Assets\\Sprites\\ClosedMenu1.png");

	m_paperClosed2.SetSize(640, 640);
	m_paperClosed2.SetPosition(20, 0);
	m_paperClosed2.SetTexture(".\\Assets\\Sprites\\ClosedMenu2.png");
}

void MenuSystem::InitMainMenu(Menu* menu)
{
	menu->SetTitle("MAIN MENU");
	menu->AddChild(GameState::LOAD_GAME, "Play");
	menu->AddChild(GameState::LOAD_LEVEL_EDITOR, "Create");
	menu->AddChild(GameState::EXIT, "Exit");
}


void MenuSystem::HandleInput()
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
		m_changeMenu = true;
		m_timer.SetTimer(0.5f, true);
	}

	if (m_inputManager->GetButtonDown(CONTROLLER_BUTTON_B))
	{
		m_rootMenu->GoBack();
		m_changeMenu = true;
		m_timer.SetTimer(0.5f, true);
	}

}

void MenuSystem::Render()
{
	m_background.Render();

	if (m_changeMenu)
	{
		if (m_timer.GetElapsed() < 0.1f || m_timer.GetElapsed() > 0.4f)
		{
			m_paperClosed1.Render();
		}
		else
		{
			m_paperClosed2.Render();
		}

		m_changeMenu = !m_timer.Update();
	}
	else
	{
		m_paperOpen.Render();
		m_rootMenu->Render();
	}
}
