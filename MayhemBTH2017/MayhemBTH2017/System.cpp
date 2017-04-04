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
	glDisable(GL_CULL_FACE);
	LevelEditor l;


	while (true)
	{
		m_inputManager->Update();

		glClear(GL_COLOR_BUFFER_BIT);


		l.Update();

		m_inputManager->Reset();

		// Switch between back and front buffer.
		m_videoManager->Swap();

	}
}

void System::Init()
{
	m_videoManager = VideoManager::Get();
	m_inputManager = InputManager::Get();
}
