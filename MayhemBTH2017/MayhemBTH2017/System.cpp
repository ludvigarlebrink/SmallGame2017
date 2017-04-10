#include "System.h"


#include "LevelEditor.h"
#include "InputManager.h"
#include "AntiAliasing.h"
#include "MeshQuad.h"



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
	msaa.Init();
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);


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
