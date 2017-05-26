#include "System.h"






System::System()
{
	Init();
}


System::~System()
{
	Free();
}


//::.. THE MAIN LOOP ..:://
void System::Run()
{
	//	TransitionManager transitionManager;
	AntiAliasing msaa;
	MeshQuad quad;

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	m_stateManager->SetCurrentState(GameState::START);

	bool isRunning = true;

	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		m_inputManager->Update();
		m_soundManager->Update();

		msaa.Reset();

		switch (m_stateManager->GetCurrentState())
		{
		case GameState::START:
			m_stateManager->SetCurrentState(GameState::LOAD_MAIN_MENU);
			break;
		case GameState::LOAD_MAIN_MENU:
			Free();
			m_menuSystem = new MenuSystem;
			m_stateManager->SetCurrentState(GameState::MAIN_MENU);
			break;
		case GameState::MAIN_MENU:
			m_menuSystem->Update();
			break;
		case GameState::LOAD_LEVEL_EDITOR:
			Free();
			m_background = new Background;
			m_levelEditor = new LevelEditor;
			m_stateManager->SetCurrentState(GameState::LEVEL_EDITOR);
			break;
		case GameState::LEVEL_EDITOR:
			m_background->UpdateAndRender();
			m_levelEditor->Update();
			break;
		case GameState::LOAD_GAME:
			Free();
			m_background = new Background;
			m_gameSystem = new GameSystem;
			m_stateManager->SetCurrentState(GameState::GAME);
			break;
		case GameState::GAME:
			m_background->UpdateAndRender();
			m_gameSystem->Update();
			break;
		case GameState::EXIT:
			Free();
			isRunning = false;
			break;
		default:
			break;
		}

		TransitionManager::Update();

		msaa.Update();
		quad.Render();

		msaa.Bind();
		quad.Draw();

		// Update managers.
		PostProcessingManager::Update();
		ScoreManager::Update();

		m_videoManager->Swap();
		m_timeManager->UpdateDeltaTime();
	}
}


void System::Init()
{
	m_videoManager	= VideoManager::Get();
	m_inputManager	= InputManager::Get();
	m_timeManager	= TimeManager::Get();
	m_stateManager	= StateManager::Get();
	m_soundManager	= SoundManager::Get();

	m_menuSystem	= nullptr;
	m_background	= nullptr;
	m_levelEditor	= nullptr;
	m_gameSystem	= nullptr;
}


void System::Free()
{
	if (m_menuSystem != nullptr)
	{
		delete m_menuSystem;
		m_menuSystem = nullptr;
	}

	if (m_background != nullptr)
	{
		delete m_background;
		m_background = nullptr;
	}

	if (m_levelEditor != nullptr)
	{
		delete m_levelEditor;
		m_levelEditor = nullptr;
	}

	if (m_gameSystem != nullptr)
	{
		delete m_gameSystem;
		m_gameSystem = nullptr;
	}
}
