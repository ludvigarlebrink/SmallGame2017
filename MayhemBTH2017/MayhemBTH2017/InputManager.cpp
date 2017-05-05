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

bool InputManager::GetButtonDown(size_t button, size_t controller)
{
	return m_playerController[controller].GetButtonDown(button);
}

bool InputManager::GetButtonHeld(size_t button, size_t controller)
{
	return m_playerController[controller].GetButtonHeld(button);
}

bool InputManager::GetButtonUp(size_t button, size_t controller)
{
	return m_playerController[controller].GetButtonUp(button);
}

float InputManager::GetAxis(size_t axis, size_t controller)
{
	return m_playerController[controller].GetAxis(axis);
}

float InputManager::GetAxisRaw(size_t axis, size_t controller)
{
	return m_playerController[controller].GetAxisRaw(axis);
}

int InputManager::GetControllerID(int ID)
{
	return m_playerController[0].GetControllerIndex(ID);
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
//		m_playerController[m_nrOfPlayers].AddPlayerController(m_nrOfPlayers);
	}
}

void InputManager::RemovePlayer(uint32_t value)
{

	m_playerController[value].RemovePlayerController();
	m_nrOfPlayers--;

}

void InputManager::Update()
{

	m_playerController[0].Update();

}

void InputManager::Reset()
{
	for (int i = 0; i < m_nrOfPlayers; i++)
	{
		m_playerController[i].Reset();
	}
}

void InputManager::Init()
{
	m_nrOfPlayers = 1;
	m_maxNrOfPlayers = 4;

	SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);
	std::cout << "INITTED" << std::endl;
}