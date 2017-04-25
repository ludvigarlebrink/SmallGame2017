#include "System.h"


#include "MenuSystem.h"
#include "Mesh.h"
#include "MeshImporter.h"
#include "ParticleSystem.h"
#include "Game.h"

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
	ParticleSystem part(".\\Assets\\GLSL\\GeometryPass", glm::vec3(0.0, 0.0, 0.0), glm::vec4(0.1, 0.1, 1.0, 0.0), 15.1f, 30);
	ParticleSystem part2(".\\Assets\\GLSL\\ParticleExplosion", glm::vec3(0.0, 0.0, 0.0), glm::vec4(0.5, 0.5, 0.0, 0.4), 5.1f, 100);
	ParticleSystem part3(".\\Assets\\GLSL\\ParticleSparks", glm::vec3(1.0, 1.0, 0.0), glm::vec4(1.1, 1.1, 0.0, 0.8),0.3f, 10000);

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
	AShader ColliderShader;
	shader.Init(".\\Assets\\GLSL\\DebugShader", false, 0);
	shaderGreen.Init(".\\Assets\\GLSL\\DebugGreen", false, 0);
	ColliderShader.Init(".\\Assets\\GLSL\\ColliderShader", false, 0);
	TextureImporter teximp;
	Texture texture = teximp.Import(".\\Assets\\Textures\\fireball.png");
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));




	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.7f, 1.0f);

		m_inputManager->Update();

		physics.Update(transform);
		physics.Render(transform, camera);



		//switch (m_stateManager->GetCurrentState())
		//{
		//case GameState::START:
		//	
		//	lvl.Render(camera);

		//	break;
		//case GameState::MAIN_MENU:

			//shader.Bind();
			//shader.Update(transform, camera);

			//m.Update();

			//game.Render();

		//	break;
		//case GameState::LEVEL_EDITOR:

		//	l.Update();

		//	break;

		//case GameState::GAME: {

			camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
			shader.Bind();
			shader.Update(transform, camera);
			camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
			transform.SetPosition(42.0, 24.0, -0.0);


			//Draw scene

			//part1
			game.Update(camera);
			//part.Bind();
			//part.UpdateParticles();
			texture.Bind();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);
			part.RenderTransformed(1);
			glDisable(GL_BLEND);
			glDepthMask(TRUE);
		
			
			//part2
			//part2.Bind();
			//part2.UpdateParticles();
			texture.Bind();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);
			part2.RenderTransformed(1);
			glDisable(GL_BLEND);
			glDepthMask(TRUE);
			//part2
			//part3.Bind();
			//part3.UpdateParticles();
			texture.Bind();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);
			part3.RenderTransformed(1);
			glDisable(GL_BLEND);
			glDepthMask(TRUE);


		//}
		//	break;
		//case GameState::EXIT:
		//	isRunning = false;
		//	break;
		//default:
		//	break;
		//}

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
