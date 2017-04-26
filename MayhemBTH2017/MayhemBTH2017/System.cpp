#include "System.h"

#include "Mesh.h"
#include "MenuSystem.h"
#include "UIText.h"
#include "Prefab.h"
#include "PrefabManager.h"
#include "GamePhysics.h"

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
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	m_stateManager->SetCurrentState(GameState::MAIN_MENU);
	bool isRunning = true;

	Transform transform;
	Camera camera;
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
	VirtualKeyboard vk;
	int count = 1;
	m.Init();
	float counter = 0;

	Prefab * pre = PrefabManager::Instantiate("");
	Camera cam;
	GamePhysics physics;
	physics.enterWorld();

	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.7f, 1.0f);
	
		m_inputManager->Update();

	//	pre->Render(cam);


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

			physics.Update();
			physics.Render(camera);
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
		SDL_Delay(10);
	//	counter += m_timeManager->GetDeltaTime();
	}
}


void System::Init()
{
	m_videoManager = VideoManager::Get();
	m_inputManager = InputManager::Get();
	m_timeManager = TimeManager::Get();
	m_stateManager = StateManager::Get();
}
