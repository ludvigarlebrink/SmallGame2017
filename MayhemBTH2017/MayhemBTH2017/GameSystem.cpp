#include "GameSystem.h"



GameSystem::GameSystem()
{
	m_playCountdown = true;
	m_input = InputManager::Get();
	m_soundManager = SoundManager::Get();
	m_numPlayers = 0;
	m_currState = SELECT_LEVEL;
	m_playerReadyUI = nullptr;

	for (uint32_t i = 0; i < MAX_PLAYERS; i++)
	{
		m_playerReady[i] = false;
	}

	m_camera.SetPosition(glm::vec3(((84 / 2)), ((48 / 2)), -51.2f));
	m_gameSettings = new GameSettings;
	m_gameSettings->CreateUI();

	m_pressToCont.SetPosition(0, 80 - (VideoManager::Get()->GetHeight() / 2));
	m_pressToCont.SetColor(255, 255, 255, 255);
	m_pressToCont.SetText("Press S to continue");
}


GameSystem::~GameSystem()
{
	Free();
}

void GameSystem::Load(uint32_t gameMode)
{
	m_gameMode = gameMode;
}

void GameSystem::Free()
{
	if (m_gameSettings != nullptr)
	{
		delete m_gameSettings;
		m_gameSettings = nullptr;
	}

	if (m_playerReadyUI != nullptr)
	{
		delete[] m_playerReadyUI;
		m_playerReadyUI = nullptr;
	}

	if (m_world != nullptr)
	{
		delete m_world;
		m_world = nullptr;
	}
}


void GameSystem::Update()
{
	switch (m_currState)
	{
	case SELECT_LEVEL:
		SelectLevel();
		break;

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

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_BACK))
	{
		StateManager::Get()->SetCurrentState(GameState::LOAD_MAIN_MENU);
	}
}


void GameSystem::SelectLevel()
{

	if (!m_levelSelector.GetVisualsInitialized())
	{
		m_levelSelector.InitVisuals();
	}

	m_levelSelector.Update();

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		if (m_levelSelector.SaveQueue())
		{
			m_levelSelector.FreeVisuals();
			m_currState = GAME_SETUP;

		}
	}

	m_pressToCont.Render();
}


void GameSystem::GameSetup()
{
	m_pressToCont.Render();

	m_gameSettings->Update();
	m_gameSettings->Render();

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		m_currState = INIT_PLAYER_READY;
	}
}


