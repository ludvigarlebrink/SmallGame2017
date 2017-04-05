#include "System.h"


#include "LevelEditor.h"
#include "InputManager.h"



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
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);


	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_inputManager->Update();

		l.Update();

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
}
