#include "GameSystem.h"



GameSystem::GameSystem()
{
	m_input = InputManager::Get();
	m_numPlayers = 0;
	m_currState = PLAYER_READY;

	for (uint32_t i = 0; i < MAX_PLAYERS; i++)
	{
		m_playerReady[i] = false;
	}
}


GameSystem::~GameSystem()
{
}

void GameSystem::Load(uint32_t gameMode)
{
	m_gameMode = gameMode;
}

void GameSystem::Free()
{
}


void GameSystem::Update()
{
	switch (m_currState)
	{
	case GAME_SETUP:
		GameSetup();
		break;

	case INIT_PLAYER_READY:
		PlayerReady();
		break;

	case PLAYER_READY:
		PlayerReady();
		break;

	case INIT_PLAY:
		InitPlay();
		break;

	case START_PLAY:
		StartPlay();
		break;
	
	case PLAY:
		Play();
		break;

	case LOAD_NEXT_LEVEL:
		LoadNextLevel();
		break;

	case GAME_OVER:
		GameOver();
		break;

	default:
		break;
	}
}


void GameSystem::GameSetup()
{

}

void GameSystem::InitPlayerReady()
{
	VideoManager * vm = VideoManager::Get();

	m_playerReadyUI[0].playerName.SetPosition((-0.3f * vm->GetWidth()) / 2, -20);
	m_playerReadyUI[1].playerName.SetPosition((-0.1f * vm->GetWidth()) / 2, -20);
	m_playerReadyUI[2].playerName.SetPosition((0.1f * vm->GetWidth()) / 2, -20);
	m_playerReadyUI[3].playerName.SetPosition((0.3f * vm->GetWidth()) / 2, -20);

	m_playerReadyUI[0].playerReady.SetPosition((-0.3f * vm->GetWidth()) / 2, 20);
	m_playerReadyUI[1].playerReady.SetPosition((-0.1f * vm->GetWidth()) / 2, 20);
	m_playerReadyUI[2].playerReady.SetPosition((0.1f * vm->GetWidth()) / 2, 20);
	m_playerReadyUI[3].playerReady.SetPosition((0.3f * vm->GetWidth()) / 2, 20);


	m_currState = INIT_PLAY;
}


void GameSystem::PlayerReady()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A), 0)
	{
		m_playerReady[0] = !m_playerReady[0];
		if (m_playerReady)
		{

		}
		else
		{

		}
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A), 1)
	{
		m_playerReady[1] = !m_playerReady[1];
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A), 2)
	{
		m_playerReady[2] = !m_playerReady[2];
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A), 3)
	{
		m_playerReady[3] = !m_playerReady[3];
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		int num = 0;
		for (uint32_t i = 0; i < MAX_PLAYERS; i++)
		{
			if (m_playerReady[i])
			{
				++num;
			}

			// TEMP CHANGE TO TWO
			if (num >= 1)
			{
				m_currState = INIT_PLAY;
				return;
			}
		}
	}
}


void GameSystem::InitPlay()
{
	for(uint32_t i = 0; i < MAX_PLAYERS; ++i)
	{
		if (m_playerReady[i])
		{
			++m_numPlayers;
		}
	}



	m_world = new GamePhysics;
	
	m_currState = START_PLAY;
	
}

void GameSystem::StartPlay()
{
	if (m_playerReadyUI != nullptr)
	{
		delete[] m_playerReadyUI;
		m_playerReadyUI = nullptr;
	}

	m_currState = PLAY;
}

void GameSystem::Play()
{
	Camera camera;
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));

	m_world->Update();
	m_world->Render(camera);
}

void GameSystem::LoadNextLevel()
{

}

void GameSystem::GameOver()
{

}
