#include "System.h"


#include "MenuSystem.h"
#include "Mesh.h"
#include "MeshImporter.h"
#include "ParticleSystem.h"
#include "Game.h"
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
	Level lvl;
	MenuSystem m;
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	m_stateManager->SetCurrentState(GameState::MAIN_MENU);
	bool isRunning = true;
	ParticleSystem p("GeometryPass", glm::vec3(0.0, 0.0, 0.0), glm::vec4(1.0, 0.0, 0.0, 1.0), 1.0f, 100);

	MeshImporter meshImp;
	Mesh mesh = meshImp.Import();
	Transform transform;
	Camera camera;
	Game game;
	AShader shader;
	AShader shaderGreen;
	shader.Init("DebugShader", false, 0);
	shaderGreen.Init("DebugGreen", false, 0);

	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.7f, 1.0f);


		m_inputManager->Update();

		switch (m_stateManager->GetCurrentState())
		{
		case GameState::START:
			
			lvl.Render(camera);

			break;
		case GameState::MAIN_MENU:			
			shader.Bind();
			shader.Update(transform, camera);
			mesh.Render();
			m.Update();
			break;
		case GameState::LEVEL_EDITOR:
			l.Update();
			break;
		case GameState::GAME:
			camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
			game.Update(camera);
			shaderGreen.Bind();
			shaderGreen.Update(transform, camera);
			game.Render();
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
