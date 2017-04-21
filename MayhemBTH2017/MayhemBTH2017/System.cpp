#include "System.h"


#include "MenuSystem.h"
#include "Mesh.h"
#include "MeshImporter.h"
#include "ParticleSystem.h"
#include "Game.h"
#include "Collider2D.h"
#include "GamePhysics.h"
#include "ParticleEmitter.h"

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
	Collider2D collider;
	collider.CreateBoundingBoxes();
	ParticleSystem part("GeometryPass", glm::vec3(0.0, 15.0, 0.0), glm::vec4(1.0, 0.0, 0.0, 0.8), 5.1f, 100);
	ParticleSystem part2("SplitterShader", glm::vec3(0.0, 0.0, 0.0), glm::vec4(1.0, 0.5, 0.5, 0.8), 5.5f, 10);
	LevelEditor l;
	Level lvl;
	MenuSystem m;
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	m_stateManager->SetCurrentState(GameState::MAIN_MENU);
	bool isRunning = true;
	
	GamePhysics physics;

	physics.enterWorld();


	Transform transform;
	Camera camera;
	Game game;
	AShader shader;
	AShader shaderGreen;
	shader.Init("DebugShader", false, 0);
	shaderGreen.Init("DebugGreen", false, 0);
	TextureImporter teximp;
	Texture texture = teximp.Import(".\\Assets\\Textures\\spark.png");
	ParticleEmitter emitter;
	emitter.SetParticleSystem(part2);

	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.7f, 1.0f);


		m_inputManager->Update();

		//physics.update();

		switch (m_stateManager->GetCurrentState())
		{
		case GameState::START:
			
			lvl.Render(camera);

			break;
		case GameState::MAIN_MENU:

			shader.Bind();
			shader.Update(transform, camera);

			m.Update();

			game.Render();

			break;
		case GameState::LEVEL_EDITOR:

			l.Update();

			break;

		case GameState::GAME: {

			camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
			shader.Bind();
			shader.Update(transform, camera);
			camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
			collider.DrawCollider(camera);
			transform.SetPosition(42.0, 24.0, -0.0);

			//Draw scene
			game.Update(camera);
			texture.Bind();
			
			//particle 1
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);
			part.UpdateParticles();
			part.RenderTransformed(1);
			glDisable(GL_BLEND);
			glDepthMask(TRUE);

			//particle 2
			transform.Rotate();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);
			part.UpdateParticles();
			part.RenderTransformed(0);
			glDisable(GL_BLEND);
			glDepthMask(TRUE);



		
		}
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
