#include "GameSystem.h"



GameSystem::GameSystem()
{
	m_input = InputManager::Get();
	m_numPlayers = 0;
	m_currState = INIT_PLAYER_READY;
	m_playerReadyUI = nullptr;

	for (uint32_t i = 0; i < MAX_PLAYERS; i++)
	{
		m_playerReady[i] = false;
	}

	m_gameTime = 60.0f;

	m_camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
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
		InitPlayerReady();
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
	m_playerReadyUI = new PlayerReadyUI[4];


	// FIX POS!
	m_playerReadyUI[0].playerName.SetPosition((-0.75f * vm->GetWidth()) / 2, 20);
	m_playerReadyUI[1].playerName.SetPosition((-0.25f * vm->GetWidth()) / 2, 20);
	m_playerReadyUI[2].playerName.SetPosition((0.25f * vm->GetWidth()) / 2, 20);
	m_playerReadyUI[3].playerName.SetPosition((0.75f * vm->GetWidth()) / 2, 20);

	m_playerReadyUI[0].playerName.SetText("PLAYER 1");
	m_playerReadyUI[1].playerName.SetText("PLAYER 2");
	m_playerReadyUI[2].playerName.SetText("PLAYER 3");
	m_playerReadyUI[3].playerName.SetText("PLAYER 4");

	m_playerReadyUI[0].playerReady.SetPosition((-0.75f * vm->GetWidth()) / 2, -20);
	m_playerReadyUI[1].playerReady.SetPosition((-0.25f * vm->GetWidth()) / 2, -20);
	m_playerReadyUI[2].playerReady.SetPosition((0.25f * vm->GetWidth()) / 2, -20);
	m_playerReadyUI[3].playerReady.SetPosition((0.75f * vm->GetWidth()) / 2, -20);

	m_playerReadyUI[0].r = 248;
	m_playerReadyUI[0].g = 78;
	m_playerReadyUI[0].b = 78;
	m_playerReadyUI[0].a = 255;

	m_playerReadyUI[1].r = 78;
	m_playerReadyUI[1].g = 248;
	m_playerReadyUI[1].b = 78;
	m_playerReadyUI[1].a = 255;

	m_playerReadyUI[2].r = 248;
	m_playerReadyUI[2].g = 248;
	m_playerReadyUI[2].b = 78;
	m_playerReadyUI[2].a = 255;

	m_playerReadyUI[3].r = 78;
	m_playerReadyUI[3].g = 78;
	m_playerReadyUI[3].b = 248;
	m_playerReadyUI[3].a = 255;


	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerReadyUI[i].playerReady.SetText("NOT READY");
	}

	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerReadyUI[i].playerName.SetColor(170, 170, 170, 255);
		m_playerReadyUI[i].playerReady.SetColor(170, 170, 170, 255);
	}

	m_pressToCont.SetPosition(0, -150);
	m_pressToCont.SetColor(255, 255, 255, 255);
	m_pressToCont.SetText("PRESS S TO CONTINUE!");

	m_currState = PLAYER_READY;
}


void GameSystem::PlayerReady()
{
	for (uint32_t i = 0; i < 4; i++)
	{
		if (m_input->GetButtonDown(CONTROLLER_BUTTON_A, i))
		{
			m_playerReady[i] = !m_playerReady[i];
			
			if (m_playerReady[i])
			{
				m_playerReadyUI[i].playerReady.SetColor(m_playerReadyUI[i].r, 
					m_playerReadyUI[i].g, m_playerReadyUI[i].b, 255);
				m_playerReadyUI[i].playerName.SetColor(m_playerReadyUI[i].r,
					m_playerReadyUI[i].g, m_playerReadyUI[i].b, 255);


				m_playerReadyUI[i].playerReady.SetText("READY!");
			}
			else
			{
				m_playerReadyUI[i].playerName.SetColor(170, 170, 170, 255);
				m_playerReadyUI[i].playerReady.SetColor(170, 170, 170, 255);

				m_playerReadyUI[i].playerReady.SetText("NOT READY!");
			}
		}
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
				TransitionManager::StartFadingOut();
				m_currState = INIT_PLAY;
				return;
			}
		}
	}

	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerReadyUI[i].playerReady.Render();
		m_playerReadyUI[i].playerName.Render();
		m_pressToCont.Render();

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

	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerReadyUI[i].playerReady.Render();
		m_playerReadyUI[i].playerName.Render();
	}

	if (TransitionManager::GetIsBlack())
	{
		if (m_playerReadyUI != nullptr)
		{
			delete[] m_playerReadyUI;
			m_playerReadyUI = nullptr;
		}

		m_world = new GamePhysics;
		m_currState = START_PLAY;

		TransitionManager::StartFadingIn();
		TimeManager::ResetDeltaTime();
	}
	
}

void GameSystem::StartPlay()
{
	Camera camera;
	camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));

	m_world->Update();
	m_world->Render(camera);

	if (!TransitionManager::GetIsFadingIn())
	{
		m_currState = PLAY;
	}
}

void GameSystem::Play()
{
	m_world->Update();
	m_world->Render(m_camera);

	m_gameUI.Update(nullptr, m_gameTime - m_timer.GetElapsed());
	m_gameUI.Render();

	m_timer.Update();
}

void GameSystem::LoadNextLevel()
{

}

void GameSystem::GameOver()
{

}
