#include "InputManager.h"


InputManager * InputManager::m_instance = nullptr;

InputManager::InputManager()
{
	// Do nothing...
}


InputManager::~InputManager()
{
	// Do nothing...
}

//::.. FAKE CONSTRUCTORS ..:://
void InputManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
		Init();
	}
}

void InputManager::ShutDown()
{
	for (int i = 0; i < m_nrOfPlayers; i++)
	{
		m_playerController[i].RemovePlayerController();
	}
}

InputManager * InputManager::Get()
{
	return m_instance;
}

uint32_t InputManager::GetNrOfPlayers()
{
	return m_nrOfPlayers;
}

void InputManager::SetNrOfPlayers(uint32_t value)
{
	m_nrOfPlayers = value;
}

void InputManager::AddPlayer()
{
	if (m_nrOfPlayers < m_maxNrOfPlayers)
	{
		m_nrOfPlayers++;
		m_playerController[m_nrOfPlayers].StartUp();
	}
}

void InputManager::RemovePlayer(uint32_t value)
{

	m_playerController[value].RemovePlayerController();
	m_nrOfPlayers--;

}

void InputManager::Update()
{
	for (int i = 0; i < m_nrOfPlayers; i++)
		m_playerController[i].Update();
}

void InputManager::Init()
{
	m_nrOfPlayers = 1;
	m_maxNrOfPlayers = 4;
	m_playerController[m_nrOfPlayers].StartUp();
}