void GameSystem::InitPlayerReady()
{
	VideoManager * vm = VideoManager::Get();
	m_playerReadyUI = new PlayerReadyUI[4];


	// FIX POS!
	m_playerReadyUI[0].playerName.SetPosition(static_cast<int>((-0.75f * vm->GetWidth()) / 2), 20);
	m_playerReadyUI[1].playerName.SetPosition(static_cast<int>((-0.25f * vm->GetWidth()) / 2), 20);
	m_playerReadyUI[2].playerName.SetPosition(static_cast<int>((0.25f * vm->GetWidth()) / 2), 20);
	m_playerReadyUI[3].playerName.SetPosition((0.75f * vm->GetWidth()) / 2, 20);

	m_playerReadyUI[0].playerName.SetText("PLAYER 1");
	m_playerReadyUI[1].playerName.SetText("PLAYER 2");
	m_playerReadyUI[2].playerName.SetText("PLAYER 3");
	m_playerReadyUI[3].playerName.SetText("PLAYER 4");

	m_playerReadyUI[0].playerReady.SetPosition(static_cast<int>((-0.75f * vm->GetWidth()) / 2), -20);
	m_playerReadyUI[1].playerReady.SetPosition(static_cast<int>((-0.25f * vm->GetWidth()) / 2), -20);
	m_playerReadyUI[2].playerReady.SetPosition(static_cast<int>((0.25f * vm->GetWidth()) / 2), -20);
	m_playerReadyUI[3].playerReady.SetPosition(static_cast<int>((0.75f * vm->GetWidth()) / 2), -20);

	m_playerReadyUI[0].r = 252;
	m_playerReadyUI[0].g = 61;
	m_playerReadyUI[0].b = 73;
	m_playerReadyUI[0].a = 255;

	m_playerReadyUI[1].r = 255;
	m_playerReadyUI[1].g = 147;
	m_playerReadyUI[1].b = 73;
	m_playerReadyUI[1].a = 255;

	m_playerReadyUI[2].r = 61;
	m_playerReadyUI[2].g = 212;
	m_playerReadyUI[2].b = 66;
	m_playerReadyUI[2].a = 255;

	m_playerReadyUI[3].r = 43;
	m_playerReadyUI[3].g = 166;
	m_playerReadyUI[3].b = 160;
	m_playerReadyUI[3].a = 255;


	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerReadyUI[i].playerReady.SetText("PRESS A");
	}

	for (uint32_t i = 0; i < 4; i++)
	{
		m_playerReadyUI[i].playerName.SetColor(170, 170, 170, 255);
		m_playerReadyUI[i].playerReady.SetColor(170, 170, 170, 255);
	}

	m_pressToCont.SetText("Press S to battle!");

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

				if (i == 0)
					m_soundManager->PlaySFX("ready1");
				if (i == 1)
					m_soundManager->PlaySFX("ready2");
				if (i == 2)
					m_soundManager->PlaySFX("ready3");
				if (i == 3)
					m_soundManager->PlaySFX("ready4");

				m_playerReadyUI[i].playerReady.SetText("READY!");
			}
			else
			{
				m_playerReadyUI[i].playerName.SetColor(170, 170, 170, 255);
				m_playerReadyUI[i].playerReady.SetColor(170, 170, 170, 255);

				m_playerReadyUI[i].playerReady.SetText("PRESS A");
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
				// INIT PLAY
				m_numPlayers = num;
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

		if (m_world == nullptr)
		{
			m_world = new GamePhysics;
			m_world->SetNrOfPlayers(m_numPlayers);
		}

		LevelHandler levelHandler;
		m_world->EnterWorld(m_levelSelector.GetLevel());
		m_currState = START_PLAY;

		TransitionManager::StartFadingIn();
		TimeManager::ResetDeltaTime();
	}
	m_soundManager->FadeInNewMusic("match_song_1", 3, 10);
	TransitionManager::Update();
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
		m_timer.SetTimer(m_gameSettings->GetGameLenght(), true, false);
	}

	TransitionManager::Update();
}


void GameSystem::Play()
{
	TransitionManager::Update();

	m_timer.Update();
	m_world->Update();
	m_world->Render(m_camera);

	if (m_timer.GetElapsed() >= m_timer.GetSetTime() - 11 && m_playCountdown) {
		m_soundManager->PlaySFX("countdown");
		m_playCountdown = false;
	}

	m_atomicBomb.Update(m_camera);

	if (TransitionManager::GetIsBlack())
	{
		m_currState = LOAD_NEXT_LEVEL;
	}
	else if (m_timer.GetElapsed() < 0.001f)
	{
		TransitionManager::StartFadingOut();
	}
	else
	{
		m_gameUI.Update(static_cast<float>(m_gameSettings->GetGameLenght()) - m_timer.GetElapsed());
	}



}


void GameSystem::LoadNextLevel()
{
	TransitionManager::Update();

	m_atomicBomb.Reset();

	if (!TransitionManager::GetIsBlack())
	{
		return;
	}

	if (m_levelSelector.GetHasPlaylistEnded())
	{
		m_currState = GAME_OVER;
		return;
	}

	m_gameUI.SetPauseDisplay(true);
	m_gameUI.Update(0);
	m_pressToCont.Render();

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		m_gameUI.SetPauseDisplay(false);
		LevelHandler levelHandler;
		m_world->EnterWorld(m_levelSelector.GetLevel());
		m_currState = START_PLAY;
		m_playCountdown = true;
		TransitionManager::StartFadingIn();
	}
}


void GameSystem::GameOver()
{
	TransitionManager::Update();

	m_gameUI.SetPauseDisplay(true);
	m_gameUI.SetShowWinner(true);
	m_gameUI.Update(0);
	m_pressToCont.SetText("Press S to return");
	m_pressToCont.Render();

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		TransitionManager::StartFadingIn();
		StateManager::Get()->SetCurrentState(GameState::LOAD_MAIN_MENU);
	}
}