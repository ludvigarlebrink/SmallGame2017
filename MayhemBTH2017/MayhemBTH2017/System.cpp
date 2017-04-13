#include "System.h"

#include "TempShader.h"
#include "Mesh.h"
#include "MeshImporter.h"
#include "MenuSystem.h"
#include "Text.h"
#include "VirtualKeyboard.h"

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

	Text text;
	MeshImporter meshImp;
	Mesh mesh = meshImp.Import();
	Transform transform;
	Camera camera;
	TempShader shader;
	JointSkeleton skel;;
	VirtualKeyboard vk;
	int count = 1;
	shader.Init(".\\Assets\\GLSL\\SkeletalAnimation", false);
	m.Init();
	float counter = 0;
	while (isRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.7f, 1.0f);
	
		m_inputManager->Update();
	
		switch (m_stateManager->GetCurrentState())
		{
		case GameState::START:
			break;
		case GameState::MAIN_MENU:
	//		m.Update();
			break;
	//	case GameState::LEVEL_EDITOR:
	//		l.Update();
	//		break;
	//	case GameState::GAME:
	//		break;
	//	case GameState::EXIT:
	//		isRunning = false;
	//		break;
		default:
			break;
		}
	
		vk.Render();
		m_inputManager->Reset();

		// Switch between back and front buffer.
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
}
