#include "System.h"


#include "LevelEditor.h"
#include "InputManager.h"
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
	glDisable(GL_CULL_FACE);
	LevelEditor l;


	ParticleSystem p("GeometryPass", glm::vec3(0.0, 0.0, 0.0),  glm::vec3(0.0, 1.0, 0.0), 0.5f, 0.0f);



	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		p.UpdateParticles();
	
		//l.Update();
		// Switch between back and front buffer.
		m_inputManager->Update();
		m_videoManager->Swap();
	}
}

void System::Init()
{
	m_videoManager = VideoManager::Get();
	m_inputManager = InputManager::Get();
}
