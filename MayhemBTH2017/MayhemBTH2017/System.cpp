#include "System.h"

#include "Mesh.h"
#include "MenuSystem.h"
#include "UIText.h"
#include "Prefab.h"
#include "PrefabManager.h"
#include "GamePhysics.h"
#include "GameUI.h"
#include "UIImage.h"
#include "GameSystem.h"
#include "TransitionManager.h"
#include "AntiAliasing.h"
#include "MeshQuad.h"
#include "Background.h"

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
	//	TransitionManager transitionManager;
	AntiAliasing msaa;
	MeshQuad quad;


	LevelEditor l;
	MenuSystem m;
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	m_stateManager->SetCurrentState(GameState::MAIN_MENU);
	bool isRunning = true;

	Transform transform;

	VirtualKeyboard vk;
	int count = 1;
	m.Init();
	float counter = 0;

	m_soundManager->PlayMusic("bensound-cute");

	Camera cam;


	GameSystem gs;

	ParticleSystem particles(".\\Assets\\GLSL\\GeometryPass", glm::vec3(40, 20, 0), glm::vec4(1.0, 0.0, 0.0, 1.0), 50.0f, 5005, 4.0f);
	TextureHandler teximp;
	Texture texture = teximp.Import(".\\Assets\\Textures\\fireball.png");


	Background bg;

	GameUI gameUI;

	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.7f, 1.0f);

		m_inputManager->Update();
		m_soundManager->Update();

		switch (m_stateManager->GetCurrentState())
		{
		case GameState::START:

			break;
		case GameState::MAIN_MENU:
			m.Update();
			break;
		case GameState::LEVEL_EDITOR:
			//	msaa.Reset();
			l.Update();
			//	msaa.Update();
			//	quad.Render();
			//	msaa.Bind();
			//	quad.Draw();
			break;
		case GameState::GAME:
			msaa.Reset();
			bg.UpdateAndRender();
			gs.Update();


			msaa.Update();
			quad.Render();

			msaa.Bind();
			quad.Draw();
			break;
		case GameState::EXIT:
			isRunning = false;
			break;
		default:
			break;
		}

		ScoreManager::Update();


		m_videoManager->Swap();
		m_timeManager->UpdateDeltaTime();
		counter += m_timeManager->GetDeltaTime();
	}
}


void System::Init()
{
	m_videoManager = VideoManager::Get();
	m_inputManager = InputManager::Get();
	m_timeManager = TimeManager::Get();
	m_stateManager = StateManager::Get();
	m_soundManager = SoundManager::Get();
}