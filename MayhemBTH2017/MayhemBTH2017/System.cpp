#include "System.h"


#include "LevelEditor.h"
#include "InputManager.h"
#include "AntiAliasing.h"
#include "MeshQuad.h"
#include "ParticleSystem.h"

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
	MeshQuad quad;
	AntiAliasing msaa;
	LevelEditor l;
	ParticleSystem p("GeometryPass", glm::vec3(0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 1.0), 0.005f, 50);
	msaa.Init();
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	TextureImporter teximp;
	Texture texture = teximp.Import(".\\Assets\\Textures\\fireball.png");
	

	while (true)
	{
		
		msaa.Reset();
		m_inputManager->Update();
		l.Update();
		msaa.Update();
		m_inputManager->Reset();
		quad.Render();
		msaa.Bind();
		quad.Draw();

		p.Bind();
		p.UpdateParticles();
		texture.Bind();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		p.RenderTransformed(1);
		glDisable(GL_BLEND);
		glDepthMask(TRUE);

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
}
