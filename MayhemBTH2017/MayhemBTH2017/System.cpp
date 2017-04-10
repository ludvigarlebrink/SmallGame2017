#include "System.h"

#include "MeshImporter.h"
#include "MenuSystem.h"

System::System()
{
	Init();
}


System::~System()
{
}


//::.. THE MAIN LOOP ..:://
void System::Run()
{

	LevelEditor l;
	MenuSystem m;
	MeshImporter meshImport;
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	m_stateManager->SetCurrentState(GameState::MAIN_MENU);
	bool isRunning = true;

	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.7f, 1.0f);
		
		m_inputManager->Update();
		switch (m_stateManager->GetCurrentState())
		{
		case GameState::START:
			break;
		case GameState::MAIN_MENU:
			m.Update();
			break;
		case GameState::LEVEL_EDITOR:
			l.Update();
			break;
		case GameState::GAME:
			break;
		case GameState::EXIT:
			isRunning = false;
			break;
		default:
			break;
		}

		m_inputManager->Reset();

		// Switch between back and front buffer.
		m_videoManager->Swap();
		m_timeManager->UpdateDeltaTime();
	}
}

void System::Init()
{
	m_videoManager = VideoManager::Get();
	m_inputManager = InputManager::Get();
	m_timeManager = TimeManager::Get();
	m_stateManager = StateManager::Get();
}
