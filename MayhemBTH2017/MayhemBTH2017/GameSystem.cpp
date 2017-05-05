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
	case PLAYER_READY:
		UpdatePlayerReady();
		break;

	case PLAY:
		break;

	case LOAD_NEXT_LEVEL:
		break;

	default:
		break;
	}
}


void GameSystem::UpdatePlayerReady()
{
	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_playerReady[0] = !m_playerReady[0];
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_playerReady[1] = !m_playerReady[1];
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_playerReady[2] = !m_playerReady[2];
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_A))
	{
		m_playerReady[3] = !m_playerReady[3];
	}

	if (m_input->GetButtonDown(CONTROLLER_BUTTON_START))
	{
		for (uint32_t i = 0; i < MAX_PLAYERS; i++)
		{
			if (m_playerReady[i])
			{
				m_gameMode = INIT_PLAY;
				return;
			}
		}
	}
}

